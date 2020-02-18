#ifndef TOKEN_CLASS_HEADER
#define TOKEN_CLASS_HEADER

#include <any>
#include <string>
#include "token_type.h"

class Token {
  private:
    TokenType type;
    std::string lexeme;
    std::any literal;
    int line;
  public:
    Token(TokenType _type): type(_type) {}
    TokenType getType() { return type; }
    std::string getLexeme() { return lexeme; }
    std::any getLiteral() { return literal; }
    int getLineNumber() { return line; }
    std::string toString() {
      // TODO: Display literal
      return std::to_string(type) + " " + lexeme;
    }
};

#endif
