#include <vector>
#include "scanner.h"
#include "token.h"
#include "token_type.h"

Scanner::~Scanner() {
  //tokens.erase(0, source.size());
}

char Scanner::advance() {
  return source[current++];
}

void Scanner::addToken(TokenType type) {
  addToken(type, NULL);
}

void Scanner::addToken(TokenType type, std::any literal) {
  std::string text = source.substr(start, current);
  tokens.push_back(*(new Token(type, text, literal, line)));
}

void Scanner::scanNextToken() {
  char c = advance();
  switch(c) {
    case '(': addToken(LEFT_PAREN); break;
    case ')': addToken(RIGHT_PAREN); break;
    case '{': addToken(LEFT_BRACE); break;
    case '}': addToken(RIGHT_BRACE); break;
    case ',': addToken(COMMA); break;
    case '.': addToken(DOT); break;
    case '-': addToken(MINUS); break;
    case '+': addToken(PLUS); break;
    case ';': addToken(SEMICOLON); break;
    case '*': addToken(STAR); break;
  }
  return;
}

bool Scanner::atEnd() {
  return current > source.size();
}

std::vector<Token> Scanner::scanAllTokens() {
  while (!atEnd()) {
    start = current;
    scanNextToken();
  }
  tokens.push_back(*(new Token(END_OF_FILE, "", NULL, line)));
  return tokens;
}
