#ifndef Expr_HEADER_AUTO_GEN
#define Expr_HEADER_AUTO_GEN
#include "token.h"
#include <vector>
#include <any>



template<class R> class Assign;

template<class R> class Binary;

template<class R> class Call;

template<class R> class Get;

template<class R> class Grouping;

template<class R> class Literal;

template<class R> class Logical;

template<class R> class Set;

template<class R> class Super;

template<class R> class This;

template<class R> class Unary;

template<class R> class Variable;
template<class R>
class AbstractExprDispatcher {
  public:
    virtual R visitAssignExpr(Assign<R>& expr) = 0;
    virtual R visitBinaryExpr(Binary<R>& expr) = 0;
    virtual R visitCallExpr(Call<R>& expr) = 0;
    virtual R visitGetExpr(Get<R>& expr) = 0;
    virtual R visitGroupingExpr(Grouping<R>& expr) = 0;
    virtual R visitLiteralExpr(Literal<R>& expr) = 0;
    virtual R visitLogicalExpr(Logical<R>& expr) = 0;
    virtual R visitSetExpr(Set<R>& expr) = 0;
    virtual R visitSuperExpr(Super<R>& expr) = 0;
    virtual R visitThisExpr(This<R>& expr) = 0;
    virtual R visitUnaryExpr(Unary<R>& expr) = 0;
    virtual R visitVariableExpr(Variable<R>& expr) = 0;
};

template<class R>
class Expr {
  public:
    virtual R Accept(AbstractExprDispatcher<R>* dispatcher) = 0;
    ~Expr() {};
};




template<class R>
class Assign: public Expr<R> {
  private:
    Token name;
    Expr<R>* value;
  public:
    ~Assign();
    Assign( Token _name, Expr<R>* _value ): name(_name), value(_value) {}
    Token getName() { return name; }
    Expr<R>* getValue() { return value; }
    R Accept(AbstractExprDispatcher<R>* dispatcher) override {
      return dispatcher->visitAssignExpr(*this);
    }
};

template<class R>
class Binary: public Expr<R> {
  private:
    Expr<R>* left;
    Token op;
    Expr<R>* right;
  public:
    ~Binary();
    Binary( Expr<R>* _left, Token _op, Expr<R>* _right ): left(_left), op(_op), right(_right) {}
    Expr<R>* getLeft() { return left; }
    Token getOp() { return op; }
    Expr<R>* getRight() { return right; }
    R Accept(AbstractExprDispatcher<R>* dispatcher) override {
      return dispatcher->visitBinaryExpr(*this);
    }
};

template<class R>
class Call: public Expr<R> {
  private:
    Expr<R>* callee;
    Token paren;
    std::vector<Expr<R>*> arguments;
  public:
    ~Call();
    Call( Expr<R>* _callee, Token _paren, std::vector<Expr<R>*> _arguments ): callee(_callee), paren(_paren), arguments(_arguments) {}
    Expr<R>* getCallee() { return callee; }
    Token getParen() { return paren; }
    std::vector<Expr<R>*> getArguments() { return arguments; }
    R Accept(AbstractExprDispatcher<R>* dispatcher) override {
      return dispatcher->visitCallExpr(*this);
    }
};

template<class R>
class Get: public Expr<R> {
  private:
    Expr<R>* object;
    Token name;
  public:
    ~Get();
    Get( Expr<R>* _object, Token _name ): object(_object), name(_name) {}
    Expr<R>* getObject() { return object; }
    Token getName() { return name; }
    R Accept(AbstractExprDispatcher<R>* dispatcher) override {
      return dispatcher->visitGetExpr(*this);
    }
};

template<class R>
class Grouping: public Expr<R> {
  private:
    Expr<R>* expression;
  public:
    ~Grouping();
    Grouping( Expr<R>* _expression ): expression(_expression) {}
    Expr<R>* getExpression() { return expression; }
    R Accept(AbstractExprDispatcher<R>* dispatcher) override {
      return dispatcher->visitGroupingExpr(*this);
    }
};

template<class R>
class Literal: public Expr<R> {
  private:
    std::any value;
  public:
    ~Literal();
    Literal( std::any _value ): value(_value) {}
    std::any getValue() { return value; }
    R Accept(AbstractExprDispatcher<R>* dispatcher) override {
      return dispatcher->visitLiteralExpr(*this);
    }
};

template<class R>
class Logical: public Expr<R> {
  private:
    Expr<R>* left;
    Token op;
    Expr<R>* right;
  public:
    ~Logical();
    Logical( Expr<R>* _left, Token _op, Expr<R>* _right ): left(_left), op(_op), right(_right) {}
    Expr<R>* getLeft() { return left; }
    Token getOp() { return op; }
    Expr<R>* getRight() { return right; }
    R Accept(AbstractExprDispatcher<R>* dispatcher) override {
      return dispatcher->visitLogicalExpr(*this);
    }
};

template<class R>
class Set: public Expr<R> {
  private:
    Expr<R>* object;
    Token name;
    Expr<R>* value;
  public:
    ~Set();
    Set( Expr<R>* _object, Token _name, Expr<R>* _value ): object(_object), name(_name), value(_value) {}
    Expr<R>* getObject() { return object; }
    Token getName() { return name; }
    Expr<R>* getValue() { return value; }
    R Accept(AbstractExprDispatcher<R>* dispatcher) override {
      return dispatcher->visitSetExpr(*this);
    }
};

template<class R>
class Super: public Expr<R> {
  private:
    Token keyword;
    Token method;
  public:
    ~Super();
    Super( Token _keyword, Token _method ): keyword(_keyword), method(_method) {}
    Token getKeyword() { return keyword; }
    Token getMethod() { return method; }
    R Accept(AbstractExprDispatcher<R>* dispatcher) override {
      return dispatcher->visitSuperExpr(*this);
    }
};

template<class R>
class This: public Expr<R> {
  private:
    Token keyword;
  public:
    ~This();
    This( Token _keyword ): keyword(_keyword) {}
    Token getKeyword() { return keyword; }
    R Accept(AbstractExprDispatcher<R>* dispatcher) override {
      return dispatcher->visitThisExpr(*this);
    }
};

template<class R>
class Unary: public Expr<R> {
  private:
    Token op;
    Expr<R>* right;
  public:
    ~Unary();
    Unary( Token _op, Expr<R>* _right ): op(_op), right(_right) {}
    Token getOp() { return op; }
    Expr<R>* getRight() { return right; }
    R Accept(AbstractExprDispatcher<R>* dispatcher) override {
      return dispatcher->visitUnaryExpr(*this);
    }
};

template<class R>
class Variable: public Expr<R> {
  private:
    Token name;
  public:
    ~Variable();
    Variable( Token _name ): name(_name) {}
    Token getName() { return name; }
    R Accept(AbstractExprDispatcher<R>* dispatcher) override {
      return dispatcher->visitVariableExpr(*this);
    }
};


#endif
