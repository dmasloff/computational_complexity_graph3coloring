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


template <size_t n>
Graph<n> GenerateMaxGraph() {
  std::vector<std::bitset<n>> adj_matrix(n);
  if (n % 3 == 0) {
    for (size_t i = 0; i < n; i += 3) {
      adj_matrix[i].set(i + 1);
      adj_matrix[i].set(i + 2);
      adj_matrix[i + 1].set(i);
      adj_matrix[i + 1].set(i + 2);
      adj_matrix[i + 2].set(i);
      adj_matrix[i + 2].set(i + 1);
    }
  }
  if (n % 3 == 1 && n > 3) {
    for (size_t j = 0; j < 4; ++j) {
      for (size_t k = 0; k < 4; ++k) {
        if (j != k) {
          adj_matrix[j].set(k);
          adj_matrix[k].set(j);
        }
      }
    }
    for (size_t i = 4; i < n; i += 3) {
      adj_matrix[i].set(i + 1);
      adj_matrix[i].set(i + 2);
      adj_matrix[i + 1].set(i);
      adj_matrix[i + 1].set(i + 2);
      adj_matrix[i + 2].set(i);
      adj_matrix[i + 2].set(i + 1);
    }
  }
  if (n % 3 == 2) {
    adj_matrix[0].set(1);
    adj_matrix[1].set(0);
    for (size_t i = 2; i < n; i += 3) {
      adj_matrix[i].set(i + 1);
      adj_matrix[i].set(i + 2);
      adj_matrix[i + 1].set(i);
      adj_matrix[i + 1].set(i + 2);
      adj_matrix[i + 2].set(i);
      adj_matrix[i + 2].set(i + 1);
    }
  }
  return Graph<n>(std::move(adj_matrix));
}


template <size_t n>
static void BM_Check3ColoringMaxAnticliques(benchmark::State& state) {
  Graph<n> graph = GenerateMaxGraph<n>();
  for (auto _ : state) {
    bool is3col = graph.Check3Coloring();
    benchmark::DoNotOptimize(is3col);
    benchmark::ClobberMemory();
  }
}

// G(n, p) model tests

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

// Tests on graphs with maximal number of anticliques

BENCHMARK_TEMPLATE(BM_Check3ColoringMaxAnticliques, 3ull);
BENCHMARK_TEMPLATE(BM_Check3ColoringMaxAnticliques, 4ull);
BENCHMARK_TEMPLATE(BM_Check3ColoringMaxAnticliques, 5ull);
BENCHMARK_TEMPLATE(BM_Check3ColoringMaxAnticliques, 6ull);
BENCHMARK_TEMPLATE(BM_Check3ColoringMaxAnticliques, 7ull);
BENCHMARK_TEMPLATE(BM_Check3ColoringMaxAnticliques, 8ull);
BENCHMARK_TEMPLATE(BM_Check3ColoringMaxAnticliques, 9ull);
BENCHMARK_TEMPLATE(BM_Check3ColoringMaxAnticliques, 10ull);
BENCHMARK_TEMPLATE(BM_Check3ColoringMaxAnticliques, 11ull);
BENCHMARK_TEMPLATE(BM_Check3ColoringMaxAnticliques, 12ull);
BENCHMARK_TEMPLATE(BM_Check3ColoringMaxAnticliques, 13ull);
BENCHMARK_TEMPLATE(BM_Check3ColoringMaxAnticliques, 14ull);
BENCHMARK_TEMPLATE(BM_Check3ColoringMaxAnticliques, 15ull);
BENCHMARK_TEMPLATE(BM_Check3ColoringMaxAnticliques, 16ull);
BENCHMARK_TEMPLATE(BM_Check3ColoringMaxAnticliques, 17ull);
BENCHMARK_TEMPLATE(BM_Check3ColoringMaxAnticliques, 18ull);
BENCHMARK_TEMPLATE(BM_Check3ColoringMaxAnticliques, 19ull);
BENCHMARK_TEMPLATE(BM_Check3ColoringMaxAnticliques, 20ull);
BENCHMARK_TEMPLATE(BM_Check3ColoringMaxAnticliques, 22ull);
BENCHMARK_TEMPLATE(BM_Check3ColoringMaxAnticliques, 24ull);
BENCHMARK_TEMPLATE(BM_Check3ColoringMaxAnticliques, 26ull);
BENCHMARK_TEMPLATE(BM_Check3ColoringMaxAnticliques, 28ull);
BENCHMARK_TEMPLATE(BM_Check3ColoringMaxAnticliques, 30ull);
BENCHMARK_TEMPLATE(BM_Check3ColoringMaxAnticliques, 32ull);
BENCHMARK_TEMPLATE(BM_Check3ColoringMaxAnticliques, 34ull);
BENCHMARK_TEMPLATE(BM_Check3ColoringMaxAnticliques, 36ull);
BENCHMARK_TEMPLATE(BM_Check3ColoringMaxAnticliques, 38ull);
BENCHMARK_TEMPLATE(BM_Check3ColoringMaxAnticliques, 40ull);
BENCHMARK_TEMPLATE(BM_Check3ColoringMaxAnticliques, 50ull);
BENCHMARK_TEMPLATE(BM_Check3ColoringMaxAnticliques, 60ull);
BENCHMARK_TEMPLATE(BM_Check3ColoringMaxAnticliques, 70ull);

BENCHMARK_MAIN();
