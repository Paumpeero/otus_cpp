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
  deque<string> dq_of_commands;

  jthread printer1_worker([this]()
                         {
                           while (true)
                           {
                             if (counter)
                             {
                               shared_lock<shared_mutex> lock(mtx);
                               printer1_->Log(cmd_copy);
                               if (!parsed_content.empty())
                               {
                                 printer1_->Log(parsed_content);
                               }

                               if (cmd_copy == "EOF"s)
                               {
                                 --counter;
                                 break;
                               }
                               --counter;
                             }
                           }
                         });

  while (true)
  {
    if (!counter)
    {
      parsed_content = ""s;
      unique_lock<shared_mutex> mtx;
      cmd_copy = scanner_->Scan();
      dq_of_commands.push_back(cmd_copy);

      printer2_->Log(cmd_copy);

      if (auto parsed = parser_->Parse(dq_of_commands))
      {
        parsed_content = parsed.value();
        logger_->Log(parsed_content);
        printer2_->Log(parsed_content);

        if (cmd_copy == "EOF"s)
        {
          counter = kMaxCounter;
          break;
        }
      }
      counter = kMaxCounter;
    }
  }
}
