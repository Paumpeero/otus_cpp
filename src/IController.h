#pragma once

#include <memory>

#include "IParser.h"
#include "IScanner.h"

namespace lib
{
class IController
{
 public:
  virtual void SetParser(std::unique_ptr<IParser> parser) = 0;
  virtual void SetScanner(std::unique_ptr<IScanner> scanner) = 0;
  virtual void Execute() = 0;
  virtual ~IController() = default;
};
}
