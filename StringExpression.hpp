#ifndef STRING_EXPRESSION_HPP
#define STRING_EXPRESSION_HPP

#include "Expression.hpp"
#include "Object.hpp"

class StringExpression : public Expression
{
public:
    StringExpression( std::string value );
    std::ostream& operator<<( std::ostream& os );
    Object* ToObject( ExecutionContext* context );
private:
    std::string value_;
};

#endif