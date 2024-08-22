#include <array>
#include <memory>

namespace lib
{
using namespace std::string_literals;

template<class T, T Default, size_t DimensionsCount, class Dimension = size_t, class... Dimensions>
class Matrix
{

};

template<class T, T Default>
class Matrix<T, Default, 1, size_t>
{

};
}
