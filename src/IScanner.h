#pragma once

#include <string>

namespace lib
{
class IScanner
{
 public:
  virtual std::string Scan() = 0;
  virtual void SetOutputStream(std::ostream& os) = 0;
  virtual ~IScanner() = default;
};
}
