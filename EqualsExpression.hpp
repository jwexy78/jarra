#ifndef EQUALS_EXPRESSION_HPP
#define EQUALS_EXPRESSION_HPP

#include "Expression.hpp"
#include "Object.hpp"

class EqualsExpression : public Expression
{
public:
    EqualsExpression( Expression* left, Expression* right );
    ~EqualsExpression();
    std::ostream& operator<<( std::ostream& os );
    Object* ToObject( ExecutionContext* context );
protected:
    Expression* left_;
    Expression* right_;
};

#endif