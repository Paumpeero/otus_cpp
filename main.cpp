#include "src/sdk.h"
//
#include <boost/asio/signal_set.hpp>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>
#include <fstream>

#include "src/Scanner.h"
#include "src/Timer.h"
#include "src/Parser.h"
#include "src/Logger.h"
#include "src/Controller.h"

using namespace std;
using namespace lib;

int main(int argc, char** argv)
{
  unique_ptr<IScanner> scanner = make_unique<Scanner>();
  unique_ptr<ITimer> timer = make_unique<Timer>();
  unique_ptr<IParser> parser = make_unique<Parser>();
  unique_ptr<ILogger> logger = make_unique<Logger>();
  unique_ptr<ILogger> printer = make_unique<Logger>();
  unique_ptr<IController> controller = make_unique<Controller>();

  auto file_output_stream = ofstream("./bulk_"s + to_string(timer->GetTime()));

  logger->SetOutputStream(cout);
  printer->SetOutputStream(file_output_stream);

  logger->Log("Qwerty"s);
  printer->Log("Qwerty"s);

  file_output_stream.close();

  return EXIT_SUCCESS;
}
