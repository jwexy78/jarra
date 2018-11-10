#include "StringExpression.hpp"
#include "StringObject.hpp"

StringExpression::StringExpression( std::string value )
    : Expression( String )
    , value_( value )
{}
std::ostream& StringExpression::operator<<( std::ostream& os )
{
    return os << "[String: " << value_ << "]";
}
Object* StringExpression::ToObject( ExecutionContext* context )
{
    return new StringObject( value_ );
}
