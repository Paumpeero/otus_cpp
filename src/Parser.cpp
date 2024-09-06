//
// Created by Антон on 06.09.2024.
//

#include "Parser.h"

using namespace lib;
using namespace std;

optional<string> Parser::Parse(const vector<string>& scanned_source)
{
  return nullopt;
}

void Parser::SetStaticBlockSize(uint64_t size)
{
  block_size_ = size;
}
