#include <chrono>

#include "Timer.h"

using namespace std;
using namespace lib;

uint64_t Timer::GetTime() const
{
  auto now = chrono::steady_clock::now().time_since_epoch();

  return now.count();
}
