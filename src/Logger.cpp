#include "Logger.h"

using namespace std;
using namespace lib;

void Logger::SetOutputStream(ostream& ostream)
{
  ostream_ = &ostream;
}

void Logger::Log(std::string input_content)
{
  for (auto& chunk : input_content)
  {
    *ostream_ << chunk << endl;
  }
}
