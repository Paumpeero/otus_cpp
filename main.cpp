#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main(int argc, char const* argv[])
{
  int a = 1;
  int& b = a;

  decltype(auto) c = b;

  c = 455;

  cout << c;
  return 0;
}
