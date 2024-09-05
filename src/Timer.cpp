#include <chrono>

#include "Timer.h"

using namespace std;
using namespace lib;

uint64_t Timer::GetTime() const
{
  auto now = chrono::system_clock::now().time_since_epoch();
  auto now_nanoseconds = chrono::duration_cast<chrono::nanoseconds>(now);

  return now_nanoseconds.count();
}
