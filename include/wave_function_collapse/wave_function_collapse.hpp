#pragma once

#include <limits.h>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/breadth_first_search.hpp>
#include <boost/graph/properties.hpp>
#include <iostream>
#include <iterator>
#include <memory>
#include <random>

namespace wfc {

template <typename T>
class WaveFunctionCollapse {
 private:
  struct RelationshipVertex;
  struct BoardVertex;
  struct EdgeData;
  using Relationships =
      boost::adjacency_list<boost::vecS, boost::vecS, boost::bidirectionalS,
                            RelationshipVertex, EdgeData, boost::no_property,
                            boost::listS>;

  using Board =
      boost::adjacency_list<boost::vecS, boost::vecS, boost::bidirectionalS,
                            BoardVertex, EdgeData, boost::no_property,
                            boost::listS>;

  Relationships m_Relationships;
  Board m_Board;
  bool initialized = false;

 public:
  WaveFunctionCollapse(typename Board::vertices_size_type size)
      : m_Board(size) {}

  void init() {
    auto bVpair = vertices(m_Board);
    auto rVpair = vertices(m_Relationships);

    // Initialize potential states
    for (auto iter = bVpair.first; iter != bVpair.second; iter++) {
      m_Board[*iter].potentialStates = std::vector(rVpair.first, rVpair.second);
    }
    initialized = true;
  }

  typename Relationships::vertex_descriptor addResource(
      const std::weak_ptr<T> data) {
    auto v = add_vertex({data}, m_Relationships);
    initialized = false;
    return v;
  }

  bool addRelationship(typename Relationships::vertex_descriptor v1,
                       typename Relationships::vertex_descriptor v2,
                       unsigned dimension) {
    auto epair = add_edge(v1, v2, {dimension}, m_Relationships);
    initialized = false;
    return epair.second;
  }

  bool addNeighbor(typename Board::vertex_descriptor v1,
                   typename Board::vertex_descriptor v2, unsigned dimension) {
    auto epair = add_edge(v1, v2, {dimension}, m_Board);
    initialized = false;
    return epair.second;
  }

  std::shared_ptr<T> getData(typename Board::vertex_descriptor v) {
    BoardVertex bV = m_Board[v];
    if (bV.entropy() > 1) {
      throw new std::domain_error("Tile has not been collapsed.");
    }

    return m_Relationships[bV.potentialStates[0]].data.lock();
  }

  void collapse(const typename Board::vertex_descriptor bVd,
                const typename Relationships::vertex_descriptor rVd) {
    if (!initialized) {
      throw new std::domain_error("WFC must be initialized");
    }

    auto bIter = m_Board[bVd].potentialStates.begin();
    auto eIter = m_Board[bVd].potentialStates.end();
    if (std::find(bIter, eIter, rVd) == eIter) {
      throw new std::domain_error("Cannot collapse vertex to specified state.");
    }

    m_Board[bVd].potentialStates = {rVd};
    boost::breadth_first_search(m_Board, bVd,
                                boost::visitor(Visitor(m_Relationships)));
  }

  void run() {
    if (!initialized) {
      throw new std::domain_error("WFC must be initialized");
    }

    auto bVpair = vertices(m_Board);

    // Select random starting vertex
    typename Board::vertex_descriptor min =
        *selectRandom(bVpair.first, bVpair.second);

    // Collapse a vertex on every iteration
    for (unsigned i = 0; i < num_vertices(m_Board); i++) {
      // Collapse the selected vertex with a random state
      collapse(min, *selectRandom(m_Board[min].potentialStates.begin(),
                                  m_Board[min].potentialStates.end()));

      // Find the vertex with the lowest entropy, excluding collapsed vertices
      min = UINT_MAX;
      for (auto vIter = bVpair.first; vIter != bVpair.second; vIter++) {
        if (m_Board[*vIter].entropy() <= 1) {
          continue;
        }
        if (min == UINT_MAX ||
            (m_Board[*vIter].entropy() < m_Board[min].entropy())) {
          min = *vIter;
        }
      }

      // If no uncollapsed vertices have been found, exit early
      if (min == UINT_MAX) {
        break;
      }
    }
  }

  void printBoard() {
    std::cout << "\nBoard:" << std::endl;
    auto vpair = vertices(m_Board);
    for (auto iter = vpair.first; iter != vpair.second; iter++) {
      std::cout << "vertex: " << *iter;
      if (m_Board[*iter].potentialStates.size() == 1) {
        std::cout << " data: " << m_Board[*iter].potentialStates[0];
      }
      std::cout << " entropy: " << m_Board[*iter].entropy() << std::endl;
    }

    // auto epair = edges(B);
    // for (auto iter = epair.first; iter != epair.second; iter++) {
    //   std::cout << "edge " << source(*iter, B) << " - " << target(*iter, B)
    //             << " has dimension " << get(&EdgeData::dimension, B)[*iter]
    //             << std::endl;
    // }
  }

 private:
  struct RelationshipVertex {
    const std::weak_ptr<T> data;
  };

  struct BoardVertex {
    std::vector<
        typename Relationships::vertex_descriptor> mutable potentialStates;
    unsigned entropy() const { return potentialStates.size(); };
  };

  struct EdgeData {
    unsigned dimension;
  };

  template <typename Iter, typename RandomGenerator>
  Iter selectRandom(Iter start, Iter end, RandomGenerator& g) {
    std::uniform_int_distribution<> dis(0, std::distance(start, end) - 1);
    std::advance(start, dis(g));
    return start;
  }

  template <typename Iter>
  Iter selectRandom(Iter start, Iter end) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    return selectRandom(start, end, gen);
  }

  class Visitor : public boost::default_bfs_visitor {
   public:
    Visitor(const Relationships& relationships)
        : m_Relationships(relationships) {}
    void discover_vertex(Board::vertex_descriptor currentVertex,
                         const Board& G) {
      if (G[currentVertex].potentialStates.size() == 1) {
        return;
      }

      auto currentEdges = out_edges(currentVertex, G);
      std::unordered_set<typename Relationships::vertex_descriptor>
          compatibleStates;
      for (auto cEdgeIter = currentEdges.first;
           cEdgeIter != currentEdges.second; cEdgeIter++) {
        // Get neighbor along current edge
        auto neighborVertex = target(*cEdgeIter, G);
        // Get the returning edge from neighbor so we can get the returning
        // dimension
        auto invEdgePair = edge(neighborVertex, currentVertex, G);
        if (!invEdgePair.second) {
          throw new std::domain_error("Shit's broke");
        }

        std::unordered_set<typename Relationships::vertex_descriptor>
            nCompatibleStates;
        for (auto state : G[neighborVertex].potentialStates) {
          // Get all potential states for current vertex based on relationships
          // and neighbor potential states
          auto neighborEdges = out_edges(state, m_Relationships);
          for (auto nEdgeIter = neighborEdges.first;
               nEdgeIter != neighborEdges.second; nEdgeIter++) {
            if (m_Relationships[*nEdgeIter].dimension !=
                G[invEdgePair.first].dimension) {
              continue;
            }
            // Build set of states compatible with neighbor vertex
            nCompatibleStates.insert(target(*nEdgeIter, m_Relationships));
          }
        }
        // Intersection of compatible states
        if (compatibleStates.empty()) {
          compatibleStates = nCompatibleStates;
        } else {
          std::erase_if(compatibleStates,
                        [&nCompatibleStates](
                            typename Relationships::vertex_descriptor e) {
                          return !nCompatibleStates.contains(e);
                        });
        }
      }

      // Set current vertex potential states to compatible states
      G[currentVertex].potentialStates =
          std::vector(compatibleStates.begin(), compatibleStates.end());
    }

   private:
    const Relationships& m_Relationships;
  };
};

}  // namespace wfc