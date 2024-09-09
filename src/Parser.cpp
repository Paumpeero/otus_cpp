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
    deque<string> ctx;

    for (const auto& cmd: scanned_source)
    {
      if (cmd == "{"s)
      {
        ctx.push_back(cmd);
      }

      if (cmd == "}"s)
      {
        ctx.pop_front();
      }

      if (cmd == "EOF"s)
      {
        if (ctx.size())
        {
          std::terminate();
        }

        scanned_source.pop_front();
        break;
      }

      ret += " "s + cmd;
      scanned_source.pop_front();
    }

    return ret;
  }

  auto dynamic_block = find(scanned_source.begin(),
                            scanned_source.end(),
                            "{"s);

  if (scanned_source.size() == block_size_)
  {
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

  if (dynamic_block != scanned_source.end())
  {
    deque<string> ctx;
    deque<string> dq_of_commands;

    for (const auto& command : scanned_source)
    {
      if (command == "{"s)
      {
        ctx.push_back(command);
        if (ctx.size() == 1 && dq_of_commands.size())
        {
          string ret = "bulk:"s;

          while (dq_of_commands.size())
          {
            ret += " "s + dq_of_commands.at(0);
            dq_of_commands.pop_front();
            scanned_source.pop_front();
          }

          return ret;
        }
        continue;
      }
      if (command == "}"s)
      {
        ctx.pop_back();

        if (ctx.empty())
        {
          string ret = "bulk:"s;

          while (dq_of_commands.size())
          {
            ret += " "s + dq_of_commands.at(0);
            dq_of_commands.pop_front();
          }

          while (scanned_source.size())
          {
            scanned_source.pop_front();
          }

          return ret;
        }
        continue;
      }

      if (command != "{"s && command != "}"s)
      {
        dq_of_commands.push_back(command);
      }
    }
  }

  return nullopt;
}

void Parser::SetStaticBlockSize(uint64_t size)
{
  block_size_ = size;
}
