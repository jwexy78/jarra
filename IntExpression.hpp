#ifndef INT_EXPRESSION_HPP
#define INT_EXPRESSION_HPP

#include "Expression.hpp"
#include "Object.hpp"

class IntExpression : public Expression
{
public:
    IntExpression( int value );
    std::ostream& operator<<( std::ostream& os );
    Object* ToObject( ExecutionContext* context );
private:
    int value_;
};

#endif