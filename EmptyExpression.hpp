#ifndef EMPTY_EXPRESSION_HPP
#define EMPTY_EXPRESSION_HPP

#include "Expression.hpp"

class EmptyExpression : public Expression
{
public:
    EmptyExpression();

    std::ostream& operator<<( std::ostream& os );

    Object* ToObject( ExecutionContext* context );
};

#endif