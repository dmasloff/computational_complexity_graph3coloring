#include <gtest/gtest.h>
#include "graph.h"

template <size_t n>
Graph<n> BuildGraph(std::vector<std::pair<size_t, size_t>> edges) {
  std::vector<std::vector<size_t>> adj_list(n);
  for (const auto &edge : edges) {
    adj_list[edge.first - 1].push_back(edge.second - 1);
    adj_list[edge.second - 1].push_back(edge.first - 1);
  }
  return Graph<n>(adj_list);
}

template <size_t n>
Graph<n> BuildFullGraph() {
  std::vector<std::vector<size_t>> adj_list(n);
  for (size_t i = 0; i < n; ++i) {
    for (size_t j = i + 1; j < n; ++j) {
      adj_list[i].push_back(j);
      adj_list[j].push_back(i);
    }
  }
  return Graph<n>(adj_list);
}

TEST(LexMinMaxAnticlique, EmptyGraphs) {
  Graph<1> gr1;
  Graph<2> gr2;
  Graph<3> gr3;
  Graph<4> gr4;
  Graph<5> gr5;

  EXPECT_EQ(gr1.LexMinMaxAnticlique(), std::bitset<1>(0b1));
  EXPECT_EQ(gr2.LexMinMaxAnticlique(), std::bitset<2>(0b11));
  EXPECT_EQ(gr3.LexMinMaxAnticlique(), std::bitset<3>(0b111));
  EXPECT_EQ(gr4.LexMinMaxAnticlique(), std::bitset<4>(0b1111));
  EXPECT_EQ(gr5.LexMinMaxAnticlique(), std::bitset<5>(0b11111));
}

TEST(LexMinMaxAnticlique, FullGraphs) {
  Graph<1> gr1 = BuildFullGraph<1>();
  Graph<2> gr2 = BuildFullGraph<2>();
  Graph<3> gr3 = BuildFullGraph<3>();
  Graph<4> gr4 = BuildFullGraph<4>();
  Graph<5> gr5 = BuildFullGraph<5>();

  EXPECT_EQ(gr1.LexMinMaxAnticlique(), std::bitset<1>(0b1));
  EXPECT_EQ(gr2.LexMinMaxAnticlique(), std::bitset<2>(0b1));
  EXPECT_EQ(gr3.LexMinMaxAnticlique(), std::bitset<3>(0b1));
  EXPECT_EQ(gr4.LexMinMaxAnticlique(), std::bitset<4>(0b1));
  EXPECT_EQ(gr5.LexMinMaxAnticlique(), std::bitset<5>(0b1));
}

TEST(LexMinMaxAnticlique, MixedGraphs) {
  Graph<5> gr1 = BuildGraph<5>({{1, 2}});
  Graph<5> gr2 = BuildGraph<5>({{1, 2}, {1, 4}});
  Graph<5> gr3 = BuildGraph<5>({{1, 2}, {1, 3}, {1, 4}});
  Graph<5> gr4 = BuildGraph<5>({{1, 5}, {2, 5}, {3, 5}, {1, 2}});

  EXPECT_EQ(gr1.LexMinMaxAnticlique(), std::bitset<5>(0b11101));
  EXPECT_EQ(gr2.LexMinMaxAnticlique(), std::bitset<5>(0b10101));
  EXPECT_EQ(gr3.LexMinMaxAnticlique(), std::bitset<5>(0b10001));
  EXPECT_EQ(gr4.LexMinMaxAnticlique(), std::bitset<5>(0b01101));
}

TEST(ListAllMaxAnticliques, EmptyGraphs) {
  Graph<1> gr1;
  Graph<2> gr2;
  Graph<3> gr3;
  Graph<4> gr4;
  Graph<5> gr5;

  std::vector<std::bitset<1>> ans1{std::bitset<1>(0b1)};
  std::vector<std::bitset<2>> ans2{std::bitset<2>(0b11)};
  std::vector<std::bitset<3>> ans3{std::bitset<3>(0b111)};
  std::vector<std::bitset<4>> ans4{std::bitset<4>(0b1111)};
  std::vector<std::bitset<5>> ans5{std::bitset<5>(0b11111)};

  EXPECT_EQ(gr1.ListAllMaxAnticliques(), ans1);
  EXPECT_EQ(gr2.ListAllMaxAnticliques(), ans2);
  EXPECT_EQ(gr3.ListAllMaxAnticliques(), ans3);
  EXPECT_EQ(gr4.ListAllMaxAnticliques(), ans4);
  EXPECT_EQ(gr5.ListAllMaxAnticliques(), ans5);
}

TEST(ListAllMaxAnticliques, FullGraphs) {
  Graph<1> gr1 = BuildFullGraph<1>();
  Graph<2> gr2 = BuildFullGraph<2>();
  Graph<3> gr3 = BuildFullGraph<3>();
  Graph<4> gr4 = BuildFullGraph<4>();
  Graph<5> gr5 = BuildFullGraph<5>();

  std::vector<std::bitset<1>> ans1{std::bitset<1>(0b1)};
  std::vector<std::bitset<2>> ans2{std::bitset<2>(0b01),
                                   std::bitset<2>(0b10)};
  std::vector<std::bitset<3>> ans3{std::bitset<3>(0b001),
                                   std::bitset<3>(0b010),
                                   std::bitset<3>(0b100)};
  std::vector<std::bitset<4>> ans4{std::bitset<4>(0b0001),
                                   std::bitset<4>(0b0010),
                                   std::bitset<4>(0b0100),
                                   std::bitset<4>(0b1000)};
  std::vector<std::bitset<5>> ans5{std::bitset<5>(0b00001),
                                   std::bitset<5>(0b00010),
                                   std::bitset<5>(0b00100),
                                   std::bitset<5>(0b01000),
                                   std::bitset<5>(0b10000)};

  EXPECT_EQ(gr1.ListAllMaxAnticliques(), ans1);
  EXPECT_EQ(gr2.ListAllMaxAnticliques(), ans2);
  EXPECT_EQ(gr3.ListAllMaxAnticliques(), ans3);
  EXPECT_EQ(gr4.ListAllMaxAnticliques(), ans4);
  EXPECT_EQ(gr5.ListAllMaxAnticliques(), ans5);
}

TEST(ListAllMaxAnticliques, MixedGraphs) {
  Graph<3> gr1 = BuildGraph<3>({{1, 2}});
  std::vector<std::bitset<3>> ans1{std::bitset<3>(0b101),
                                   std::bitset<3>(0b110)};

  Graph<3> gr2 = BuildGraph<3>({{1, 2}, {1, 3}});
  std::vector<std::bitset<3>> ans2{std::bitset<3>(0b001),
                                   std::bitset<3>(0b110)};

  Graph<4> gr3 = BuildGraph<4>({{1, 2}, {1, 3}, {1, 4}});
  std::vector<std::bitset<4>> ans3{std::bitset<4>(0b0001),
                                   std::bitset<4>(0b1110)};
  Graph<4> gr4 = BuildGraph<4>({{1, 2}, {2, 3}, {3, 4}});
  std::vector<std::bitset<4>> ans4{std::bitset<4>(0b0101),
                                   std::bitset<4>(0b1001),
                                   std::bitset<4>(0b1010)};

  Graph<4> gr5 = BuildGraph<4>({{1, 2}, {2, 3}, {3, 4}, {4, 1}});
  std::vector<std::bitset<4>> ans5{std::bitset<4>(0b0101),
                                   std::bitset<4>(0b1010)};

  EXPECT_EQ(gr1.ListAllMaxAnticliques(), ans1);
  EXPECT_EQ(gr2.ListAllMaxAnticliques(), ans2);
  EXPECT_EQ(gr3.ListAllMaxAnticliques(), ans3);
  EXPECT_EQ(gr4.ListAllMaxAnticliques(), ans4);
  EXPECT_EQ(gr5.ListAllMaxAnticliques(), ans5);
}

TEST(Check3Coloring, EmptyGraphs) {
  Graph<1> gr1;
  Graph<2> gr2;
  Graph<3> gr3;
  Graph<4> gr4;
  Graph<5> gr5;

  EXPECT_TRUE(gr1.Check3Coloring());
  EXPECT_TRUE(gr2.Check3Coloring());
  EXPECT_TRUE(gr3.Check3Coloring());
  EXPECT_TRUE(gr4.Check3Coloring());
  EXPECT_TRUE(gr5.Check3Coloring());
}

TEST(Check3Coloring, FullGraphs) {
  Graph<1> gr1 = BuildFullGraph<1>();
  Graph<2> gr2 = BuildFullGraph<2>();
  Graph<3> gr3 = BuildFullGraph<3>();
  Graph<4> gr4 = BuildFullGraph<4>();
  Graph<5> gr5 = BuildFullGraph<5>();

  EXPECT_TRUE(gr1.Check3Coloring());
  EXPECT_TRUE(gr2.Check3Coloring());
  EXPECT_TRUE(gr3.Check3Coloring());
  EXPECT_FALSE(gr4.Check3Coloring());
  EXPECT_FALSE(gr5.Check3Coloring());
}

TEST(Check3Coloring, MixedGraphs) {
  // G = (V, E)
  // ---------
  //  1 --- 2
  //   \   /
  //     3
  //   /   \
  //  4 --- 5
  // ---------
  // X(G) = 3
  Graph<5> gr1 = BuildGraph<5>({{1, 2}, {1, 3}, {2, 3}, {3, 4}, {3, 5}, {4, 5}});

  // G = (V, E)
  // ---------
  //  1 --- 2
  //  | \ / |
  //  |  5  |
  //  | / \ |
  //  4 --- 3
  // ---------
  // X(G) = 3
  Graph<5> gr2 = BuildGraph<5>({{1, 2}, {2, 3}, {3, 4}, {4, 1},
                               {1, 5}, {2, 5}, {3, 5}, {4, 5}});

  // G = (V, E)
  // ---------
  //  1 --- 2
  //  |\   /  \
  //  |  3     |
  //  |/   \   |
  //  4 --- 5  |
  //   \_______|
  // ---------
  // X(G) = 4
  Graph<5> gr3 = BuildGraph<5>({{1, 2}, {1, 3}, {2, 3}, {1, 4},
                               {3, 4}, {2, 4}, {3, 5}, {4, 5}});

  EXPECT_TRUE(gr1.Check3Coloring());
  EXPECT_TRUE(gr2.Check3Coloring());
  EXPECT_FALSE(gr3.Check3Coloring());
}

TEST(Check3Coloring, NamedGraphs) {
  //     G = (V, E)
  // -------------------
  //      ___ 1 ___
  //    /   /   \   \
  //   /   /     \   \
  //  |   2 ----- 3   |
  //  | /   \   /   \ |
  //  |/     \ /     \|
  //  4 ----- 5 ----- 6
  //   \_____________/
  // -------------------
  // X(G) = 3
  Graph<6> plain_graph = BuildGraph<6>({{1, 2}, {1, 3}, {1, 4}, {1, 6},
                                        {2, 3}, {2, 4}, {2, 5}, {3, 5},
                                        {3, 6}, {4, 5}, {4, 6}, {5, 6}});

  /// G = (V, E)
  // ---------------
  // G - граф Петерсена(https://ru.wikipedia.org/wiki/Граф_Петерсена)
  Graph<10> petersen_graph = BuildGraph<10>({
    {1, 2}, {1, 3}, {1, 4}, {2, 5}, {2, 9},
    {3, 7}, {3, 8}, {4, 6}, {4, 10}, {5, 6},
    {5, 8}, {6, 7}, {7, 9}, {8, 10}, {9, 10}
  });

  EXPECT_TRUE(plain_graph.Check3Coloring());
  EXPECT_TRUE(petersen_graph.Check3Coloring());
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}