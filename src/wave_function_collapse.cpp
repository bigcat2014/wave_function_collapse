#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/breadth_first_search.hpp>
#include <boost/graph/graphviz.hpp>
#include <boost/graph/named_function_params.hpp>
#include <boost/graph/properties.hpp>
#include <boost/property_map/property_map.hpp>
#include <iostream>
#include <iterator>
#include <random>
#include <ranges>
#include <string>
// #include <wave_function_collapse/wave_function_collapse.hpp>

template <typename T>
struct RelVertexData;
template <typename T>
struct BoardVertexData;
struct EdgeData;

template <typename T>
using tmpRelationships =
    boost::adjacency_list<boost::vecS, boost::vecS, boost::bidirectionalS,
                          RelVertexData<T>, EdgeData, boost::no_property,
                          boost::listS>;

template <typename T>
using tmpBoard =
    boost::adjacency_list<boost::vecS, boost::vecS, boost::bidirectionalS,
                          BoardVertexData<T>, EdgeData, boost::no_property,
                          boost::listS>;

template <typename T>
struct RelVertexData {
  T data;
};

template <typename T>
struct BoardVertexData {
  std::vector<
      typename tmpRelationships<T>::vertex_descriptor> mutable potentialStates;
  unsigned entropy() const { return potentialStates.size(); };
};

struct EdgeData {
  unsigned dimension;
};

template <typename T>
void createVertices(tmpRelationships<T>& R) {
  add_vertex({0}, R);
  add_vertex({1}, R);
  add_vertex({2}, R);
  add_vertex({3}, R);
  add_vertex({4}, R);
}

template <typename T>
void createRelationships(tmpRelationships<T>& R) {
  // Edges for vertex 0
  add_edge(0, 0, {0}, R).first;
  add_edge(0, 0, {1}, R);
  add_edge(0, 0, {2}, R);
  add_edge(0, 0, {3}, R);

  add_edge(0, 1, {1}, R);

  add_edge(0, 2, {2}, R);

  add_edge(0, 3, {3}, R);

  add_edge(0, 4, {0}, R);

  // Edges for vertex 1
  add_edge(1, 0, {3}, R);

  add_edge(1, 1, {0}, R);
  add_edge(1, 1, {2}, R);

  add_edge(1, 2, {0}, R);
  add_edge(1, 2, {1}, R);

  add_edge(1, 3, {0}, R);
  add_edge(1, 3, {1}, R);
  add_edge(1, 3, {2}, R);
  add_edge(1, 3, {3}, R);

  add_edge(1, 4, {1}, R);
  add_edge(1, 4, {2}, R);

  // Edges for vertex 2
  add_edge(2, 0, {0}, R);

  add_edge(2, 1, {2}, R);
  add_edge(2, 1, {3}, R);

  add_edge(2, 2, {1}, R);
  add_edge(2, 2, {3}, R);

  add_edge(2, 3, {1}, R);
  add_edge(2, 3, {2}, R);

  add_edge(2, 4, {0}, R);
  add_edge(2, 4, {1}, R);
  add_edge(2, 4, {2}, R);
  add_edge(2, 4, {3}, R);

  // Edges for vertex 3
  add_edge(3, 0, {1}, R);

  add_edge(3, 1, {0}, R);
  add_edge(3, 1, {1}, R);
  add_edge(3, 1, {2}, R);
  add_edge(3, 1, {3}, R);

  add_edge(3, 2, {0}, R);
  add_edge(3, 2, {3}, R);

  add_edge(3, 3, {0}, R);
  add_edge(3, 3, {2}, R);

  add_edge(3, 4, {2}, R);
  add_edge(3, 4, {3}, R);

  // Edges for vertex 4
  add_edge(4, 0, {2}, R);

  add_edge(4, 1, {0}, R);
  add_edge(4, 1, {3}, R);

  add_edge(4, 2, {0}, R);
  add_edge(4, 2, {1}, R);
  add_edge(4, 2, {2}, R);
  add_edge(4, 2, {3}, R);

  add_edge(4, 3, {0}, R);
  add_edge(4, 3, {1}, R);

  add_edge(4, 4, {1}, R);
  add_edge(4, 4, {3}, R);
}

template <typename T>
void createBoard(tmpBoard<T>& B) {
  // Row 1
  add_edge(0, 1, {2}, B);
  add_edge(0, 4, {3}, B);

  add_edge(1, 0, {0}, B);
  add_edge(1, 2, {2}, B);
  add_edge(1, 5, {3}, B);

  add_edge(2, 1, {0}, B);
  add_edge(2, 3, {2}, B);
  add_edge(2, 6, {3}, B);

  add_edge(3, 2, {0}, B);
  add_edge(3, 7, {3}, B);

  // Row 2
  add_edge(4, 0, {1}, B);
  add_edge(4, 5, {2}, B);
  add_edge(4, 8, {3}, B);

  add_edge(5, 1, {1}, B);
  add_edge(5, 4, {0}, B);
  add_edge(5, 6, {2}, B);
  add_edge(5, 9, {3}, B);

  add_edge(6, 2, {1}, B);
  add_edge(6, 5, {0}, B);
  add_edge(6, 7, {2}, B);
  add_edge(6, 10, {3}, B);

  add_edge(7, 3, {1}, B);
  add_edge(7, 6, {0}, B);
  add_edge(7, 11, {3}, B);

  // Row 3
  add_edge(8, 4, {1}, B);
  add_edge(8, 9, {2}, B);
  add_edge(8, 12, {3}, B);

  add_edge(9, 5, {1}, B);
  add_edge(9, 8, {0}, B);
  add_edge(9, 10, {2}, B);
  add_edge(9, 13, {3}, B);

  add_edge(10, 6, {1}, B);
  add_edge(10, 9, {0}, B);
  add_edge(10, 11, {2}, B);
  add_edge(10, 14, {3}, B);

  add_edge(11, 7, {1}, B);
  add_edge(11, 10, {0}, B);
  add_edge(11, 15, {3}, B);

  // Row 4
  add_edge(12, 8, {1}, B);
  add_edge(12, 13, {2}, B);

  add_edge(13, 9, {1}, B);
  add_edge(13, 12, {0}, B);
  add_edge(13, 14, {2}, B);

  add_edge(14, 10, {1}, B);
  add_edge(14, 13, {0}, B);
  add_edge(14, 15, {2}, B);

  add_edge(15, 11, {1}, B);
  add_edge(15, 14, {0}, B);
}

template <typename T>
void printRelationships(tmpRelationships<T>& R) {
  std::cout << "Relationships:" << std::endl;
  auto vpair = vertices(R);
  for (auto iter = vpair.first; iter != vpair.second; iter++) {
    std::cout << "vertex: " << *iter
              << " data: " << get(&RelVertexData<int>::data, R)[*iter]
              << std::endl;
  }

  auto epair = edges(R);
  for (auto iter = epair.first; iter != epair.second; iter++) {
    std::cout << "edge " << source(*iter, R) << " - " << target(*iter, R)
              << " has dimension " << get(&EdgeData::dimension, R)[*iter]
              << std::endl;
  }
}

template <typename T>
void printBoard(tmpBoard<T>& B) {
  std::cout << "\nBoard:" << std::endl;
  auto vpair = vertices(B);
  for (auto iter = vpair.first; iter != vpair.second; iter++) {
    std::cout << "vertex: " << *iter;
    if (B[*iter].potentialStates.size() == 1) {
      std::cout << " data: " << B[*iter].potentialStates[0];
    }
    std::cout << " entropy: " << B[*iter].entropy() << std::endl;
  }

  // auto epair = edges(B);
  // for (auto iter = epair.first; iter != epair.second; iter++) {
  //   std::cout << "edge " << source(*iter, B) << " - " << target(*iter, B)
  //             << " has dimension " << get(&EdgeData::dimension, B)[*iter]
  //             << std::endl;
  // }
}

template <typename T>
void printAll(tmpBoard<T>& B, tmpRelationships<T>& R) {
  printRelationships<T>(R);
  printBoard<T>(B);
}

template <typename T>
class BFSWFCVisitor : public boost::default_bfs_visitor {
 public:
  BFSWFCVisitor(const tmpRelationships<T>& R) : m_relationships(R) {}
  template <typename Vertex, typename Graph>
  void discover_vertex(Vertex currentVertex, Graph& G) {
    if (G[currentVertex].potentialStates.size() == 1) {
      // std::cout << "Vertex " << currentVertex << " already collapsed.
      // Skipping."
      //           << std::endl;
      return;
    }
    // std::cout << "Visited vertex " << currentVertex << std::endl;

    auto currentEdges = out_edges(currentVertex, G);
    std::unordered_set<typename tmpRelationships<T>::vertex_descriptor>
        compatibleStates;
    for (auto cEdgeIter = currentEdges.first; cEdgeIter != currentEdges.second;
         cEdgeIter++) {
      // std::cout << "Checking edge with dimension " << G[*cEdgeIter].dimension
      //           << std::endl;
      // Get neighbor along current edge
      auto neighborVertex = target(*cEdgeIter, G);
      // Get the returning edge from neighbor so we can get the returning
      // dimension
      auto invEdgePair = edge(neighborVertex, currentVertex, G);
      if (!invEdgePair.second) {
        throw new std::domain_error("Shit's broke");
      }

      std::unordered_set<typename tmpRelationships<T>::vertex_descriptor>
          nCompatibleStates;
      for (auto state : G[neighborVertex].potentialStates) {
        // Get all potential states for current vertex based on relationships
        // and neighbor potential states
        auto neighborEdges = out_edges(state, m_relationships);
        for (auto nEdgeIter = neighborEdges.first;
             nEdgeIter != neighborEdges.second; nEdgeIter++) {
          if (m_relationships[*nEdgeIter].dimension !=
              G[invEdgePair.first].dimension) {
            continue;
          }
          // Build set of states compatible with neighbor vertex
          nCompatibleStates.insert(target(*nEdgeIter, m_relationships));
        }
      }
      // Intersection of compatible states
      if (compatibleStates.empty()) {
        compatibleStates = nCompatibleStates;
      } else {
        std::erase_if(compatibleStates,
                      [&nCompatibleStates](
                          typename tmpRelationships<T>::vertex_descriptor e) {
                        return !nCompatibleStates.contains(e);
                      });
      }
    }

    // Set current vertex potential states to compatible states
    G[currentVertex].potentialStates =
        std::vector(compatibleStates.begin(), compatibleStates.end());
  }

 private:
  const tmpRelationships<T>& m_relationships;
};

// template <typename T>
// void updateNeighbors(tmpBoard<T>& B, const tmpRelationships<T>& R,
//                      const typename tmpBoard<T>::vertex_descriptor bV) {
//   // auto epair = out_edges(bV, B);
//   // for (auto iter = epair.first; iter != epair.second; iter++) {
//   //   std::cout << "Out edge from " << source(*iter, B) << " - "
//   //             << target(*iter, B) << " has dimension "
//   //             << get(&EdgeData::dimension, B)[*iter] << std::endl;
//   // }

//   boost::breadth_first_search(B, bV, boost::visitor(BFSWFCVisitor<T>(R)));
// }

template <typename T>
void collapse(tmpBoard<T>& B, const tmpRelationships<T>& R,
              const typename tmpBoard<T>::vertex_descriptor bV,
              const typename tmpRelationships<T>::vertex_descriptor rV) {
  B[bV].potentialStates = {rV};

  // updateNeighbors<T>(B, R, bV);
  boost::breadth_first_search(B, bV, boost::visitor(BFSWFCVisitor<T>(R)));
}

template <typename Iter, typename RandomGenerator>
Iter select_randomly(Iter start, Iter end, RandomGenerator& g) {
  std::uniform_int_distribution<> dis(0, std::distance(start, end) - 1);
  std::advance(start, dis(g));
  return start;
}

template <typename Iter>
Iter select_randomly(Iter start, Iter end) {
  static std::random_device rd;
  static std::mt19937 gen(rd());
  return select_randomly(start, end, gen);
}

int main(int argc, char const* argv[]) {
  tmpRelationships<int> R;
  createVertices<int>(R);
  createRelationships<int>(R);

  tmpBoard<int> B(16);

  createBoard<int>(B);

  auto bvpair = vertices(B);
  auto rvpair = vertices(R);
  for (auto iter = bvpair.first; iter != bvpair.second; iter++) {
    B[*iter].potentialStates = std::vector(rvpair.first, rvpair.second);
  }

  // printAll<int>(B, R);

  collapse(B, R, 5, 1);

  for (unsigned i = 0; i < num_vertices(B); i++) {
    typename tmpBoard<int>::vertex_descriptor min = 0;
    for (auto iter = bvpair.first; iter != bvpair.second; iter++) {
      if ((B[*iter].entropy() != 1 && min == 0) ||
          (B[*iter].entropy() != 1 && B[*iter].entropy() < B[min].entropy())) {
        min = *iter;
      }
    }
    // vec | std::ranges::views::filter([](int a) { return a % 2 == 0; });
    // auto minEntropyIter =
    //     std::min_element(bvpair.first, bvpair.second,
    //                      [&B](typename tmpBoard<int>::vertex_descriptor v1,
    //                           typename tmpBoard<int>::vertex_descriptor v2) {
    //                        if (B[v1].entropy() == 1) {
    //                          return false;
    //                        }
    //                        return B[v1].entropy() <= B[v2].entropy();
    //                      });
    // std::cout << "Next vertex descriptor: " << min << std::endl;
    // if (B[*minEntropyIter].entropy() == 1) {
    //   break;
    // }

    collapse(B, R, min,
             *select_randomly(B[min].potentialStates.begin(),
                              B[min].potentialStates.end()));
  }

  printBoard<int>(B);

  return 0;
}
