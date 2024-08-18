#include <unordered_map>
#include <memory>

namespace lib
{
template<uint64_t Dimensions, int64_t DefaultValue>
class MatrixIterator;

template<uint64_t Dimensions, int64_t DefaultValue>
class IMatrix
{
 protected:
  using Raw = IMatrix<Dimensions - 1, DefaultValue>;
  using Iterator = MatrixIterator<Dimensions, DefaultValue>;
  using ConstIterator = const Iterator;
 public:
  virtual size_t GetSize() const = 0;
  virtual Iterator begin() = 0;
  virtual ConstIterator begin() const = 0;
  virtual Iterator end() = 0;
  virtual ConstIterator end() const = 0;
  virtual Raw& operator [](size_t index) = 0;

  virtual ~IMatrix() = default;
};

template<int64_t DefaultValue>
class IMatrix<1, DefaultValue>
{
  using Raw = int64_t;
 public:
  using Iterator = std::unordered_map<uint64_t, int64_t>::iterator;
  using ConstIterator = const Iterator;

  virtual size_t GetSize() const = 0;
  virtual Iterator begin() = 0;
  virtual ConstIterator begin() const = 0;
  virtual Iterator end() = 0;
  virtual ConstIterator end() const = 0;
  virtual Raw& operator [](size_t index) = 0;

  virtual ~IMatrix() = default;
};

template<uint64_t Dimensions, int64_t DefaultValue>
class MatrixProxy;

template<uint64_t Dimensions, int64_t DefaultValue>
class Matrix : public IMatrix<Dimensions, DefaultValue>
{
  using Parent = IMatrix<Dimensions, DefaultValue>;
  using Proxy = MatrixProxy<Dimensions, DefaultValue>;

  std::unique_ptr<Proxy> impl_;
 public:
  size_t GetSize() const { return impl_->GetSize(); }
  Parent::Iterator begin() { return impl_->begin(); }
  Parent::ConstIterator begin() const { return impl_->begin(); }
  Parent::Iterator end() { return impl_->end(); }
  Parent::ConstIterator end() const { return impl_->end(); }
  Parent::Raw& operator [](size_t index) { return impl_->operator [](index); }
};
}
