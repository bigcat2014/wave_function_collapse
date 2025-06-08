#include <map>
#include <memory>
#include <wave_function_collapse/wave_function_collapse.hpp>

template <typename T>
void addRelationships(wfc::WaveFunctionCollapse<T>& w) {
  // Edges for vertex 0
  w.addRelationship(0, 0, 0);
  w.addRelationship(0, 0, 1);
  w.addRelationship(0, 0, 2);
  w.addRelationship(0, 0, 3);

  w.addRelationship(0, 1, 1);

  w.addRelationship(0, 2, 2);

  w.addRelationship(0, 3, 3);

  w.addRelationship(0, 4, 0);

  // Edges for vertex 1
  w.addRelationship(1, 0, 3);

  w.addRelationship(1, 1, 0);
  w.addRelationship(1, 1, 2);

  w.addRelationship(1, 2, 0);
  w.addRelationship(1, 2, 1);

  w.addRelationship(1, 3, 0);
  w.addRelationship(1, 3, 1);
  w.addRelationship(1, 3, 2);
  w.addRelationship(1, 3, 3);

  w.addRelationship(1, 4, 1);
  w.addRelationship(1, 4, 2);

  // Edges for vertex 2
  w.addRelationship(2, 0, 0);

  w.addRelationship(2, 1, 2);
  w.addRelationship(2, 1, 3);

  w.addRelationship(2, 2, 1);
  w.addRelationship(2, 2, 3);

  w.addRelationship(2, 3, 1);
  w.addRelationship(2, 3, 2);

  w.addRelationship(2, 4, 0);
  w.addRelationship(2, 4, 1);
  w.addRelationship(2, 4, 2);
  w.addRelationship(2, 4, 3);

  // Edges for vertex 3
  w.addRelationship(3, 0, 1);

  w.addRelationship(3, 1, 0);
  w.addRelationship(3, 1, 1);
  w.addRelationship(3, 1, 2);
  w.addRelationship(3, 1, 3);

  w.addRelationship(3, 2, 0);
  w.addRelationship(3, 2, 3);

  w.addRelationship(3, 3, 0);
  w.addRelationship(3, 3, 2);

  w.addRelationship(3, 4, 2);
  w.addRelationship(3, 4, 3);

  // Edges for vertex 4
  w.addRelationship(4, 0, 2);

  w.addRelationship(4, 1, 0);
  w.addRelationship(4, 1, 3);

  w.addRelationship(4, 2, 0);
  w.addRelationship(4, 2, 1);
  w.addRelationship(4, 2, 2);
  w.addRelationship(4, 2, 3);

  w.addRelationship(4, 3, 0);
  w.addRelationship(4, 3, 1);

  w.addRelationship(4, 4, 1);
  w.addRelationship(4, 4, 3);
}

template <typename T>
void addNeighbors(wfc::WaveFunctionCollapse<T>& w) {
  // Row 1
  w.addNeighbor(0, 1, 2);
  w.addNeighbor(0, 4, 3);

  w.addNeighbor(1, 0, 0);
  w.addNeighbor(1, 2, 2);
  w.addNeighbor(1, 5, 3);

  w.addNeighbor(2, 1, 0);
  w.addNeighbor(2, 3, 2);
  w.addNeighbor(2, 6, 3);

  w.addNeighbor(3, 2, 0);
  w.addNeighbor(3, 7, 3);

  // Row 2
  w.addNeighbor(4, 0, 1);
  w.addNeighbor(4, 5, 2);
  w.addNeighbor(4, 8, 3);

  w.addNeighbor(5, 1, 1);
  w.addNeighbor(5, 4, 0);
  w.addNeighbor(5, 6, 2);
  w.addNeighbor(5, 9, 3);

  w.addNeighbor(6, 2, 1);
  w.addNeighbor(6, 5, 0);
  w.addNeighbor(6, 7, 2);
  w.addNeighbor(6, 10, 3);

  w.addNeighbor(7, 3, 1);
  w.addNeighbor(7, 6, 0);
  w.addNeighbor(7, 11, 3);

  // Row 3
  w.addNeighbor(8, 4, 1);
  w.addNeighbor(8, 9, 2);
  w.addNeighbor(8, 12, 3);

  w.addNeighbor(9, 5, 1);
  w.addNeighbor(9, 8, 0);
  w.addNeighbor(9, 10, 2);
  w.addNeighbor(9, 13, 3);

  w.addNeighbor(10, 6, 1);
  w.addNeighbor(10, 9, 0);
  w.addNeighbor(10, 11, 2);
  w.addNeighbor(10, 14, 3);

  w.addNeighbor(11, 7, 1);
  w.addNeighbor(11, 10, 0);
  w.addNeighbor(11, 15, 3);

  // Row 4
  w.addNeighbor(12, 8, 1);
  w.addNeighbor(12, 13, 2);

  w.addNeighbor(13, 9, 1);
  w.addNeighbor(13, 12, 0);
  w.addNeighbor(13, 14, 2);

  w.addNeighbor(14, 10, 1);
  w.addNeighbor(14, 13, 0);
  w.addNeighbor(14, 15, 2);

  w.addNeighbor(15, 11, 1);
  w.addNeighbor(15, 14, 0);
}

int main(int argc, char const* argv[]) {
  std::map<unsigned, std::shared_ptr<int>> resources;

  wfc::WaveFunctionCollapse<int> w(16);

  {
    auto tmpData = std::make_shared<int>(0);
    auto tmpVertex = w.addResource(tmpData);
    resources[tmpVertex] = tmpData;

    tmpData = std::make_shared<int>(1);
    tmpVertex = w.addResource(tmpData);
    resources[tmpVertex] = tmpData;

    tmpData = std::make_shared<int>(2);
    tmpVertex = w.addResource(tmpData);
    resources[tmpVertex] = tmpData;

    tmpData = std::make_shared<int>(3);
    tmpVertex = w.addResource(tmpData);
    resources[tmpVertex] = tmpData;

    tmpData = std::make_shared<int>(4);
    tmpVertex = w.addResource(tmpData);
    resources[tmpVertex] = tmpData;
  }

  addRelationships(w);
  addNeighbors(w);

  w.init();
  // w.collapse(5, 4); // This is ok by itself
  // w.collapse(9, 0); // This throws if both lines uncommented
  w.run();
  w.printBoard();

  return 0;
}
