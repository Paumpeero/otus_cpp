#include "src/sdk.h"
//
#include <boost/asio/signal_set.hpp>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

#include "src/IParser.h"
#include "src/Scanner.h"

using namespace std;
using namespace lib;

int main(int argc, char** argv)
{
  unique_ptr<IScanner> scanner = make_unique<Scanner>();

  scanner->SetOutputStream(cin);

  while (true)
  {
    cout << scanner->Scan() << endl;
  }

  return EXIT_SUCCESS;
}
