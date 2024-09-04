#pragma once

#include <vector>
#include <string>

namespace lib
{
class IParser
{
 public:
  virtual std::optional<std::string> Parse(std::vector<std::string>& scanned_source) = 0;
  virtual ~IParser() = default;
};
}
