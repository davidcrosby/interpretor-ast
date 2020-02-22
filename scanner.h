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
  std::vector<Token> scan_all_tokens();
  void scan_next_token();
  bool end_of_source();
  char advance();
  void add_token(TokenType type);
  void add_token(TokenType type, void* literal);
  void add_token(TokenType type, double number);
  bool advance_ifequals(char c);
  char peek();
  char peek_next();
  void parse_string_token();
  void parse_number_token();
  void parse_identifier();
  ~Scanner();
};
#endif
