#pragma once

#include <vector>
#include <string>

namespace lib
{
class IParser
{
 public:
  virtual std::vector<std::string> Parse(const std::vector<std::string>& scanned_source) = 0;
  virtual ~IParser() = default;
};
}
