#ifndef SCANNER_CLASS_HEADER
#define SCANNER_CLASS_HEADER

#include <any>
#include <vector>
#include "token.h"
#include "token_type.h"

class Scanner {
 private:
  std::string source;
  std::vector<Token> tokens;
  unsigned long current = 0;
  unsigned long start = 0;
  unsigned long line = 1;

 public:
  Scanner(std::string _source) : source(_source) {}
  std::vector<Token> scanAllTokens();
  void scanNextToken();
  bool atEnd();
  char advance();
  void addToken(TokenType type);
  void addToken(TokenType type, std::any literal);
  bool advanceIfNextEquals(char c);
  char peek();
  void parseStringToken();
  ~Scanner();
};
#endif
