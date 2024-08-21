#include <array>
#include <memory>

namespace lib
{
using namespace std::string_literals;

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
  [[nodiscard]]
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
class IMatrix<T, Default, 1>
{
 protected:
  using Cell = std::tuple<size_t, T>;
  using Iter = IMatrixIterator<T, Default, 1, size_t>;
  using ConstIter = const Iter;
 public:
  [[nodiscard]]
  virtual size_t GetSize() const = 0;
  virtual T& operator [](size_t index) = 0;
  virtual T& At(size_t d) = 0;
  virtual Iter begin() = 0;
  virtual ConstIter begin() const = 0;
  virtual ConstIter cbegin() const = 0;
  virtual Iter end() = 0;
  virtual ConstIter end() const = 0;
  virtual ConstIter cend() const = 0;
  virtual ~IMatrix() = default;
};

template<
  class T,
  T Default
>
class IMatrixIterator<T, Default, 1>
{
 protected:
  using Cell = std::tuple<size_t, T>;
  using Matrix = IMatrix<T, Default, 1, size_t>;
 public:
  virtual Matrix& GetMatrix() const = 0;
  virtual Cell operator *() = 0;
  virtual Matrix* operator ->() = 0;
  virtual IMatrixIterator& operator ++() = 0;
  virtual IMatrixIterator operator ++(int) = 0;
  virtual bool operator ==(const IMatrixIterator& iter) const = 0;
  virtual bool operator !=(const IMatrixIterator& iter) const = 0;
  virtual ~IMatrixIterator() = default;
};

template<class T, T Default>
class MatrixImpl final : public IMatrix<T, Default, 1>
{
  using Interface = IMatrix<T, Default, 1>;
  std::unordered_map<uint64_t, T> indexes_to_values_;
 public:
  [[nodiscard]]
  size_t GetSize() const override { return indexes_to_values_.size(); }
  T& operator [](size_t index)
  {
    if (!indexes_to_values_.count(index))
    {
      indexes_to_values_[index] = Default;
    }

    return indexes_to_values_[index];
  }
  T& At(size_t d) override { return indexes_to_values_.at(d); }
  Interface::Iter begin() override {}
  Interface::ConstIter begin() const override {}
  Interface::ConstIter cbegin() const override {}
  Interface::Iter end() override {}
  Interface::ConstIter end() const override {}
  Interface::ConstIter cend() const override {}
};

template<class T, T Default>
class Matrix final : public IMatrix<T, Default, 1>
{
  using Interface = IMatrix<T, Default, 1>;
  using Implementation = MatrixImpl<T, Default>;

  std::unique_ptr<Interface> impl_ = std::make_unique<Implementation>();
 public:
  [[nodiscard]]
  size_t GetSize() const override { return impl_->GetSize(); }
  T& operator [](size_t index) override { return impl_->operator [](index); }

  T& At(size_t d) override
  {
    if (!GetSize()) ThrowEmptyMatrixError();

    return impl_->At(d);
  }

  Interface::Iter begin() override
  {
    if (!GetSize()) ThrowEmptyMatrixError();

    return impl_->begin();
  }

  Interface::ConstIter begin() const override
  {
    if (!GetSize()) ThrowEmptyMatrixError();

    return impl_->cbegin();
  }

  Interface::ConstIter cbegin() const override
  {
    if (!GetSize()) ThrowEmptyMatrixError();

    return impl_->cbegin();
  }

  Interface::Iter end() override { return impl_->end(); }
  Interface::ConstIter end() const override { return impl_->cend(); }
  Interface::ConstIter cend() const override { return impl_->cend(); }

 private:
  void ThrowEmptyMatrixError()
  {
    throw std::runtime_error("Current matrix is empty"s);
  }
};
}
