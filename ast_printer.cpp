#include <iostream>
#include "ast_printer.h"

int main(int argc, char** argp) {
  Binary<std::string>* expression = new Binary<std::string>(
      new Unary<std::string>(
        *(new Token(MINUS, "-", NULL, 1)),
        new Literal<std::string>(123)),
      *(new Token(STAR, "*", NULL, 1)),
      new Grouping<std::string>(
        new Literal<std::string>(45.67)));
  std::cout << "asdfasdfasdfdsf\n";
  AstPrinter* ast = new AstPrinter();
  std::cout << (ast->print(expression)) << std::endl;
}
