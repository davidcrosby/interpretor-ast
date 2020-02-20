#ifndef Stmt_HEADER_AUTO_GEN
#define Stmt_HEADER_AUTO_GEN
#include "token.h"
#include "expr.h"
#include <vector>
class Block;
class Class;
class Expression;
class Function;
class If;
class Print;
class Return;
class Var;
class While;
class AbstractStmtDispatcher {
  public:
    virtual void Dispatch(Block Expr) = 0;
    virtual void Dispatch(Class Expr) = 0;
    virtual void Dispatch(Expression Expr) = 0;
    virtual void Dispatch(Function Expr) = 0;
    virtual void Dispatch(If Expr) = 0;
    virtual void Dispatch(Print Expr) = 0;
    virtual void Dispatch(Return Expr) = 0;
    virtual void Dispatch(Var Expr) = 0;
    virtual void Dispatch(While Expr) = 0;
};
class Stmt {
  public:
    virtual void Accept(AbstractStmtDispatcher dispatcher) = 0;
    virtual ~Stmt() = 0;
};




class Block: public Stmt {
  private:
    std::vector<Stmt*> statements;
  public:
    Block( std::vector<Stmt*> _statements ): statements(_statements) {}
    std::vector<Stmt*> getStatements() { return Statements; }
    void Accept(AbstractStmtDispatcher dispatcher) override {
      dispatcher.Dispatch(*this);
    }
};

class Class: public Stmt {
  private:
    Token name;
    Variable superclass;
    std::vector<Function> methods;
  public:
    Class( Token _name, Variable _superclass, std::vector<Function> _methods ): name(_name), superclass(_superclass), methods(_methods) {}
    Token getName() { return Name; }
    Variable getSuperclass() { return Superclass; }
    std::vector<Function> getMethods() { return Methods; }
    void Accept(AbstractStmtDispatcher dispatcher) override {
      dispatcher.Dispatch(*this);
    }
};

class Expression: public Stmt {
  private:
    Expr* expression;
  public:
    Expression( Expr* _expression ): expression(_expression) {}
    Expr* getExpression() { return Expression; }
    void Accept(AbstractStmtDispatcher dispatcher) override {
      dispatcher.Dispatch(*this);
    }
};

class Function: public Stmt {
  private:
    Token name;
    std::vector<Token> params;
    std::vector<Stmt*> body;
  public:
    Function( Token _name, std::vector<Token> _params, std::vector<Stmt*> _body ): name(_name), params(_params), body(_body) {}
    Token getName() { return Name; }
    std::vector<Token> getParams() { return Params; }
    std::vector<Stmt*> getBody() { return Body; }
    void Accept(AbstractStmtDispatcher dispatcher) override {
      dispatcher.Dispatch(*this);
    }
};

class If: public Stmt {
  private:
    Expr* condition;
    Stmt* thenBranch;
    Stmt* elseBranch;
  public:
    If( Expr* _condition, Stmt* _thenBranch, Stmt* _elseBranch ): condition(_condition), thenBranch(_thenBranch), elseBranch(_elseBranch) {}
    Expr* getCondition() { return Condition; }
    Stmt* getThenBranch() { return ThenBranch; }
    Stmt* getElseBranch() { return ElseBranch; }
    void Accept(AbstractStmtDispatcher dispatcher) override {
      dispatcher.Dispatch(*this);
    }
};

class Print: public Stmt {
  private:
    Expr* expression;
  public:
    Print( Expr* _expression ): expression(_expression) {}
    Expr* getExpression() { return Expression; }
    void Accept(AbstractStmtDispatcher dispatcher) override {
      dispatcher.Dispatch(*this);
    }
};

class Return: public Stmt {
  private:
    Token keyword;
    Expr* value;
  public:
    Return( Token _keyword, Expr* _value ): keyword(_keyword), value(_value) {}
    Token getKeyword() { return Keyword; }
    Expr* getValue() { return Value; }
    void Accept(AbstractStmtDispatcher dispatcher) override {
      dispatcher.Dispatch(*this);
    }
};

class Var: public Stmt {
  private:
    Token name;
    Expr* initializer;
  public:
    Var( Token _name, Expr* _initializer ): name(_name), initializer(_initializer) {}
    Token getName() { return Name; }
    Expr* getInitializer() { return Initializer; }
    void Accept(AbstractStmtDispatcher dispatcher) override {
      dispatcher.Dispatch(*this);
    }
};

class While: public Stmt {
  private:
    Expr* condition;
    Stmt* body;
  public:
    While( Expr* _condition, Stmt* _body ): condition(_condition), body(_body) {}
    Expr* getCondition() { return Condition; }
    Stmt* getBody() { return Body; }
    void Accept(AbstractStmtDispatcher dispatcher) override {
      dispatcher.Dispatch(*this);
    }
};


#endif
