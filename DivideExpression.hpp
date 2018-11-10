#ifndef DIVIDE_EXPRESSION_HPP
#define DIVIDE_EXPRESSION_HPP

#include "Expression.hpp"
#include "Object.hpp"

class DivideExpression : public Expression
{
public:
    DivideExpression( Expression* left, Expression* right );
    ~DivideExpression();
    std::ostream& operator<<( std::ostream& os );
    Object* ToObject( ExecutionContext* context );
protected:
    Expression* left_;
    Expression* right_;
};

#endif