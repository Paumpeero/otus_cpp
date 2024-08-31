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
  using Table = std::unordered_map<uint64_t, Row<T, DefaultValue>>;

  Table table_;
 public:
  class Iter
  {
    using Cell = std::tuple<uint64_t, uint64_t, T>;

    Table& table_;
    Table::iterator table_iter_;
    Row<T, DefaultValue>::Iter row_iter_;
   public:
    Iter() = delete;

    Iter(Table::iterator table_iter,
         Row<T, DefaultValue>::Iter row_iter,
         Table& table)
      : table_iter_(table_iter), row_iter_(row_iter), table_(table) {}

    Cell operator *() { return std::tuple_cat(table_iter_->first, *row_iter_); }
    Table* operator ->() { return table_iter_; }

    bool operator ==(const Iter& rhs) const
    {
      return table_iter_ == rhs.table_iter_ && row_iter_ == rhs.row_iter_;
    }

    bool operator !=(const Iter& rhs) { return !this->operator ==(rhs); }

    Iter& operator ++()
    {
      if (table_iter_ == table_.end()) return;

      if (row_iter_ == table_iter_->second.end())
      {
        ++table_iter_;
        row_iter_ = table_iter_->second.begin();
      }
      else
      {
        ++row_iter_;
      }
    }
  };
  size_t GetSize()
  {
    size_t count = 0;

    for (auto& row: table_)
    {
      count += row.second.GetSize();
    }

    return count;
  }

  Row<T, DefaultValue>& operator [](size_t index)
  {
    return table_[index];
  }

  Iter begin()
  {
    typename Table::iterator table_iter = table_.begin();
    Row<T, DefaultValue> row_iter;

    if (table_iter != table_.end())
    {
      row_iter = table_iter->second.begin();
    }

    return Iter(table_iter, row_iter, table_);
  }

  Iter end()
  {
    typename Table::iterator table_iter = table_.end();
    Row<T, DefaultValue> row_iter;

    return Iter(table_iter, row_iter, table_);
  }
};
}
