#pragma once

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/adjacency_matrix.hpp>
#include <boost/graph/graphviz.hpp>
#include <boost/graph/named_function_params.hpp>
#include <boost/graph/properties.hpp>
#include <boost/property_map/property_map.hpp>

namespace wfc {

template <typename T>
struct RelVertexData {
  T data;
};

template <typename T>
struct BoardVertexData : public RelVertexData<T> {
  unsigned entropy;
};

struct EdgeData {
  unsigned dimension;
};

template <typename T>
class wfc {
 private:
  using Relationships =
      boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS,
                            RelVertexData<T>, EdgeData, boost::no_property,
                            boost::listS>;
  using Board =
      boost::adjacency_matrix<boost::undirectedS, BoardVertexData<T>, EdgeData,
                              boost::no_property, std::allocator<bool>>;

  Relationships m_Relationships;
  Board m_Board;

 public:
  bool addRelationship(unsigned v1, unsigned v2, unsigned dimension) {
    return false;
  }

  bool addNeighbor(unsigned v1, unsigned v2) { return false; }

 private:
  inline T& getRelationshipData(unsigned vertex) {
    get(&RelVertexData<T>::data, m_Relationships)[vertex];
  }

  inline T& getBoardData(unsigned vertex) {
    get(&BoardVertexData<T>::data, m_Board)[vertex];
  }
};

}  // namespace wfc