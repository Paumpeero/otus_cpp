#pragma once

#include "IController.h"

namespace lib
{
class Controller : public IController
{
  std::unique_ptr<ILogger> logger_;
  std::unique_ptr<ILogger> printer1_;
  std::unique_ptr<ILogger> printer2_;
  std::unique_ptr<IParser> parser_;
  std::unique_ptr<IScanner> scanner_;
  std::unique_ptr<ITimer> timer_;

  std::string cmd_copy;
  std::string parsed_content;
  std::shared_mutex mtx;
  std::atomic<int> counter = 0;
  constexpr static int kMaxCounter = 2;
 public:
  void SetLogger(std::unique_ptr<ILogger> logger) override;
  void SetPrinter1(std::unique_ptr<ILogger> printer) override;
  void SetPrinter2(std::unique_ptr<ILogger> printer) override;
  void SetParser(std::unique_ptr<IParser> parser) override;
  void SetScanner(std::unique_ptr<IScanner> scanner) override;
  void SetTimer(std::unique_ptr<ITimer> timer) override;
  void Execute() override;
};
}
