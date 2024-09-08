#include <algorithm>

#include "Parser.h"

using namespace lib;
using namespace std;

optional<string> Parser::Parse(std::deque<std::string>& scanned_source)
{
  auto eof_iter = find(scanned_source.begin(),
                       scanned_source.end(),
                       "EOF"s);
  bool has_eof = eof_iter != scanned_source.end();

  if (has_eof)
  {
    string ret = "bulk:"s;

    for (const auto& cmd: scanned_source)
    {
      if (cmd == "EOF"s)
      {
        scanned_source.pop_front();
        break;
      }

      ret += " "s + cmd;
      scanned_source.pop_front();
    }

    return ret;
  }

  if (scanned_source.size() == block_size_)
  {
    auto dynamic_block = find(scanned_source.begin(),
                              scanned_source.end(),
                              "{"s);

    if (dynamic_block == scanned_source.end())
    {
      string ret = "bulk:"s;

      for (const auto& cmd: scanned_source)
      {
        ret += " "s + cmd;
        scanned_source.pop_front();
      }

      return ret;
    }
  }

  return nullopt;
}

void Parser::SetStaticBlockSize(uint64_t size)
{
  block_size_ = size;
}
