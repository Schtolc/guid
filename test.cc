#include "Guid.hh"

#include "benchmark/benchmark.h"
#include <uuid/uuid.h>

static void GuidMyGen(benchmark::State &state) {
  Guid::Generator guid_gen{};
  while (state.KeepRunning()) {
    auto guid = guid_gen();
  }
}
BENCHMARK(GuidMyGen);
BENCHMARK(GuidMyGen)->Threads(4);

static void GuidLibuuidGen(benchmark::State &state) {
  while (state.KeepRunning()) {
    uuid_t u{};
    uuid_generate_random(u);
  }
}
BENCHMARK(GuidLibuuidGen);
BENCHMARK(GuidLibuuidGen)->Threads(4);

int main(int argc, char **argv) {
  benchmark::Initialize(&argc, argv);
  benchmark::RunSpecifiedBenchmarks();
}
