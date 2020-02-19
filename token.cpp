#include "token.h"
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include "token_type.h"

std::ostream& operator<<(std::ostream& os, Token& tok) {
  std::stringstream ss;
  ss << "T: " << TokenTypeStrings[tok.getType()] << std::setw(5)
     << "L: " << tok.getLexeme() << " " << tok.getLexeme().size() << std::endl;
  // ss << tok.getLexeme();
  // std::string out;
  // ss >> out;
  return os << ss.str();
}
