#include "scanner.h"
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <exception>
#include "error_handler.h"
#include "token.h"
#include "token_type.h"

std::unordered_map<std::string, TokenType> keyword_token_type_mapping = {
    {"and", AND},     {"and", AND},   {"class", CLASS}, {"else", ELSE},
    {"false", FALSE}, {"for", FOR},   {"fun", FUN},     {"if", IF},
    {"nil", NIL},     {"or", OR},     {"print", PRINT}, {"return", RETURN},
    {"super", SUPER}, {"this", THIS}, {"true", TRUE},   {"var", VAR},
    {"while", WHILE}};

Scanner::~Scanner() {
  // tokens.erase(0, source.size());
}

char Scanner::advance() {
  return source[current++];
}

void Scanner::add_token(TokenType type) {
  tokens.push_back( *(new Token(type, "", NULL, line) ));
}

void Scanner::add_token(TokenType type, double number) {
  std::stringstream ss;
  ss << number;
  tokens.push_back(* (new Token(type, ss.str(), &number, line)));
}

void Scanner::add_token(TokenType type, void* literal) {
  std::string text = source.substr(start, current - start);
  tokens.push_back(*(new Token(type, text, literal, line)));
}

bool Scanner::advance_ifequals(char c) {
  if (end_of_source())
    return false;
  if (peek() != c)
    return false;
  current++;
  return true;
}

char Scanner::peek() {
  if (end_of_source())
    return '\0';
  return source[current];
}

char Scanner::peek_next() {
  if (current + 1 >= source.size())
    return '\0';
  return source[current + 1];
}

bool is_alpha(char byte) {
  return (byte >= 'a' && byte <= 'z') || (byte >= 'A' && byte <= 'Z') ||
         byte == '_';
}

bool is_digit(char byte) {  // UTIL
  return '0' <= byte && byte <= '9';
}

bool is_alpha_numeric(char byte) {
  return is_alpha(byte) || is_digit(byte);
}

void Scanner::parse_string_token() {
  while (!end_of_source() && peek() != '"') {
    if (peek() == '\n')
      line++;
    advance();
  }

  if (end_of_source()) {
    report_error(line, "Scanner", "Unterminated string");
  }

  advance();  // Closing quote
  std::string returnValue = source.substr(start + 1, current - start - 2);
  add_token(STRING, &returnValue);
}

void Scanner::parse_number_token() {
  while (!end_of_source() && is_digit(peek())) {
    advance();
  }

  if (peek() == '.' && is_digit(peek_next())) {
    advance();
    while (!end_of_source() && is_digit(peek())) {
      advance();
    }
  }
  double value = std::stod(source.substr(start, current - start + 1));
  add_token(NUMBER, value);
}

void Scanner::parse_identifier() {
  while (is_alpha_numeric(peek())) advance();
  std::string identifier = source.substr(start, current - start);
  auto type = keyword_token_type_mapping.find(identifier);
  if(type == keyword_token_type_mapping.end())
    report_error(line, "", "Cannot recognize idenitifer.");
  else
    add_token(type->second);
}

void Scanner::scan_next_token() {
  char byte = advance();
  switch (byte) {
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
      add_token(advance_ifequals('=') ? BANG_EQUAL : BANG);
      break;
    case '=':
      add_token(advance_ifequals('=') ? EQUAL_EQUAL : EQUAL);
      break;
    case '<':
      add_token(advance_ifequals('=') ? LESS_EQUAL : LESS);
      break;
    case '>':
      add_token(advance_ifequals('=') ? GREATER_EQUAL : GREATER);
      break;

    // NORMAL SINGLE CHAR OPS
    case '(':
      add_token(LEFT_PAREN);
      break;
    case ')':
      add_token(RIGHT_PAREN);
      break;
    case '{':
      add_token(LEFT_BRACE);
      break;
    case '}':
      add_token(RIGHT_BRACE);
      break;
    case ',':
      add_token(COMMA);
      break;
    case '.':
      add_token(DOT);
      break;
    case '-':
      add_token(MINUS);
      break;
    case '+':
      add_token(PLUS);
      break;
    case ';':
      add_token(SEMICOLON);
      break;
    case '*':
      add_token(STAR);
      break;
    case '/':
      add_token(SLASH);
      break;
    case '"':
      parse_string_token();
      break;
    case '#':  // comment
      while (peek() != '\n' && !end_of_source())
        advance();
      line++;
      break;
    default:
      if (is_digit(byte)) {
        parse_number_token();
        break;
      } else if (is_alpha_numeric(byte)) {
        parse_identifier();
        break;
      }
      report_error(line, "Scanner", "Unexpected character.");
      break;
  }
  return;
}

bool Scanner::end_of_source() {
  return current > source.size();
}

std::vector<Token> Scanner::scan_all_tokens() {
  while (!end_of_source()) {
    start = current;
    scan_next_token();
  }
  tokens.push_back(*(new Token(END_OF_FILE, "", NULL, line)));
  return tokens;
}
