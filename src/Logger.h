#pragma once

#include "ILogger.h"

namespace lib
{
class Logger : public ILogger
{
  std::ostream* ostream_;
 public:
  void SetOutputStream(std::ostream& ostream) override;
  void Log(std::vector<std::string> input_content) override;
};
}
