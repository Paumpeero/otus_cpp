#include "src/sdk.h"

#include <boost/asio/signal_set.hpp>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

#include "src/IPParser.h"

using namespace std;
using namespace otus_cpp;

int main()
{
  cout << GetAsIP( int8_t{-1} ) << endl;  // 255
  cout << GetAsIP( int16_t{0} ) << endl;  // 0.0
  cout << GetAsIP( int32_t{2130706433} ) << endl;  // 127.0.0.1
  cout << GetAsIP( int64_t{8875824491850138409} ) << endl; // 123.45.67.89.101.112.131.41
  cout << GetAsIP( std::string{"Hello, World!"} ) << endl; // Hello, World!
  cout << GetAsIP( std::vector<int>{100, 200, 300, 400} ) << endl; // 100.200.300.400
  cout << GetAsIP( std::list<short>{400, 300, 200, 100} ) << endl; // 400.300.200.100
//  GetAsIP( std::make_tuple(123, 456, 789, 0) ); // 123.456.789.0
  return EXIT_SUCCESS;
}
