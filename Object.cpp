#include "Object.hpp"
#include "StringObject.hpp"
#include "BoolObject.hpp"
#include "ExecutionContext.hpp"
#include "Logger.hpp"

#include <iostream>

std::string Object::TypeToString( ObjectType type )
{
    switch( type )
    {
        case None:
            return "None";
        case Int:
            return "Int";
        case Float:
            return "Float";
        case String:
            return "String";
        case Function:
            return "Function";
        case List:
            return "List";
        case Reference:
            return "Reference";
        case WeakReference:
            return "WeakReference";
        case Bool:
            return "Bool";
        case CodeBlock:
            return "CodeBlock";
    }
}

// Define the object methods
Object::Object( ObjectType type )
    : type_( type )
    , referenceCount_( 0 )
{
    Acquire();
    LOG( "allocated new " + TypeToString( type_ ) + " object at " + THIS_STR );
}

Object::~Object()
{
    LOG( "de-allocating " + TypeToString(type_) + " object at " + THIS_STR );
}

Object* Object::ThrowNotImplemented( std::string operation, ObjectType otherType, ExecutionContext* context )
{
    context->SetException( new StringObject( 
        operation + " is not defined for Objects of type " + TypeToString( type_ ) 
        + " and " + TypeToString( otherType ) ) );
    return nullptr;
}

Object* Object::ThrowAddNotImplemented( ObjectType otherType, ExecutionContext* context )
{
    return ThrowNotImplemented( "Add", otherType, context );
}

Object* Object::ThrowSubtractNotImplemented( ObjectType otherType, ExecutionContext* context )
{
    return ThrowNotImplemented( "Subtract", otherType, context );
}

Object* Object::ThrowMultiplyNotImplemented( ObjectType otherType, ExecutionContext* context )
{
    return ThrowNotImplemented( "Multiply", otherType, context );
}

Object* Object::ThrowDivideNotImplemented( ObjectType otherType, ExecutionContext* context )
{
    return ThrowNotImplemented( "Divide", otherType, context );
}

Object* Object::ThrowAssignNotImplemented( ObjectType otherType, ExecutionContext* context )
{
    return ThrowNotImplemented( "Assign", otherType, context );
}

Object* Object::ThrowCallNotImplemented( ObjectType otherType, ExecutionContext* context )
{
    return ThrowNotImplemented( "Call", otherType, context );
}

Object* Object::ThrowJoinNotImplemented( ObjectType otherType, ExecutionContext* context )
{
    return ThrowNotImplemented( "Join", otherType, context );
}

Object* Object::ThrowIndexNotImplemented( ObjectType otherType, ExecutionContext* context )
{
    return ThrowNotImplemented( "Index", otherType, context );
}

Object* Object::ThrowEqualsNotImplemented( ObjectType otherType, ExecutionContext* context )
{
    return ThrowNotImplemented( "Equals", otherType, context );
}

Object* Object::ThrowLessThanNotImplemented( ObjectType otherType, ExecutionContext* context )
{
    return ThrowNotImplemented( "Less Than", otherType, context );
}

// Un-override method defaults

Object* Object::Add( Object* other, ExecutionContext* context )
{
    return ThrowAddNotImplemented( other->type_, context );
}

Object* Object::Subtract( Object* other, ExecutionContext* context )
{
    return ThrowSubtractNotImplemented( other->type_, context );
}

Object* Object::Multiply( Object* other, ExecutionContext* context )
{
    return ThrowMultiplyNotImplemented( other->type_, context );
}

Object* Object::Divide( Object* other, ExecutionContext* context )
{
    return ThrowDivideNotImplemented( other->type_, context );
}

Object* Object::Assign( Object* other, ExecutionContext* context )
{
    return ThrowAssignNotImplemented( other->type_, context );
}

Object* Object::Call( Object* other, ExecutionContext* context )
{
    return ThrowCallNotImplemented( other->type_, context );
}

Object* Object::Join( Object* other, ExecutionContext* context )
{
    return ThrowJoinNotImplemented( other->type_, context );
}

Object* Object::Index( Object* other, ExecutionContext* context )
{
    return ThrowIndexNotImplemented( other->type_, context );
}

BoolObject* Object::Equals( Object* other, ExecutionContext* context )
{
    ThrowEqualsNotImplemented( other->type_, context );
    return nullptr;
}

BoolObject* Object::LessThan( Object* other, ExecutionContext* context )
{
    ThrowLessThanNotImplemented( other->type_, context );
    return nullptr;
}

void Object::Acquire()
{
    referenceCount_++;
    // std::cout << "Acquired " << this << " (" << referenceCount_ << ")\n";
}

bool Object::Release(){
    referenceCount_--;
    // std::cout << "Released " << this << " (" << referenceCount_ << ")\n";
    if( !referenceCount_ )
    {
        // std::cout << "Destroying...\n";
        Destroy();
        delete this;
        return false;
    }
    return true;
}

void Object::Destroy()
{

}

Object* Object::Finalize( const ExecutionContext* )
{
    return this;
}