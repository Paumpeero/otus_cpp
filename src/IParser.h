#pragma once

#include <deque>
#include <string>
#include <optional>

namespace lib
{
class IParser
{
 public:
  virtual std::optional<std::string> Parse(std::deque<std::string>& scanned_source) = 0;
  virtual void SetStaticBlockSize(uint64_t size) = 0;
  virtual ~IParser() = default;
};
}
