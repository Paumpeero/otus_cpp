#pragma once

#include <string>

namespace otus_cpp
{
using namespace std;
/**
 * @brief Базовый шаблон для парсинга IP адреса
 * @tparam T Тип источника данных.
 * @param source Источник данных
 * @return Строку, как разобранный IP адрес
 */
template<class T>
string GetAsIP(T source)
{
  return to_string(uint8_t(source));
}

template<>
string GetAsIP<int32_t>(int32_t source)
{
  uint32_t source_as_uint = source;
  uint8_t* source_as_vector = reinterpret_cast<uint8_t*>(&source_as_uint);
  string ret;

  for (uint64_t i = 3; i != uint64_t(-1); --i)
  {
    if (i != 3)
    {
      ret += "."s;
    }
    ret += to_string(source_as_vector[i]);
  }

  return ret;
}

template<>
string GetAsIP<string>(string source) { return source; }

template<>
string GetAsIP<vector<int>>(vector<int> source)
{
  string ret;

  for (int32_t i = 0; i != source.size(); ++i)
  {
    if (i) ret += "."s;

    ret += to_string(source[i]);
  }

  return ret;
}

template<>
string GetAsIP<list<short>>(list<short> source)
{
  string ret;

  for (auto iter = source.begin(), end = source.end(); iter != end; ++iter)
  {
    if (iter != source.begin()) ret += "."s;

    ret += to_string(*iter);
  }

  return ret;
}
template<>
string GetAsIP<tuple<int, int, int, int>>(tuple<int, int, int, int> source)
{
  string ret;

  ret += to_string(get<0>(source));
  ret += "."s;
  ret += to_string(get<1>(source));
  ret += "."s;
  ret += to_string(get<2>(source));
  ret += "."s;
  ret += to_string(get<3>(source));

  return ret;
}
}
