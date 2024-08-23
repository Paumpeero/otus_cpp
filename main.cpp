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
  Matrix<int64_t, -1, 1> matrix;
  assert(matrix.GetSize() == 0);
  auto a = matrix[0];
  assert(a == -1);
  matrix[100] = 314;
  assert(matrix[100] == 314);
  assert(matrix[101] == -1);
  assert(matrix.GetSize() == 1);

  auto iter = matrix.begin();
  assert(iter->GetSize() == 1);
  auto result = make_tuple<size_t, int64_t>(100, 314);

  matrix[101] = 311;

  for (auto t : matrix)
  {
    size_t x;
    int64_t val;

    std::tie(x, val) = t;

    cout << "x: "s << x << "\nval: " << val << endl;
  }

  return EXIT_SUCCESS;
}
