#ifndef Expr_HEADER_AUTO_GEN
#define Expr_HEADER_AUTO_GEN
#include "token.h"
#include <vector>
#include <any>
class Assign;
class Binary;
class Call;
class Get;
class Grouping;
class Literal;
class Logical;
class Set;
class Super;
class This;
class Unary;
class Variable;
class AbstractExprDispatcher {
  public:
    virtual void Dispatch(Assign Expr) = 0;
    virtual void Dispatch(Binary Expr) = 0;
    virtual void Dispatch(Call Expr) = 0;
    virtual void Dispatch(Get Expr) = 0;
    virtual void Dispatch(Grouping Expr) = 0;
    virtual void Dispatch(Literal Expr) = 0;
    virtual void Dispatch(Logical Expr) = 0;
    virtual void Dispatch(Set Expr) = 0;
    virtual void Dispatch(Super Expr) = 0;
    virtual void Dispatch(This Expr) = 0;
    virtual void Dispatch(Unary Expr) = 0;
    virtual void Dispatch(Variable Expr) = 0;
};
class Expr {
  public:
    virtual void Accept(AbstractExprDispatcher dispatcher) = 0;
    virtual ~Expr() = 0;
};




class Assign: public Expr {
  private:
    Token name;
    Expr* value;
  public:
    Assign( Token _name, Expr* _value ): name(_name), value(_value) {}
    Token getName() { return Name; }
    Expr* getValue() { return Value; }
    void Accept(AbstractExprDispatcher dispatcher) override {
      dispatcher.Dispatch(*this);
    }
};

class Binary: public Expr {
  private:
    Expr* left;
    Token op;
    Expr* right;
  public:
    Binary( Expr* _left, Token _op, Expr* _right ): left(_left), op(_op), right(_right) {}
    Expr* getLeft() { return Left; }
    Token getOp() { return Op; }
    Expr* getRight() { return Right; }
    void Accept(AbstractExprDispatcher dispatcher) override {
      dispatcher.Dispatch(*this);
    }
};

class Call: public Expr {
  private:
    Expr* callee;
    Token paren;
    std::vector<Expr*> arguments;
  public:
    Call( Expr* _callee, Token _paren, std::vector<Expr*> _arguments ): callee(_callee), paren(_paren), arguments(_arguments) {}
    Expr* getCallee() { return Callee; }
    Token getParen() { return Paren; }
    std::vector<Expr*> getArguments() { return Arguments; }
    void Accept(AbstractExprDispatcher dispatcher) override {
      dispatcher.Dispatch(*this);
    }
};

class Get: public Expr {
  private:
    Expr* object;
    Token name;
  public:
    Get( Expr* _object, Token _name ): object(_object), name(_name) {}
    Expr* getObject() { return Object; }
    Token getName() { return Name; }
    void Accept(AbstractExprDispatcher dispatcher) override {
      dispatcher.Dispatch(*this);
    }
};

class Grouping: public Expr {
  private:
    Expr* expression;
  public:
    Grouping( Expr* _expression ): expression(_expression) {}
    Expr* getExpression() { return Expression; }
    void Accept(AbstractExprDispatcher dispatcher) override {
      dispatcher.Dispatch(*this);
    }
};

class Literal: public Expr {
  private:
    std::any value;
  public:
    Literal( std::any _value ): value(_value) {}
    std::any getValue() { return Value; }
    void Accept(AbstractExprDispatcher dispatcher) override {
      dispatcher.Dispatch(*this);
    }
};

class Logical: public Expr {
  private:
    Expr* left;
    Token op;
    Expr* right;
  public:
    Logical( Expr* _left, Token _op, Expr* _right ): left(_left), op(_op), right(_right) {}
    Expr* getLeft() { return Left; }
    Token getOp() { return Op; }
    Expr* getRight() { return Right; }
    void Accept(AbstractExprDispatcher dispatcher) override {
      dispatcher.Dispatch(*this);
    }
};

class Set: public Expr {
  private:
    Expr* object;
    Token name;
    Expr* value;
  public:
    Set( Expr* _object, Token _name, Expr* _value ): object(_object), name(_name), value(_value) {}
    Expr* getObject() { return Object; }
    Token getName() { return Name; }
    Expr* getValue() { return Value; }
    void Accept(AbstractExprDispatcher dispatcher) override {
      dispatcher.Dispatch(*this);
    }
};

class Super: public Expr {
  private:
    Token keyword;
    Token method;
  public:
    Super( Token _keyword, Token _method ): keyword(_keyword), method(_method) {}
    Token getKeyword() { return Keyword; }
    Token getMethod() { return Method; }
    void Accept(AbstractExprDispatcher dispatcher) override {
      dispatcher.Dispatch(*this);
    }
};

class This: public Expr {
  private:
    Token keyword;
  public:
    This( Token _keyword ): keyword(_keyword) {}
    Token getKeyword() { return Keyword; }
    void Accept(AbstractExprDispatcher dispatcher) override {
      dispatcher.Dispatch(*this);
    }
};

class Unary: public Expr {
  private:
    Token op;
    Expr* right;
  public:
    Unary( Token _op, Expr* _right ): op(_op), right(_right) {}
    Token getOp() { return Op; }
    Expr* getRight() { return Right; }
    void Accept(AbstractExprDispatcher dispatcher) override {
      dispatcher.Dispatch(*this);
    }
};

class Variable: public Expr {
  private:
    Token name;
  public:
    Variable( Token _name ): name(_name) {}
    Token getName() { return Name; }
    void Accept(AbstractExprDispatcher dispatcher) override {
      dispatcher.Dispatch(*this);
    }
};


#endif