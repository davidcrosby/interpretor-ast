#include <iostream>
#include "../scanner.h"


bool test_scan_tokens_basic_ops() {
  std::cout << "Test scanning basic tokens." << std::endl;
  std::string source = "{}()*-alskdjfasdf";
  Scanner* sc = new Scanner(source);
  std::vector<Token> out = sc->scanAllTokens();
  for(auto it=out.begin(); it != out.end(); it++) {
    std::cout << *it;
  }
  return false;
}