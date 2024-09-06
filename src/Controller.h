#pragma once

#include "IController.h"

namespace lib
{
class Controller : public IController
{
  std::unique_ptr<ILogger> logger_;
  std::unique_ptr<ILogger> printer_;
  std::unique_ptr<IParser> parser_;
  std::unique_ptr<IScanner> scanner_;
  std::unique_ptr<ITimer> timer_;
 public:
  void SetLogger(std::unique_ptr<ILogger> logger) override;
  void SetPrinter(std::unique_ptr<ILogger> printer) override;
  void SetParser(std::unique_ptr<IParser> parser) override;
  void SetScanner(std::unique_ptr<IScanner> scanner) override;
  void SetTimer(std::unique_ptr<ITimer> timer) override;
  void Execute() override;
};
}
