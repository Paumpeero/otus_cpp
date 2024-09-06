#include "Logger.h"

using namespace std;
using namespace lib;

void Logger::SetOutputStream(ostream& ostream)
{
  ostream_ = &ostream;
}

void Logger::Log(std::string input_content)
{
  *ostream_ << input_content << endl;
}
