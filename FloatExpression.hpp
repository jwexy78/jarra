#ifndef FLOAT_EXPRESSION_HPP
#define FLOAT_EXPRESSION_HPP

#include "Expression.hpp"
#include "Object.hpp"

class FloatExpression : public Expression
{
public:
    FloatExpression( float value );
    std::ostream& operator<<( std::ostream& os );
    Object* ToObject( ExecutionContext* context );
private:
    float value_;
};

#endif