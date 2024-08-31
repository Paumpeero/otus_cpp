#include "src/sdk.h"
#include <boost/asio/signal_set.hpp>
#include <iostream>
#include <memory>
#include <mutex>
#include <thread>
#include <vector>
#include "src/matrix.h"

using namespace lib;
using namespace std;

int main()
{
  // бесконечная матрица int заполнена значениями -1
  Matrix<int, -1> matrix;
  assert(matrix.GetSize() == 0); // все ячейки свободны
  auto a = matrix[0][0];
  assert(a == -1);
  assert(matrix.GetSize() == 0);
  matrix[100][100] = 314;
  assert(matrix[100][100] == 314);
  assert(matrix.GetSize() == 1);
// выведется одна строка
// 100100314
  for(const auto& c : matrix)
  {
    int x;
    int y;
    int v;
    std::tie(x, y, v) = c;
    std::cout << x << y << v << std::endl;
  }

  return EXIT_SUCCESS;
}
