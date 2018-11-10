#include "Expression.hpp"

Expression::Expression( ExpressionType type )
    : type_( type )
{
}

Expression::~Expression()
{
}

std::ostream& operator<<( std::ostream& os, Expression* exp )
{
    return (*exp) << os;
}