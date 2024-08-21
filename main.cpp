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
  constexpr int64_t kDefault = -1;
  constexpr size_t kDimensionsCount = 1;
  Matrix<int64_t, kDefault, kDimensionsCount> matrix;

  return EXIT_SUCCESS;
}
