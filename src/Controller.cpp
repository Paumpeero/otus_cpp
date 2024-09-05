#include <string>
#include <vector>

#include "Controller.h"

using namespace lib;
using namespace std;

void Controller::SetLogger(std::unique_ptr<ILogger> logger)
{
  logger_ = std::move(logger);
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
  string current_command;
  vector<string> v_of_commands;

  while (true)
  {
    current_command = scanner_->Scan();
    v_of_commands.push_back(current_command);
    if (auto printed = parser_->Parse(v_of_commands))
    {
      logger_->Log(*printed);

      if (*printed == "EOF"s)
      {
        break;
      }
    }
  }
}
