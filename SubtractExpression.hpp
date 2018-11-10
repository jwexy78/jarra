#ifndef SUBTRACT_EXPRESSION_HPP
#define SUBTRACT_EXPRESSION_HPP

#include "Expression.hpp"
#include "Object.hpp"

class SubtractExpression : public Expression
{
public:
    SubtractExpression( Expression* left, Expression* right );
    ~SubtractExpression();
    std::ostream& operator<<( std::ostream& os );
    Object* ToObject( ExecutionContext* context );
protected:
    Expression* left_;
    Expression* right_;
};

#endif