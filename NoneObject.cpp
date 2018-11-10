#include "NoneObject.hpp"
#include "BoolObject.hpp"

NoneObject::NoneObject()
    : Object( Object::None )
{
}

std::string NoneObject::ToString()
{
    return "None";
}

bool NoneObject::BoolValue()
{
    return false;
}

BoolObject* NoneObject::Equals( Object* other, ExecutionContext* context )
{
    if( other->type_ == None )
    {
        return new BoolObject( true );
    }
    return new BoolObject( false );
}
