#include <array>
#include <cstring>
#include <random>
#include <sstream>

namespace Guid {
struct guid {
  static constexpr uint8_t UUID_SIZE = 16;

  std::string dump() const {
    std::stringstream ss{};
    ss << std::hex;
    ss.fill(ss.widen('0'));
    std::size_t i = 0;
    for (auto it = octets.cbegin(); it != octets.cend(); ++it, ++i) {
      ss.width(2);
      ss << static_cast<uint32_t>(*it);
      if (i == 3 || i == 5 || i == 7 || i == 9) {
        ss << ss.widen('-');
      }
    }
    return ss.str();
  }

  std::array<uint8_t, UUID_SIZE> octets{};
};

class Generator {
public:
  Generator() : rd{}, gen{rd()} {}

  guid operator()() {
    guid g{};
    uint64_t rand_num_left = gen();
    uint64_t rand_num_right = gen();
    std::memcpy(g.octets.data(), &rand_num_left, sizeof(rand_num_left));
    std::memcpy(g.octets.data() + sizeof(rand_num_left), &rand_num_right,
                sizeof(rand_num_right));
    return g;
  }

private:
  std::random_device rd;
  std::mt19937_64 gen;
};
} // Guid
