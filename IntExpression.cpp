#include "IntExpression.hpp"
#include "IntObject.hpp"
#include "Logger.hpp"

IntExpression::IntExpression( int value )
    : Expression( Expression::Int )
    , value_( value )
{}
std::ostream& IntExpression::operator<<( std::ostream& os )
{
    return os << "[Int: " << value_ << "]";
}
Object* IntExpression::ToObject( ExecutionContext* context )
{
    return new IntObject( value_ );
}
