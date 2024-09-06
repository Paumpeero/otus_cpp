#pragma once

#include <string>

namespace lib
{
class IScanner
{
 public:
  virtual std::string Scan() = 0;
  virtual void SetInputStream(std::istream& os) = 0;
  virtual ~IScanner() = default;
};
}
