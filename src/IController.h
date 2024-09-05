#pragma once

#include <memory>

#include "IParser.h"
#include "IScanner.h"
#include "ITimer.h"

namespace lib
{
class IController
{
 public:
  virtual void SetParser(std::unique_ptr<IParser> parser) = 0;
  virtual void SetScanner(std::unique_ptr<IScanner> scanner) = 0;
  virtual void SetTimer(std::unique_ptr<ITimer> timer) = 0;
  virtual void Execute() = 0;
  virtual ~IController() = default;
};
}
