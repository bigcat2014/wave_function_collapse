#pragma once

#include <functional>
#include <memory>
#include <unordered_set>
#include <vector>

namespace wave_function_collapse
{
template <class T>
struct Vertex
{
  //! \brief Construct a graph vertex with the specified value.
  //! \param [in] value The value to store in the vertex.
  Vertex<T>(const T& value): data(value) {}

  //! \brief The value stored in the vertex.
  T data;

  //! \brief The adjacent vertices in the graph.
  std::vector<Vertex<T>> adj;

  // Arithmetic operators
  inline T operator+(const Vertex<T>& rhs)                      const { return data + rhs.data; }
  inline T operator+(const T& rhs)                              const { return data + rhs; }
  inline friend T operator+(const T& lhs, const Vertex<T>& rhs)       { return lhs + rhs.data; }

  inline T operator-(const Vertex<T>& rhs)                      const { return data - rhs.data; }
  inline T operator-(const T& rhs)                              const { return data - rhs; }
  inline friend T operator-(const T& lhs, const Vertex<T>& rhs)       { return lhs - rhs.data; }

  inline T operator*(const Vertex<T>& rhs)                      const { return data * rhs.data; }
  inline T operator*(const T& rhs)                              const { return data * rhs; }
  inline friend T operator*(const T& lhs, const Vertex<T>& rhs)       { return lhs * rhs.data; }

  inline T operator/(const Vertex<T>& rhs)                      const { return data / rhs.data; }
  inline T operator/(const T& rhs)                              const { return data / rhs; }
  inline friend T operator/(const T& lhs, const Vertex<T>& rhs)       { return lhs / rhs.data; }

  inline T operator%(const Vertex<T>& rhs)                      const { return data % rhs.data; }
  inline T operator%(const T& rhs)                              const { return data % rhs; }
  inline friend T operator%(const T& lhs, const Vertex<T>& rhs)       { return lhs % rhs.data; }

  // Compound assignment operators
  inline Vertex<T>& operator+=(const Vertex<T>& rhs)                      const { data = rhs.data; return *this; }
  inline Vertex<T>& operator+=(const T& rhs)                              const { data = rhs; return *this; }
  inline friend Vertex<T>& operator+=(const T& lhs, const Vertex<T>& rhs)       { lhs += rhs.data; return lhs; }

  // Increment and decrement

  // Relational and comparison operators
  // template <typename U=T>
  // inline auto operator==(const Vertex<U>& rhs)                       -> decltype(data = rhs.data) const { return data == rhs.data; }
  // template <typename U=T>
  // inline auto operator==(const U& rhs)                               -> decltype(data = rhs) const { return data == rhs; }
  // template <typename U=T>
  // inline friend auto operator==(const U& lhs, const Vertex<U>& rhs)       -> decltype(lhs = rhs.data) { return lhs == rhs.data; }

  inline bool operator==(const Vertex<T>& rhs)                      const { return data == rhs.data; }
  inline bool operator==(const T& rhs)                              const { return data == rhs; }
  inline friend bool operator==(const T& lhs, const Vertex<T>& rhs)       { return lhs == rhs.data; }

  inline bool operator!=(const Vertex<T>& rhs)                      const { return data != rhs.data; }
  inline bool operator!=(const T& rhs)                              const { return data != rhs; }
  inline friend bool operator!=(const T& lhs, const Vertex<T>& rhs)       { return lhs != rhs.data; }

  inline bool operator>(const Vertex<T>& rhs)                       const { return data > rhs.data; }
  inline bool operator>(const T& rhs)                               const { return data > rhs; }
  inline friend bool operator>(const T& lhs, const Vertex<T>& rhs)        { return lhs > rhs.data; }

  inline bool operator>=(const Vertex<T>& rhs)                      const { return data >= rhs.data; }
  inline bool operator>=(const T& rhs)                              const { return data >= rhs; }
  inline friend bool operator>=(const T& lhs, const Vertex<T>& rhs)       { return lhs >= rhs.data; }

  inline bool operator<(const Vertex<T>& rhs)                       const { return data < rhs.data; }
  inline bool operator<(const T& rhs)                               const { return data < rhs; }
  inline friend bool operator<(const T& lhs, const Vertex<T>& rhs)        { return lhs < rhs.data; }

  inline bool operator<=(const Vertex<T>& rhs)                      const { return data <= rhs.data; }
  inline bool operator<=(const T& rhs)                              const { return data <= rhs; }
  inline friend bool operator<=(const T& lhs, const Vertex<T>& rhs)       { return lhs <= rhs.data; }

  // Logical operators
  inline bool operator!()                                           const { return !data; }

  inline bool operator&&(const Vertex<T>& rhs)                      const { return data && rhs.data; }
  inline bool operator&&(const T& rhs)                              const { return data && rhs; }
  inline friend bool operator&&(const T& lhs, const Vertex<T>& rhs)       { return lhs && rhs.data; }

  inline bool operator||(const Vertex<T>& rhs)                      const { return data || rhs.data; }
  inline bool operator||(const T& rhs)                              const { return data || rhs; }
  inline friend bool operator||(const T& lhs, const Vertex<T>& rhs)       { return lhs || rhs.data; }

  // Conditional ternary operator

  // Bitwise operators
  inline T operator&(const Vertex<T>& rhs)                      const { return data & rhs.data; }
  inline T operator&(const T& rhs)                              const { return data & rhs; }
  inline friend T operator&(const T& lhs, const Vertex<T>& rhs)       { return lhs & rhs.data; }

  inline T operator|(const Vertex<T>& rhs)                      const { return data | rhs.data; }
  inline T operator|(const T& rhs)                              const { return data | rhs; }
  inline friend T operator|(const T& lhs, const Vertex<T>& rhs)       { return lhs | rhs.data; }

  inline T operator^(const Vertex<T>& rhs)                      const { return data ^ rhs.data; }
  inline T operator^(const T& rhs)                              const { return data ^ rhs; }
  inline friend T operator^(const T& lhs, const Vertex<T>& rhs)       { return lhs ^ rhs.data; }

  inline T operator~()                                          const { return ~data; }

  // Stream insertion operator
  inline friend std::ostream& operator<<(std::ostream& os, const Vertex<T>& vertex) { os << vertex.data; return os;}
};
} // namespace wave_function_collapse
