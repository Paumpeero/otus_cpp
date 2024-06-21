#include "src/sdk.h"
//
#include <boost/asio/signal_set.hpp>
#include <boost/log/trivial.hpp>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

using namespace std;

int main()
{
  BOOST_LOG_TRIVIAL(error) << "GET" << " /api/v1/config" << endl;

  return EXIT_SUCCESS;
}
