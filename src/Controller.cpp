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

void Controller::SetPrinter1(std::unique_ptr<ILogger> printer)
{
  printer1_ = std::move(printer);
}

void Controller::SetPrinter2(std::unique_ptr<ILogger> printer)
{
  printer2_ = std::move(printer);
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
  deque<string> dq_of_commands;

  while (true)
  {
    string command = scanner_->Scan();
    dq_of_commands.push_back(command);

    printer1_->Log(command);

    try
    {
      if (auto parsed = parser_->Parse(dq_of_commands))
      {
        logger_->Log(*parsed);
        printer1_->Log(*parsed);

        if (command == "EOF"s)
        {
          break;
        }
      }
    }
    catch (const runtime_error& err)
    {
      break;
    }
  }
}
