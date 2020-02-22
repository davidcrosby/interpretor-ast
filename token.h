#ifndef TOKEN_CLASS_HEADER
#define TOKEN_CLASS_HEADER

#include <any>
#include <iostream>
#include <string>
#include "token_type.h"

class Token {
 private:
  TokenType type;
  std::string lexeme;
  void* literal;
  unsigned long line;

 public:
  Token(TokenType _type,
        std::string _lexeme,
        void* _literal,
        unsigned long _line)
      : type(_type), lexeme(_lexeme), literal(_literal), line(_line) {}
  Token(TokenType _type) : type(_type) {}
  TokenType getType() { return type; }
  std::string getLexeme() { return lexeme; }
  std::any getLiteral() { return literal; }
  unsigned long getLineNumber() { return line; }
  friend std::ostream& operator<<(std::ostream& os, Token& tok);
};

#endif
