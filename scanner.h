#ifndef SCANNER_CLASS_HEADER
#define SCANNER_CLASS_HEADER

#include <vector>
#include "token.h"

class Scanner {
  private:
    std::string source;
    std::vector<Token> tokens;
    unsigned long current;
  public:
    Scanner (std::string _source): source(_source) {}
    std::vector<Token> scanAllTokens();
    void scanNextToken();
    bool atEnd() { return current == source.length()-1; }
};
#endif
