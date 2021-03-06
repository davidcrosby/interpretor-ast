#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "token.h"
#include "token_type.h"
#include "scanner.h"

using namespace std;

bool GLOBAL_HAD_ERROR = false;

char* read_file_into_byte_array(const char* path, int* length) {
  ifstream fl(path);
  fl.seekg(0, ios::end);
  size_t len = fl.tellg();
  char* ret = new char[len];
  fl.seekg(0, ios::beg);
  fl.read(ret, len);
  fl.close();
  *length = len;
  return ret;
}

vector<string> tokenize_string(string target) {
  vector<string> tokens;
  stringstream target_stream(target);
  string intermediate;
  while (getline(target_stream, intermediate, ' ')) {
    tokens.push_back(intermediate);
  }
  return tokens;
}

void run(string source_code) {
  Scanner* scanner = new Scanner(source_code);
  vector<Token> tokens = scanner->scan_all_tokens();
  for (auto it = tokens.begin(); it != tokens.end(); it++) {
    cout << *it;
  }
}

void run_file(char* path) {
  int length = 0;
  char* bytes_of_file = read_file_into_byte_array(path, &length);
  string file(bytes_of_file);
  run(file);
}

void run_interactive_shell() {
  string current_line;
  while (1) {
    cout << "$ ";
    getline(cin, current_line);
    run(current_line);
  }
}

int main(int argc, char** argp) {
  if (argc > 2) {
    cout << "Usage: meh [script]" << endl;
  } else if (argc == 2) {
    run_file(argp[1]);
  } else {
    run_interactive_shell();
    return 1;
  }
}
