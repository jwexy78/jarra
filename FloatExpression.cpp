#include "FloatExpression.hpp"
#include "FloatObject.hpp"

FloatExpression::FloatExpression( float value )
    : Expression( Float )
    , value_( value )
{}
std::ostream& FloatExpression::operator<<( std::ostream& os )
{
    return os << "[Float: " << value_ << "]";
}
Object* FloatExpression::ToObject( ExecutionContext* context )
{
    return new FloatObject( value_ );
}
