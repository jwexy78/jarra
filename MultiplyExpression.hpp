#ifndef MULTIPLY_EXPRESSION_HPP
#define MULTIPLY_EXPRESSION_HPP

#include "Expression.hpp"
#include "Object.hpp"

class MultiplyExpression : public Expression
{
public:
    MultiplyExpression( Expression* left, Expression* right );
    ~MultiplyExpression();
    std::ostream& operator<<( std::ostream& os );
    Object* ToObject( ExecutionContext* context );
protected:
    Expression* left_;
    Expression* right_;
};

#endif