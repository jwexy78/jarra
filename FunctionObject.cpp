#include "FunctionObject.hpp"

FunctionObject::FunctionObject()
    : Object( Object::Function )
{
}

std::string FunctionObject::ToString()
{
    return "Function";
}

bool FunctionObject::BoolValue()
{
    return true;
}

Object* FunctionObject::Call( Object* parameter, ExecutionContext* context )
{
    ThrowCallNotImplemented( parameter->type_, context );
    return nullptr;
}