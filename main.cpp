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
  uint64_t step_size = stoi(argv[1]);

  unique_ptr<IScanner> scanner = make_unique<Scanner>();
  unique_ptr<ITimer> timer = make_unique<Timer>();
  unique_ptr<IParser> parser = make_unique<Parser>();
  unique_ptr<ILogger> logger = make_unique<Logger>();
  unique_ptr<ILogger> printer1 = make_unique<Logger>();
  unique_ptr<ILogger> printer2 = make_unique<Logger>();
  unique_ptr<IController> controller = make_unique<Controller>();

  auto file_output_stream1 = ofstream("./file1"s);
  auto file_output_stream2 = ofstream("./file2"s);

  parser->SetStaticBlockSize(step_size);

  logger->SetOutputStream(cout);
  printer1->SetOutputStream(file_output_stream1);
  printer2->SetOutputStream(file_output_stream2);

  scanner->SetInputStream(cin);

  controller->SetLogger(std::move(logger));
  controller->SetPrinter1(std::move(printer1));
  controller->SetParser(std::move(parser));
  controller->SetTimer(std::move(timer));
  controller->SetScanner(std::move(scanner));

  controller->Execute();

  file_output_stream1.close();
  file_output_stream2.close();

  return EXIT_SUCCESS;
}
