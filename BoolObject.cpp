#include "BoolObject.hpp"

BoolObject::BoolObject( bool value )
    : Object( Object::Bool )
    , value_( value )
{
}

std::string BoolObject::ToString()
{
    return (value_ ? "True" : "False");
}

bool BoolObject::BoolValue()
{
    return value_;
}