#include <array>
#include <memory>

namespace lib
{
template<class T, T Default, size_t DimensionsCount, class Dimension = size_t, class... Dimensions>
class Matrix
{};

template<class T, T Default>
class Matrix<T, Default, 1, size_t>
{
  class Iter
  {
    using IterImpl = typename std::unordered_map<size_t, T>::iterator;

    std::unordered_map<size_t, T>& row_;
    IterImpl impl_;
   public:
    Iter() = delete;
    Iter(std::unordered_map<size_t, T>& row, IterImpl impl): row_(row), impl_(impl) {}

    bool operator ==(const Iter& rhs)
    {
      return row_ == rhs.row_ && impl_ == rhs.impl_;
    }
    bool operator !=(const Iter& rhs)
    {
      return !(*this == rhs);
    }
  };

  std::unordered_map<size_t, T> row_;
 public:
  Iter begin() { return Iter(row_, 0); }
  Iter end() { return Iter(row_, row_.size()); }
};
}
