#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphviz.hpp>
#include <boost/graph/named_function_params.hpp>
#include <boost/graph/properties.hpp>
#include <boost/property_map/property_map.hpp>
#include <iostream>
#include <string>
#include <wave_function_collapse/wave_function_collapse.hpp>

template <typename T>
using tmpRelationships =
    boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS,
                          wfc::RelVertexData<T>, wfc::EdgeData,
                          boost::no_property, boost::listS>;

template <typename T>
void createRelationships(tmpRelationships<T>& R) {
  auto v0 = add_vertex(R);
  R[v0].data = 0;
  auto v1 = add_vertex(R);
  R[v1].data = 1;
  auto v2 = add_vertex(R);
  R[v2].data = 2;
  auto v3 = add_vertex(R);
  R[v3].data = 3;
  auto v4 = add_vertex(R);
  R[v4].data = 4;

  // Edges for vertex 0
  auto e1 = add_edge(v0, v0, R).first;
  R[e1].dimension = 0;
  e1 = add_edge(v0, v0, R).first;
  R[e1].dimension = 1;
  e1 = add_edge(v0, v0, R).first;
  R[e1].dimension = 2;
  e1 = add_edge(v0, v0, R).first;
  R[e1].dimension = 3;

  e1 = add_edge(v0, v1, R).first;
  R[e1].dimension = 1;

  e1 = add_edge(v0, v2, R).first;
  R[e1].dimension = 2;

  e1 = add_edge(v0, v3, R).first;
  R[e1].dimension = 3;

  e1 = add_edge(v0, v4, R).first;
  R[e1].dimension = 0;

  // Edges for vertex 1
  e1 = add_edge(v1, v0, R).first;
  R[e1].dimension = 3;

  e1 = add_edge(v1, v1, R).first;
  R[e1].dimension = 0;
  e1 = add_edge(v1, v1, R).first;
  R[e1].dimension = 2;

  e1 = add_edge(v1, v2, R).first;
  R[e1].dimension = 0;
  e1 = add_edge(v1, v2, R).first;
  R[e1].dimension = 1;

  e1 = add_edge(v1, v3, R).first;
  R[e1].dimension = 0;
  e1 = add_edge(v1, v3, R).first;
  R[e1].dimension = 1;
  e1 = add_edge(v1, v3, R).first;
  R[e1].dimension = 2;
  e1 = add_edge(v1, v3, R).first;
  R[e1].dimension = 3;

  e1 = add_edge(v1, v4, R).first;
  R[e1].dimension = 1;
  e1 = add_edge(v1, v4, R).first;
  R[e1].dimension = 2;

  // Edges for vertex 2
  e1 = add_edge(v2, v0, R).first;
  R[e1].dimension = 0;

  e1 = add_edge(v2, v1, R).first;
  R[e1].dimension = 2;
  e1 = add_edge(v2, v1, R).first;
  R[e1].dimension = 3;

  e1 = add_edge(v2, v2, R).first;
  R[e1].dimension = 1;
  e1 = add_edge(v2, v2, R).first;
  R[e1].dimension = 3;

  e1 = add_edge(v2, v3, R).first;
  R[e1].dimension = 1;
  e1 = add_edge(v2, v3, R).first;
  R[e1].dimension = 2;

  e1 = add_edge(v2, v4, R).first;
  R[e1].dimension = 0;
  e1 = add_edge(v2, v4, R).first;
  R[e1].dimension = 1;
  e1 = add_edge(v2, v4, R).first;
  R[e1].dimension = 2;
  e1 = add_edge(v2, v4, R).first;
  R[e1].dimension = 3;

  // Edges for vertex 3
  e1 = add_edge(v3, v0, R).first;
  R[e1].dimension = 1;

  e1 = add_edge(v3, v1, R).first;
  R[e1].dimension = 0;
  e1 = add_edge(v3, v1, R).first;
  R[e1].dimension = 1;
  e1 = add_edge(v3, v1, R).first;
  R[e1].dimension = 2;
  e1 = add_edge(v3, v1, R).first;
  R[e1].dimension = 3;

  e1 = add_edge(v3, v2, R).first;
  R[e1].dimension = 0;
  e1 = add_edge(v3, v2, R).first;
  R[e1].dimension = 3;

  e1 = add_edge(v3, v3, R).first;
  R[e1].dimension = 0;
  e1 = add_edge(v3, v3, R).first;
  R[e1].dimension = 2;

  e1 = add_edge(v3, v4, R).first;
  R[e1].dimension = 2;
  e1 = add_edge(v3, v4, R).first;
  R[e1].dimension = 3;

  // Edges for vertex 4
  e1 = add_edge(v4, v0, R).first;
  R[e1].dimension = 2;

  e1 = add_edge(v4, v1, R).first;
  R[e1].dimension = 0;
  e1 = add_edge(v4, v1, R).first;
  R[e1].dimension = 3;

  e1 = add_edge(v4, v2, R).first;
  R[e1].dimension = 0;
  e1 = add_edge(v4, v2, R).first;
  R[e1].dimension = 1;
  e1 = add_edge(v4, v2, R).first;
  R[e1].dimension = 2;
  e1 = add_edge(v4, v2, R).first;
  R[e1].dimension = 3;
  e1 = add_edge(v4, v2, R).first;
  R[e1].dimension = 2;
  e1 = add_edge(v4, v2, R).first;
  R[e1].dimension = 3;

  e1 = add_edge(v4, v3, R).first;
  R[e1].dimension = 0;
  e1 = add_edge(v4, v3, R).first;
  R[e1].dimension = 1;

  e1 = add_edge(v4, v4, R).first;
  R[e1].dimension = 1;
  e1 = add_edge(v4, v4, R).first;
  R[e1].dimension = 3;
}

int main(int argc, char const* argv[]) {
  tmpRelationships<int> R;
  createRelationships<int>(R);

  auto vpair = vertices(R);
  for (auto iter = vpair.first; iter != vpair.second; iter++) {
    std::cout << "vertex: " << *iter
              << " data: " << get(&wfc::RelVertexData<int>::data, R)[*iter]
              << std::endl;
  }

  auto epair = edges(R);
  for (auto iter = epair.first; iter != epair.second; iter++) {
    std::cout << "edge " << source(*iter, R) << " - " << target(*iter, R)
              << " has dimension " << get(&wfc::EdgeData::dimension, R)[*iter]
              << std::endl;
  }

  return 0;
}
