#include <array>
#include <memory>
#include <algorithm>

namespace lib
{
template<class T, T Default>
class Row
{
  std::unordered_map<size_t, T> row_;
 public:
  class Iter
  {
    using IterImpl = typename std::unordered_map<size_t, T>::iterator;

    Row& matrix_;
    IterImpl impl_;
   public:
    using Cell = std::tuple<size_t, T>;
    Iter() = delete;
    explicit Iter(Row& matrix, size_t offset = 0)
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

    Row* operator ->() { return &matrix_; }

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

template<class T, T DefaultValue>
class Matrix
{
  using _Row = Row<T, DefaultValue>;
  using Table = std::unordered_map<uint64_t, _Row>;

  friend class Iter;

  Table table_;
 public:
  size_t GetSize()
  {
    size_t count = 0;

    for (auto& row : table_)
    {
      count += row.second.GetSize();
    }

    return count;
  }

  _Row& operator [](size_t index)
  {
    return table_[index];
  }
};
}
