#pragma once

#include "ITimer.h"

namespace lib
{
class Timer : public ITimer
{
 public:
  [[nodiscard]]
  uint64_t GetTime() const override;
};
}
