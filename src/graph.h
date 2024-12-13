//
// Created by Даниил Маслов on 09.12.2024.
//

#include <algorithm>
#include <bitset>
#include <iostream>
#include <set>
#include <stack>
#include <vector>


#ifndef COMPUTATIONAL_COMPLEXITY_GRAPH3COLORING_GRAPH_H
#define COMPUTATIONAL_COMPLEXITY_GRAPH3COLORING_GRAPH_H

template<size_t n>
class VertexSubset {
 public:
  VertexSubset(const std::bitset<n>& set_mask)
    : set_mask_(set_mask) {}

  VertexSubset(std::bitset<n>&& set_mask)
    : set_mask_(std::move(set_mask)) {}

  VertexSubset(const VertexSubset& other)
    : set_mask_(other.set_mask_) {}

  VertexSubset(VertexSubset&& other)
    : set_mask_(std::move(other.set_mask_)) {}

  VertexSubset& operator=(const VertexSubset& other) {
    set_mask_ = other.set_mask_;
    return *this;
  }

  VertexSubset& operator=(VertexSubset&& other) {
    set_mask_ = std::move(other);
    return *this;
  }

  const std::bitset<n>& View() const {
    return set_mask_;
  }

  std::bitset<n>&& Extract() {
    return std::move(set_mask_);
  }

  size_t MinVertex() const {
    for (size_t i = 0; i < n; ++i) {
      if (set_mask_[i]) {
        return i;
      }
    }
    return n;
  }

  bool operator<(const VertexSubset& other) const {
    for (size_t i = 0; i < n; ++i) {
      if (set_mask_[i] != other.set_mask_[i]) {
        return set_mask_[i] == 1;
      }
    }
    return false;
  }

  bool operator>(const VertexSubset& other) const {
    return other < *this;
  }

  bool operator==(const VertexSubset& other) const {
    return set_mask_ == other.set_mask_;
  }

 private:
  std::bitset<n> set_mask_;
};

template<size_t n>
class Graph {
 public:
  using VertexSet = VertexSubset<n>;

  Graph() : adjacency_matrix_(n) {}

  Graph(const std::vector<std::vector<size_t>>& adjacency_list)
    : adjacency_matrix_(n) {
    for (size_t i = 0; i < n; ++i) {
      for (const auto& j: adjacency_list[i]) {
        adjacency_matrix_[i].set(j);
      }
    }
  }

  Graph(const std::vector<std::bitset<n>>& adjacency_matrix)
    : adjacency_matrix_(adjacency_matrix) {}

  Graph(std::vector<std::bitset<n>>&& adjacency_matrix)
    : adjacency_matrix_(std::move(adjacency_matrix)) {}


  std::vector<std::bitset<n>> ListAllMaxAnticliques() const {
    std::vector<std::bitset<n>> answer;
    std::set<VertexSet> queue;

    VertexSet first = VertexSet(LexMinMaxAnticlique());
    queue.insert(first);

    size_t cnt = 0;

    while (!queue.empty()) {
      cnt += 1;
      auto it = queue.begin();
      VertexSet s = queue.extract(it).value();
      for (size_t j = s.MinVertex() + 1; j < n; ++j) {
        if (CheckMaxAnticliqueOnPrefixConstraint(s, j)) {
          std::bitset<n> set_mask = s.View();
          set_mask >>= (n - j - 1);
          set_mask <<= (n - j - 1);
          set_mask &= (~adjacency_matrix_[j]);
          set_mask.set(j);
          VertexSet t(LexMinMaxAnticlique(set_mask));
          if (s < t) {
            queue.insert(std::move(t));
          }
        }
      }
      answer.push_back(std::move(s.Extract()));
      if (cnt > 10) {
        break;
      }
    }
    return answer;
  }

  bool Check3Coloring() const {
    std::vector<std::bitset<n>> max_anticliques = ListAllMaxAnticliques();
    for (const auto& max_anticlique : max_anticliques) {
      if (CheckRestIsBipartite(max_anticlique)) {
        return true;
      }
    }
    return false;
  }

  const std::vector<std::bitset<n>>& View() const {
    return adjacency_matrix_;
  }

 private:
  std::vector<std::bitset<n>> adjacency_matrix_;

  std::bitset<n> LexMinMaxAnticlique() const {
    std::bitset<n> access;
    for (size_t i = 0; i < n; ++i) {
      if (!access[i]) {
        access |= adjacency_matrix_[i];
      }
    }
    access.flip();
    return access;
  }

  std::bitset<n> LexMinMaxAnticlique(const std::bitset<n>& condition) const {
    std::bitset<n> access;
    for (size_t i = 0; i < n; ++i) {
      if (condition[i]) {
        access |= adjacency_matrix_[i];
      }
    }
    for (size_t i = 0; i < n; ++i) {
      if (!access[i]) {
        access |= adjacency_matrix_[i];
      }
    }
    access.flip();
    return access;
  }

  bool CheckMaxAnticliqueOnPrefixConstraint(const VertexSet& vertex_set, size_t j) const {
    std::bitset<n> set_mask = vertex_set.View();
    std::bitset<n> covering_mask;
    for (size_t i = 0; i <= j; ++i) {
      if ((set_mask[i] && !adjacency_matrix_[j][i]) || i == j) {
        covering_mask.set(i);
        covering_mask |= adjacency_matrix_[i];
      }
    }
    for (size_t i = 0; i <= j; ++i) {
      if (!covering_mask[i]) {
        return false;
      }
    }
    return true;
  }

  bool CheckRestIsBipartite(const std::bitset<n> set_mask) const {
    std::vector<char> color(n, -1);
    std::stack<std::pair<size_t, size_t>> st;
    for (size_t i = 0; i < n; ++i) {
      if (set_mask[i]) {
        color[i] = 3;
      }
    }
    for (size_t i = 0; i < n; ++i) {
      if (color[i] == -1) {
        st.push({i, 0});
        color[i] = 1;
      }
      while (!st.empty()) {
        std::pair<size_t, size_t> top = st.top();
        size_t v = top.first, index = top.second;
        while (index < n) {
          if (adjacency_matrix_[v][index] && color[index] == -1) {
            st.push({index, 0});
            color[index] = 3 - color[v];
            break;
          }
          if (adjacency_matrix_[v][index] && color[v] == color[index]) {
            return false;
          }
          ++index;
        }
        if (index == n) {
          st.pop();
        }
      }
    }
    return true;
  }
};

#endif //COMPUTATIONAL_COMPLEXITY_GRAPH3COLORING_GRAPH_H
