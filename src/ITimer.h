#include <cstdint>

namespace lib
{
class ITimer
{
 public:
  virtual uint64_t GetTime() const = 0;
  virtual ~ITimer() = default;
};
}
