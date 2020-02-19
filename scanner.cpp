#include "scanner.h"
#include <iostream>
#include <vector>
#include "error_handler.h"
#include "token.h"
#include "token_type.h"

Scanner::~Scanner() {
  // tokens.erase(0, source.size());
}

char Scanner::advance() {
  return source[current++];
}

void Scanner::addToken(TokenType type) {
  addToken(type, NULL);
}

void Scanner::addToken(TokenType type, std::any literal) {
  std::string text = source.substr(start, current - start);
  tokens.push_back(*(new Token(type, text, literal, line)));
}

bool Scanner::advanceIfNextEquals(char c) {
  if (atEnd())
    return false;
  if (peek() != c)
    return false;
  current++;
  return true;
}

char Scanner::peek() {
  if (atEnd())
    return '\0';
  return source[current];
}

void Scanner::parseStringToken() {
  while (peek() != '"' && !atEnd()) {
    if (peek() == '\n')
      line++;
    advance();
  }

  if (atEnd()) {
    report_error(line, "Scanner", "Unterminated string");
  }

  advance();  // Closing "
  std::string returnValue = source.substr(start, current - start);
  addToken(STRING, returnValue);
}

void Scanner::scanNextToken() {
  char c = advance();
  switch (c) {
    case ' ':
      break;
    case '\r':
      break;
    case '\t':
      break;
    case '\n':
      line++;
      break;

    // LOGICAL OPS
    case '!':
      addToken(advanceIfNextEquals('=') ? BANG_EQUAL : BANG);
      break;
    case '=':
      addToken(advanceIfNextEquals('=') ? EQUAL_EQUAL : EQUAL);
      break;
    case '<':
      addToken(advanceIfNextEquals('=') ? LESS_EQUAL : LESS);
      break;
    case '>':
      addToken(advanceIfNextEquals('=') ? GREATER_EQUAL : GREATER);
      break;

    // NORMAL SINGLE CHAR OPS
    case '(':
      addToken(LEFT_PAREN);
      break;
    case ')':
      addToken(RIGHT_PAREN);
      break;
    case '{':
      addToken(LEFT_BRACE);
      break;
    case '}':
      addToken(RIGHT_BRACE);
      break;
    case ',':
      addToken(COMMA);
      break;
    case '.':
      addToken(DOT);
      break;
    case '-':
      addToken(MINUS);
      break;
    case '+':
      addToken(PLUS);
      break;
    case ';':
      addToken(SEMICOLON);
      break;
    case '*':
      addToken(STAR);
      break;
    case '/':
      addToken(SLASH);
      break;
    case '#':  // comment
      while (peek() != '\n' && !atEnd())
        advance();
      line++;
      break;
    default:
      report_error(line, "Scanner", "Unexpected character.");
      break;
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
