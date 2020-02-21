#ifndef Stmt_HEADER_AUTO_GEN
#define Stmt_HEADER_AUTO_GEN
#include "token.h"
#include "expr.h"
#include <vector>



template<class R> class Block;

template<class R> class Class;

template<class R> class Expression;

template<class R> class Function;

template<class R> class If;

template<class R> class Print;

template<class R> class Return;

template<class R> class Var;

template<class R> class While;
template<class R>
class AbstractStmtDispatcher {
  public:
    virtual R visitBlockStmt(Block<R>& expr) = 0;
    virtual R visitClassStmt(Class<R>& expr) = 0;
    virtual R visitExpressionStmt(Expression<R>& expr) = 0;
    virtual R visitFunctionStmt(Function<R>& expr) = 0;
    virtual R visitIfStmt(If<R>& expr) = 0;
    virtual R visitPrintStmt(Print<R>& expr) = 0;
    virtual R visitReturnStmt(Return<R>& expr) = 0;
    virtual R visitVarStmt(Var<R>& expr) = 0;
    virtual R visitWhileStmt(While<R>& expr) = 0;
};

template<class R>
class Stmt {
  public:
    virtual R Accept(AbstractStmtDispatcher<R>* dispatcher) = 0;
    ~Stmt() {};
};




template<class R>
class Block: public Stmt<R> {
  private:
    std::vector<Stmt<R>*> statements;
  public:
    ~Block();
    Block( std::vector<Stmt<R>*> _statements ): statements(_statements) {}
    std::vector<Stmt<R>*> getStatements() { return statements; }
    R Accept(AbstractStmtDispatcher<R>* dispatcher) override {
      return dispatcher->visitBlockStmt(*this);
    }
};

template<class R>
class Class: public Stmt<R> {
  private:
    Token name;
    Variable<R> superclass;
    std::vector<Function<R>> methods;
  public:
    ~Class();
    Class( Token _name, Variable<R> _superclass, std::vector<Function<R>> _methods ): name(_name), superclass(_superclass), methods(_methods) {}
    Token getName() { return name; }
    Variable<R> getSuperclass() { return superclass; }
    std::vector<Function<R>> getMethods() { return methods; }
    R Accept(AbstractStmtDispatcher<R>* dispatcher) override {
      return dispatcher->visitClassStmt(*this);
    }
};

template<class R>
class Expression: public Stmt<R> {
  private:
    Expr<R>* expression;
  public:
    ~Expression();
    Expression( Expr<R>* _expression ): expression(_expression) {}
    Expr<R>* getExpression() { return expression; }
    R Accept(AbstractStmtDispatcher<R>* dispatcher) override {
      return dispatcher->visitExpressionStmt(*this);
    }
};

template<class R>
class Function: public Stmt<R> {
  private:
    Token name;
    std::vector<Token> params;
    std::vector<Stmt<R>*> body;
  public:
    ~Function();
    Function( Token _name, std::vector<Token> _params, std::vector<Stmt<R>*> _body ): name(_name), params(_params), body(_body) {}
    Token getName() { return name; }
    std::vector<Token> getParams() { return params; }
    std::vector<Stmt<R>*> getBody() { return body; }
    R Accept(AbstractStmtDispatcher<R>* dispatcher) override {
      return dispatcher->visitFunctionStmt(*this);
    }
};

template<class R>
class If: public Stmt<R> {
  private:
    Expr<R>* condition;
    Stmt<R>* thenBranch;
    Stmt<R>* elseBranch;
  public:
    ~If();
    If( Expr<R>* _condition, Stmt<R>* _thenBranch, Stmt<R>* _elseBranch ): condition(_condition), thenBranch(_thenBranch), elseBranch(_elseBranch) {}
    Expr<R>* getCondition() { return condition; }
    Stmt<R>* getThenBranch() { return thenBranch; }
    Stmt<R>* getElseBranch() { return elseBranch; }
    R Accept(AbstractStmtDispatcher<R>* dispatcher) override {
      return dispatcher->visitIfStmt(*this);
    }
};

template<class R>
class Print: public Stmt<R> {
  private:
    Expr<R>* expression;
  public:
    ~Print();
    Print( Expr<R>* _expression ): expression(_expression) {}
    Expr<R>* getExpression() { return expression; }
    R Accept(AbstractStmtDispatcher<R>* dispatcher) override {
      return dispatcher->visitPrintStmt(*this);
    }
};

template<class R>
class Return: public Stmt<R> {
  private:
    Token keyword;
    Expr<R>* value;
  public:
    ~Return();
    Return( Token _keyword, Expr<R>* _value ): keyword(_keyword), value(_value) {}
    Token getKeyword() { return keyword; }
    Expr<R>* getValue() { return value; }
    R Accept(AbstractStmtDispatcher<R>* dispatcher) override {
      return dispatcher->visitReturnStmt(*this);
    }
};

template<class R>
class Var: public Stmt<R> {
  private:
    Token name;
    Expr<R>* initializer;
  public:
    ~Var();
    Var( Token _name, Expr<R>* _initializer ): name(_name), initializer(_initializer) {}
    Token getName() { return name; }
    Expr<R>* getInitializer() { return initializer; }
    R Accept(AbstractStmtDispatcher<R>* dispatcher) override {
      return dispatcher->visitVarStmt(*this);
    }
};

template<class R>
class While: public Stmt<R> {
  private:
    Expr<R>* condition;
    Stmt<R>* body;
  public:
    ~While();
    While( Expr<R>* _condition, Stmt<R>* _body ): condition(_condition), body(_body) {}
    Expr<R>* getCondition() { return condition; }
    Stmt<R>* getBody() { return body; }
    R Accept(AbstractStmtDispatcher<R>* dispatcher) override {
      return dispatcher->visitWhileStmt(*this);
    }
};


#endif