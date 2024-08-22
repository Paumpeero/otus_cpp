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
    using Cell = std::tuple<size_t, T>;

    Matrix& matrix_;
    IterImpl impl_;
   public:
    Iter() = delete;
    Iter(Matrix& matrix, IterImpl impl): matrix_(matrix), impl_(impl) {}

    Cell operator *() {
      return std::make_tuple<size_t, T>(impl_->first, impl_->second);
    }

    Matrix* operator ->() { return &matrix_; }

    bool operator ==(const Iter& rhs)
    {
      return matrix_.row_ == rhs.matrix_.row_ && impl_ == rhs.impl_;
    }

    bool operator !=(const Iter& rhs)
    {
      return !(*this == rhs);
    }
  };

  friend class Iter;

  std::unordered_map<size_t, T> row_;
 public:
  Iter begin() { return Iter(*this, 0); }
  Iter end() { return Iter(*this, row_.size()); }
};
}
