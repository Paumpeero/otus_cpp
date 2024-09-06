#pragma once

#include "IParser.h"

namespace lib
{
class Parser : public IParser
{
  uint64_t block_size_;
 public:
  std::optional<std::string> Parse(const std::vector<std::string>& scanned_source) override;
  void SetStaticBlockSize(uint64_t size) override;
};
}
