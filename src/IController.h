#pragma once

#include <memory>

#include "ILogger.h"
#include "IParser.h"
#include "IScanner.h"
#include "ITimer.h"

namespace lib
{
class IController
{
 public:
  virtual void SetLogger(std::unique_ptr<ILogger> logger) = 0;
  virtual void SetPrinter1(std::unique_ptr<ILogger> printer) = 0;
  virtual void SetPrinter2(std::unique_ptr<ILogger> printer) = 0;
  virtual void SetParser(std::unique_ptr<IParser> parser) = 0;
  virtual void SetScanner(std::unique_ptr<IScanner> scanner) = 0;
  virtual void SetTimer(std::unique_ptr<ITimer> timer) = 0;
  virtual void Execute() = 0;
  virtual ~IController() = default;
};
}
