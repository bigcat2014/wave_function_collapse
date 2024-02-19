#include <iostream>
#include <string>

#include <wave_function_collapse/graph/graph.hpp>

class MyClass
{
public:
  MyClass(const std::string& name): name_(name) {}

private:
  std::string name_;
};

namespace wfc = wave_function_collapse;
int main(int argc, char const *argv[])
{
  wfc::Graph<int> graph1;
  graph1.addVertex(1);
  graph1.addVertex(2);

  wfc::Graph<int> graph2;
  graph2.addVertex(3);
  graph2.addVertex(4);

  // wfc::Graph<wfc::Graph<int>> graph3;
  // graph3.addVertex(graph1);
  // graph3.addVertex(graph2);

  // std::cout << "Graph 1: [ ";
  // for (auto vertex : graph1)
  // {
  //   std::cout << vertex << " ";
  // }
  // std::cout << "]" << std::endl;

  // std::cout << "Graph 2: [ ";
  // for (auto vertex : graph2)
  // {
  //   std::cout << vertex << " ";
  // }
  // std::cout << "]" << std::endl;

  return 0;
}
