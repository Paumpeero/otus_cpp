#include <array>
#include <memory>

namespace lib
{
using namespace std::string_literals;

template<class T, T Default, size_t DimensionsCount, class Dimension, class... Dimensions>
class IMatrix;

template<class T, T Default, size_t DimensionsCount, class Dimension = size_t, class... Dimensions>
class IMatrixIter
{
 protected:
  using Matrix = IMatrix<T, Default, DimensionsCount, Dimension, Dimensions...>;
 public:
  virtual Matrix* operator ->() = 0;
  virtual ~IMatrixIter() = default;
};

template<class T, T Default, size_t DimensionsCount, class Dimension = size_t, class... Dimensions>
class IMatrix
{
 protected:
  using Cell = IMatrix<T, Default, DimensionsCount - 1, Dimensions...>;
  using Iter = IMatrixIter<T, Default, DimensionsCount, Dimension, Dimensions...>;
 public:
  virtual Iter begin() = 0;
  virtual Iter end() = 0;
  virtual ~IMatrix() = default;
};
}
