#include "../scanner.h"
#include <iostream>

bool test_scan_tokens_basic_ops() {
  std::cout << "Test scanning basic tokens." << std::endl;
  //std::string source = "{}()*-asdf\n== == <= <= >= {==}";
  //std::string source = "var x = \"asdf\"\nn >= 45 ";
  std::string source = "1234\n1234.4\n1234 123.3 102.29\n";
  Scanner* sc = new Scanner(source);
  std::vector<Token> out = sc->scan_all_tokens();
  for (auto it = out.begin(); it != out.end(); it++) {
    std::cout << *it;
  }
  return false;
}
