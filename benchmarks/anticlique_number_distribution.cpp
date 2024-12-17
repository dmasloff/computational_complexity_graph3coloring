#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <random>
#include "graph.h"

std::random_device random_device;
std::mt19937_64 gen(random_device());
std::uniform_real_distribution<> distribution(0.0, 1.0);

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

template<size_t n>
void GenerateAverageMaxAnticliqueNumberDistribution(std::string filename, float density = 0.01, size_t k = 5000) {
  std::ofstream output_file(filename);
  std::vector<std::vector<size_t>> results(1 + n * (n - 1) / 2);
  for (float p = 0.0; p <= 1; p += density) {
    std::cout << p << '\n';
    for (int i = 0; i < k; ++i) {
      auto graph = GenerateRandomGraph<n>(p);
      auto anticliques = graph.ListAllMaxAnticliques();
      results[graph.EdgeCount()].push_back(anticliques.size());
    }
  }
  for (auto group : results) {
    size_t sum = 0;
    for (auto value : group) {
      sum += value;
    }
    output_file << static_cast<float>(sum) / group.size() << '\n';
  }
}

int main() {
  GenerateAverageMaxAnticliqueNumberDistribution<30>("graph30.txt");
  GenerateAverageMaxAnticliqueNumberDistribution<40>("graph40.txt");
  GenerateAverageMaxAnticliqueNumberDistribution<50>("graph50.txt");
}
