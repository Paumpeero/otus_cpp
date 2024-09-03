#pragma once

#include <vector>
#include <string>

namespace lib
{
class IScanner
{
 public:
  virtual std::vector<std::string> Scan() = 0;
  virtual ~IScanner() = default;
};
}
