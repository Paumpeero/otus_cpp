#pragma once

#include "IScanner.h"

namespace lib
{
class Scanner final : public IScanner
{
  std::istream* is_;
 public:
  std::string Scan() override;
  void SetOutputStream(std::istream& is) override;
};
}
