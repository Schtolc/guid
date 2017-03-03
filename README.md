1. Алгоритм.
Для генерации глобального уникального идентификатора был выбран random-based метод, так как согласно [RFC4122](https://www.ietf.org/rfc/rfc4122.txt) подходит для данной задачии он прост в реализации. Для генерации случайных битов был использован алгоритм [Mersenne_Twister](https://en.wikipedia.org/wiki/Mersenne_Twister).

2. Использование.

#include "Guid.hh"
#include <iostream>

int main() {
    Guid::Generator guid_gen{};
        auto g = guid_gen();
            std::cout << g.dump() << '\n';
                // guid string, e.g. 019de418-f735-ad3f-a788-06f76b1a638e

}

3. Производительность.
В сравнение с radnom-based генератором в libguuid на i7-4710MQ 2.50GHz c 4 физ. ядрами google-benchmark показывает:
----------------------------------------------------------------
Benchmark                         Time           CPU Iterations
----------------------------------------------------------------
GuidMyGen                        34 ns         34 ns   19602129
GuidMyGen/threads:4              10 ns         40 ns   17143776
GuidLibuuidGen                 4283 ns       4283 ns     163608
GuidLibuuidGen/threads:4       4531 ns      14073 ns      51228

Т.е. представленный способ быстрее где-то в 15000 раз быстрее в 1 поток и в 1500000 раз быстрее в 4 потока.

4. Коллизии.
При конструировании большого количества генераторов (не самих guid'ов) возможны коллизии, так как std::random_device, использованный для засеивания алгоритма Мерсенна генерирует 32-битные числа. Поэтому рекомедуется использовать static или tread_local генераторы.
