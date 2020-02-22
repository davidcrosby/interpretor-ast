#include <iostream>
#include <string>
#include <typeinfo>
#include "ast_printer.h"

int main(int argc, char** argp) {
  double lit1 = 123;
  double lit2 = 45.67;
  std::string type = typeid(lit1).name();
  Binary<std::string>* expression = new Binary<std::string>(
      new Unary<std::string>(
        *(new Token(MINUS, "-", NULL, 1)),
        new Literal<std::string>(&lit1, type)),
      *(new Token(STAR, "*", NULL, 1)),
      new Grouping<std::string>(
        new Literal<std::string>(&lit2, type)));
  AstPrinter* ast = new AstPrinter();
  std::cout << (ast->print(expression)) << std::endl;
}
