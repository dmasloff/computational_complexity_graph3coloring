#include <benchmark/benchmark.h>
#include <random>
#include <bitset>
#include "graph.h"


std::random_device random_device;
std::mt19937_64 gen(random_device());
std::uniform_real_distribution<> distribution(0.0, 1.0);


// Generates random graph G(n, p) from Erdos-Renyi model
template<size_t n>
Graph<n> GenerateRandomGraph(float p = 0.5) {
  std::vector<std::bitset<n>> adj_matrix(n);
  for (size_t i = 0; i < n; ++i) {
    for (size_t j = i + 1; j < n; ++j) {
      if (distribution(gen) <= p) {
        adj_matrix[i].set(j);
        adj_matrix[j].set(i);
      }
    }
  }
  return Graph<n>(std::move(adj_matrix));
}


template <size_t n>
static void BM_Check3Coloring(benchmark::State& state) {
  for (auto _ : state) {
    state.PauseTiming();
    Graph<n> graph = GenerateRandomGraph<n>();
    state.ResumeTiming();
    bool is3col = graph.Check3Coloring();
    benchmark::DoNotOptimize(is3col);
    benchmark::ClobberMemory();
  }
}


BENCHMARK_TEMPLATE(BM_Check3Coloring, 3ull);
BENCHMARK_TEMPLATE(BM_Check3Coloring, 4ull);
BENCHMARK_TEMPLATE(BM_Check3Coloring, 5ull);
BENCHMARK_TEMPLATE(BM_Check3Coloring, 6ull);
BENCHMARK_TEMPLATE(BM_Check3Coloring, 7ull);
BENCHMARK_TEMPLATE(BM_Check3Coloring, 8ull);
BENCHMARK_TEMPLATE(BM_Check3Coloring, 9ull);
BENCHMARK_TEMPLATE(BM_Check3Coloring, 10ull);
BENCHMARK_TEMPLATE(BM_Check3Coloring, 11ull);
BENCHMARK_TEMPLATE(BM_Check3Coloring, 12ull);
BENCHMARK_TEMPLATE(BM_Check3Coloring, 13ull);
BENCHMARK_TEMPLATE(BM_Check3Coloring, 14ull);
BENCHMARK_TEMPLATE(BM_Check3Coloring, 15ull);
BENCHMARK_TEMPLATE(BM_Check3Coloring, 16ull);
BENCHMARK_TEMPLATE(BM_Check3Coloring, 17ull);
BENCHMARK_TEMPLATE(BM_Check3Coloring, 18ull);
BENCHMARK_TEMPLATE(BM_Check3Coloring, 19ull);
BENCHMARK_TEMPLATE(BM_Check3Coloring, 20ull);
BENCHMARK_TEMPLATE(BM_Check3Coloring, 22ull);
BENCHMARK_TEMPLATE(BM_Check3Coloring, 24ull);
BENCHMARK_TEMPLATE(BM_Check3Coloring, 26ull);
BENCHMARK_TEMPLATE(BM_Check3Coloring, 28ull);
BENCHMARK_TEMPLATE(BM_Check3Coloring, 30ull);
BENCHMARK_TEMPLATE(BM_Check3Coloring, 32ull);
BENCHMARK_TEMPLATE(BM_Check3Coloring, 34ull);
BENCHMARK_TEMPLATE(BM_Check3Coloring, 36ull);
BENCHMARK_TEMPLATE(BM_Check3Coloring, 38ull);
BENCHMARK_TEMPLATE(BM_Check3Coloring, 40ull);
BENCHMARK_TEMPLATE(BM_Check3Coloring, 50ull);
BENCHMARK_TEMPLATE(BM_Check3Coloring, 60ull);
BENCHMARK_TEMPLATE(BM_Check3Coloring, 70ull);
BENCHMARK_TEMPLATE(BM_Check3Coloring, 80ull);
BENCHMARK_TEMPLATE(BM_Check3Coloring, 90ull);
BENCHMARK_TEMPLATE(BM_Check3Coloring, 100ull);



BENCHMARK_MAIN();
