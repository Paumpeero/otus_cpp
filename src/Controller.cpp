#include <string>
#include <vector>
#include <fstream>

#include "Controller.h"

using namespace lib;
using namespace std;

void Controller::SetLogger(std::unique_ptr<ILogger> logger)
{
  logger_ = std::move(logger);
}

void Controller::SetPrinter(std::unique_ptr<ILogger> printer)
{
  printer_ = std::move(printer);
}

void Controller::SetParser(std::unique_ptr<IParser> parser)
{
  parser_ = std::move(parser);
}

void Controller::SetScanner(std::unique_ptr<IScanner> scanner)
{
  scanner_ = std::move(scanner);
}

void Controller::SetTimer(std::unique_ptr<ITimer> timer)
{
  timer_ = std::move(timer);
}

void Controller::Execute()
{

}
