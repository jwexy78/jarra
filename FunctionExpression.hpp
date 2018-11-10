#ifndef FUNCTION_EXPRESSION_HPP
#define FUNCTION_EXPRESSION_HPP

#include "Expression.hpp"
#include "Object.hpp"

class FunctionExpression : public Expression
{
public:
    FunctionExpression( Expression* caller, Expression* parameter );
    ~FunctionExpression();
    std::ostream& operator<<( std::ostream& os );
    Object* ToObject( ExecutionContext* context );
protected:
    Expression* caller_;
    Expression* parameter_;
};

#endif