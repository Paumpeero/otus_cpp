#include <array>
#include <memory>

namespace lib
{
template<
  class T,
  T Default,
  size_t DimensionsCount,
  class Dimension,
  class... Dimensions
>
class IMatrix;

template<
  class T,
  T Default,
  size_t DimensionsCount,
  class Dimension = size_t,
  class... Dimensions
>
class IMatrixIterator
{
  using Cell = std::tuple<Dimension, Dimensions..., T>;
  using Matrix = IMatrix<T, Default, DimensionsCount, Dimension, Dimensions...>;
 public:
  virtual Matrix& GetMatrix() const = 0;
  virtual Cell operator *() = 0;
  virtual IMatrixIterator* operator ->() = 0;
  virtual IMatrixIterator& operator ++() = 0;
  virtual IMatrixIterator operator ++(int) = 0;
  virtual bool operator ==(const IMatrixIterator& iter) const = 0;
  virtual bool operator !=(const IMatrixIterator& iter) const = 0;
  virtual ~IMatrixIterator() = default;
};

template<
  class T,
  T Default,
  size_t DimensionsCount,
  class Dimension = size_t,
  class... Dimensions
>
class IMatrix
{
 protected:
  using ILowerMatrix = IMatrix<T, Default, DimensionsCount - 1, Dimensions...>;
  using Cell = std::tuple<Dimension, Dimensions..., T>;
  using Iter = IMatrixIterator<T, Default, DimensionsCount, Dimension, Dimensions...>;
  using ConstIter = const Iter;
 public:
  virtual size_t GetSize() const = 0;
  virtual ILowerMatrix& operator [](size_t index) = 0;
  virtual Cell At(Dimension d, Dimensions... ds) = 0;
  virtual Iter begin() = 0;
  virtual ConstIter begin() const = 0;
  virtual ConstIter cbegin() const = 0;
  virtual Iter end() = 0;
  virtual ConstIter end() const = 0;
  virtual ConstIter cend() const = 0;
  virtual ~IMatrix() = default;
};

template<class T, T Default>
class IMatrix<T, Default, 1, size_t>
{
 protected:
  using ILowerMatrix = IMatrix<T, Default, 1>;
  using Cell = std::tuple<size_t, T>;
  using Iter = IMatrixIterator<T, Default, 1, size_t>;
  using ConstIter = const Iter;
 public:
  virtual size_t GetSize() const = 0;
  virtual ILowerMatrix& operator [](size_t index) = 0;
  virtual Cell At(size_t d) = 0;
  virtual Iter begin() = 0;
  virtual ConstIter begin() const = 0;
  virtual ConstIter cbegin() const = 0;
  virtual Iter end() = 0;
  virtual ConstIter end() const = 0;
  virtual ConstIter cend() const = 0;
  virtual ~IMatrix() = default;
};
}
