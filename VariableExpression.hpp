#ifndef VARIABLE_EXPRESSION_HPP
#define VARIABLE_EXPRESSION_HPP

#include "Expression.hpp"
#include "Object.hpp"

class VariableExpression : public Expression
{
public:
    VariableExpression( std::string value );
    std::ostream& operator<<( std::ostream& os );
    Object* ToObject( ExecutionContext* context );
    std::string GetValue();
private:
    std::string value_;
};

#endif