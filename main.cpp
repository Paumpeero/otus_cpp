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
  unique_ptr<IMatrix<int64_t, -1, 1>> matrix = make_unique<Matrix<int64_t, -1>>();

  return EXIT_SUCCESS;
}
