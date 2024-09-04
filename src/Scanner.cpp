#include <iostream>

#include "Scanner.h"

using namespace lib;
using namespace std;

std::string Scanner::Scan()
{
  string ret;

  getline(*is_, ret);

  return ret;
}

void Scanner::SetOutputStream(istream& is)
{
  is_ = &is;
}
