#include <iostream>
#include <vector>
#include <string>

namespace lib
{
class ILogger
{
 public:
  virtual void SetOutputStream(std::ostream& ostream) = 0;
  virtual void Log(std::vector<std::string> input_content) = 0;
  virtual ~ILogger() = default;
};
}
