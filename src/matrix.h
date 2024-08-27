#include <array>
#include <memory>
#include <algorithm>

namespace lib
{
template<class T, T Default, size_t DimensionsCount>
class Matrix
{
  using LowerMatrix = Matrix<T, Default, DimensionsCount - 1>;

  std::unordered_map<size_t, LowerMatrix> row_;
 public:
  class Iter
  {
   public:
    using Cell = decltype(std::tuple_cat(size_t(0), typename LowerMatrix::Iter::Cell()));
    using IterImpl = typename std::unordered_map<size_t, LowerMatrix>::iterator;

    explicit Iter(Matrix& matrix, size_t offset) noexcept
    : matrix_(matrix), iter_(matrix_.begin())
    {
      while (offset)
      {
        ++iter_;
        --offset;
      }
    }

    friend class Matrix<T, Default, DimensionsCount + 1>;
   private:
    Matrix& matrix_;
    IterImpl iter_;
  };

  size_t GetSize() const
  {
    size_t i = 0;

    for (auto& [key, lower_matrix]: row_)
    {
      i += lower_matrix.GetSize();
    }

    return i;
  }

  LowerMatrix& operator [](size_t i)
  {
    return row_[i];
  }

  Iter begin() { return Iter(*this); }
  Iter from(size_t offset) { return Iter(*this, offset); }
  Iter end() { return Iter(*this, GetSize()); }
};

template<class T, T Default>
class Matrix<T, Default, 1>
{
  std::unordered_map<size_t, T> row_;
 public:
  class Iter
  {
    using IterImpl = typename std::unordered_map<size_t, T>::iterator;

    Matrix& matrix_;
    IterImpl impl_;
   public:
    using Cell = std::tuple<size_t, T>;
    Iter() = delete;
    explicit Iter(Matrix& matrix, size_t offset = 0)
      : matrix_(matrix), impl_(matrix_.row_.begin())
    {
      while (offset)
      {
        ++impl_;
        --offset;
      }
    }

    Cell operator *()
    {
      return tuple<size_t, T&>(impl_->first, impl_->second);
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

    Iter& operator ++()
    {
      ++impl_;
      return *this;
    }
  };

  size_t GetSize() const
  {
    size_t i = 0;

    for (auto& [key, value]: row_)
    {
      if (value != Default) ++i;
    }

    return i;
  }

  T& operator [](size_t i)
  {
    if (!row_.count(i))
    {
      row_[i] = Default;
    }

    return row_[i];
  }

  Iter begin() { return Iter(*this); }
  Iter from(size_t i) { return Iter(*this, i); }
  Iter end() { return Iter(*this, row_.size()); }
};
}
