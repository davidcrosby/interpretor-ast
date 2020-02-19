#include <iostream>

using namespace std;

void report_error(int line, string where, string message) {
  cout << "[line " << line << "] Error" + where << ": " + message << endl;
}
