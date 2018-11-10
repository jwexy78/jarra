#include "EmptyExpression.hpp"
#include "NoneObject.hpp"

EmptyExpression::EmptyExpression()
    : Expression( Empty )
{
}

std::ostream& EmptyExpression::operator<<( std::ostream& os )
{
    return os << "[Empty]";
}

Object* EmptyExpression::ToObject( ExecutionContext* context )
{
    return new NoneObject();
}