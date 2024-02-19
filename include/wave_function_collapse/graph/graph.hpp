#pragma once

#include <algorithm>
#include <exception>
#include <iostream>
#include <iterator>

#include <wave_function_collapse/graph/vertex.hpp>


namespace wave_function_collapse
{
class GraphException;

template <class T>
class Graph
{
public:
  Graph() = default;

  struct Iterator;
  // Iterator begin() { return Iterator(&vertices_[0]); }
  // Iterator end() { return Iterator(&vertices_[vertices_.size()]); }

  //! \brief Add a vertex to the graph.
  //!
  //! \param [in] value The value to store in the new vertex.
  //! \return true If the vertex is successfully added.
  //! \return false If the vertex is not successfully added.
  //! If the vertex cannot be added this means that the vertex already exists.
  bool addVertex(const T& value) noexcept
  {
    return addVertex(Vertex<T>(value));
  }

  //! \brief Add an edge to the graph.
  //! Add an undirected edge between two vertices of the graph.
  //!
  //! \param [in] value_1 The value in the first vertex to create the edge between.
  //! \param [in] value_2 The value in the second vertex to create the edge between.
  //! \return true If the edge is successfully added.
  //! \return false If the edge is not successfully added.
  //! If the edge cannot be added then one of the vertices does not exist.
  bool addEdge(const T& value_1, const T& value_2) noexcept
  {
    // Get references to the specified vertices
    auto value_1_vertex = std::find(vertices_.begin(), vertices_.end(), value_1);
    auto value_2_vertex = std::find(vertices_.begin(), vertices_.end(), value_2);

    // If either of the vertices don't exist, return false
    if (value_1_vertex == vertices_.end() || value_2_vertex == vertices_.end()) { return false; }

    // If the edge already exists return false
    if (std::find(value_1_vertex->adj.begin(), value_1_vertex->adj.end(), value_2) != value_1_vertex->adj.end()) { return false; }
    if (std::find(value_2_vertex->adj.begin(), value_2_vertex->adj.end(), value_1) != value_2_vertex->adj.end()) { return false; }

    // Add value_2 to the adjacency list of value_1
    value_1_vertex->adj.emplace_back(Vertex<T>(value_2));

    // If value_1 == value_2, the edge is a loopback; avoid adding the edge to the same adjacency list twice
    if (value_1 != value_2)
    {
      value_2_vertex->adj.emplace_back(Vertex<T>(value_1));
    }

    return true;
  }

  //! \brief Get the vertex with the specified value.
  //!
  //! \param [in] value The value stored in the vertex to return.
  //! \exception GraphException Thrown when the requested vertex is not found in the graph.
  //! \return Vertex<T> The vertex that contains the value specified.
  Vertex<T> getVertex(const T& value) const
  {
    auto vertex_itr = std::find_if(vertices_.begin(), vertices_.end(), [value](const Vertex<T>& v)
    {
      return value == v;
    });

    if (vertex_itr == vertices_.end())
    {
      throw GraphException("Vertex not found.");
    }
    return *vertex_itr;
  }

  //! \brief Get the list of vertices in the graph.
  //! \return std::vector<Vertex<T>> The list of vertices in the graph.
  std::vector<Vertex<T>> getVertices() { return vertices_; }

  //! \brief Whether or not the graph is cyclic.
  //! \return true If the graph is cyclic.
  //! \return false If the graph is not cyclic.
  bool isCyclic()
  {
    return true;
  }

  // struct DFSIterator
  // {
  //   using iterator_category = std::input_iterator_tag;
  //   using difference_type   = std::ptrdiff_t;
  //   using value_type        = Vertex<T>;
  //   using pointer           = Vertex<T>*;
  //   using reference         = Vertex<T>&;

  //   Iterator(pointer ptr): ptr_(ptr) {}

  //   reference operator*() const { return *ptr_; }
  //   pointer operator->() { return ptr_; }

  //   // Prefix increment
  //   Iterator& operator++() { ptr_++; return *this; }  

  //   // Postfix increment
  //   Iterator operator++(int) { Iterator tmp = *this; ++(*this); return tmp; }

  //   friend bool operator== (const Iterator& a, const Iterator& b) { return a.ptr_ == b.ptr_; };
  //   friend bool operator!= (const Iterator& a, const Iterator& b) { return a.ptr_ != b.ptr_; };

  //   private:
  //     pointer ptr_;
  // };

  struct Iterator
  {
    using iterator_category = std::input_iterator_tag;
    using difference_type   = std::ptrdiff_t;
    using value_type        = Vertex<T>;
    using pointer           = Vertex<T>*;
    using reference         = Vertex<T>&;

    Iterator(pointer ptr): ptr_(ptr) {}

    reference operator*() const { return *ptr_; }
    pointer operator->() { return ptr_; }

    // Prefix increment
    Iterator& operator++() { ptr_++; return *this; }  

    // Postfix increment
    Iterator operator++(int) { Iterator tmp = *this; ++(*this); return tmp; }

    friend bool operator== (const Iterator& a, const Iterator& b) { return a.ptr_ == b.ptr_; };
    friend bool operator!= (const Iterator& a, const Iterator& b) { return a.ptr_ != b.ptr_; };

    private:
      pointer ptr_;
  };

private:
  //! \brief The list of vertices in the graph.
  std::vector<Vertex<T>> vertices_;

  //! \brief Add a vertex to the graph.
  //!
  //! \param [in] vertex The vertex to add to the graph.
  //! \return true If the vertex is successfully added.
  //! \return false If the vertex is not successfully added.
  //! If the vertex cannot be added this means that the vertex already exists.
  bool addVertex(const Vertex<T>& vertex) noexcept
  {
    // If the vertex already exists, return false
    if (std::find(vertices_.begin(), vertices_.end(), vertex) != vertices_.end()) { return false; }

    // Add the vertex to the graph
    vertices_.emplace_back(vertex);
    return true;
  }

};

class GraphException : public std::exception
{
public:
  //! \brief Create a GraphException with a specific message.
  //!
  //! \param [in] message The message in the exception.
  GraphException(const std::string& message): message_(message){}

  const char* what() { return message_.c_str(); }

private:
  //! \brief The message of the exception.
  std::string message_;
};

} // namespace wave_function_collapse