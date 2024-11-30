#include <string>
#include <vector>
#include <fstream>
#include <atomic>
#include <condition_variable>
#include <thread>
#include <shared_mutex>

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
  static string cmd_copy;
  static string parsed_content;
  static shared_mutex mtx;
  static atomic<int> counter = 0;

  cmd_copy = ""s;
  parsed_content = ""s;

  deque<string> dq_of_commands;

  while (true)
  {
    if (!counter) {
      string command = scanner_->Scan();
      cmd_copy = command;
      dq_of_commands.push_back(command);

      printer1_->Log(cmd_copy);
      printer2_->Log(cmd_copy);

      if (auto parsed = parser_->Parse(dq_of_commands))
      {
        parsed_content = parsed.value();
        logger_->Log(parsed_content);
        printer1_->Log(parsed_content);
        printer2_->Log(parsed_content);

        if (command == "EOF"s)
        {
          break;
        }
      }
    }
  }
}
