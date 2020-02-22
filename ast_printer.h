#ifndef AST_PRINTER_HEADER
#define AST_PRINTER_HEADER

#include <string>
#include <iostream>
#include <vector>
#include <sstream>

#include "expr.h"
#include "stmt.h"

std::string test = "test";
class AstPrinter: AbstractExprDispatcher<std::string> {
  private:
    std::string parenthesize(std::string name, std::vector<Expr<std::string>*> exprs) {
      std::stringstream ss;
      ss << " ( ";
      ss << name;
      for(Expr<std::string>* expr : exprs) {
        ss << " " << expr->Accept(this);
      }
      ss << " ) ";
      std::string out = ss.str();
      return out;
    }
  public:
    std::string print(Expr<std::string> * expr) {
      return expr->Accept(this);
    }
    std::string visitBinaryExpr(Binary<std::string>& expr) override {
      std::vector< Expr<std::string>* > exprs;
      exprs.push_back(expr.getLeft());
      exprs.push_back(expr.getRight());
      return parenthesize(expr.getOp().getLexeme(), exprs);
    }
    std::string visitGroupingExpr(Grouping<std::string>& expr) override {
      std::vector< Expr<std::string>* > exprs;
      exprs.push_back(expr.getExpression());
      return parenthesize("group", exprs);
    }
    std::string visitLiteralExpr(Literal<std::string>& expr) override {
      std::stringstream ss;
      std::string actualType = expr.getActualType();
      if (actualType == "double" ) {
        ss << *static_cast<double*>(expr.getValue());
      } else {
        ss << "BAD";
      }

      std::string val = ss.str();
      return val;
    }
    std::string visitUnaryExpr(Unary<std::string>& expr) override {
      std::vector< Expr<std::string>* > exprs;
      exprs.push_back(expr.getRight());
      return parenthesize(expr.getOp().getLexeme(), exprs);
    }

    std::string visitAssignExpr(Assign<std::string>& expr) override {
      return "";
    }
    std::string visitCallExpr(Call<std::string>& expr) override {
      return "";
    }
    std::string visitGetExpr(Get<std::string>& expr)  override{
      return "";
    }
    std::string visitLogicalExpr(Logical<std::string>& expr) {
      return "";
    }
    std::string visitSetExpr(Set<std::string>& expr) override {
      return "";
    }
    std::string visitSuperExpr(Super<std::string>& expr) override {
      return "";
    }
    std::string visitThisExpr(This<std::string>& expr)  override{
      return "";
    }
    std::string visitVariableExpr(Variable<std::string>& expr) override {
      return "";
    }
};

#endif
