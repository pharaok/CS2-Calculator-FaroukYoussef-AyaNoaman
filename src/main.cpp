#include "parser.h"
#include <iostream>
#include <string>
using namespace std;

int main() {
  string inp;
  getline(cin, inp);
  cout << compute(inp) << "\n";
}
