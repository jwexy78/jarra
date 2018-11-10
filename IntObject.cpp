#include "IntObject.hpp"
#include "FloatObject.hpp"
#include "BoolObject.hpp"

IntObject::IntObject( int data )
    : Object( Object::Int )
    , data_( data )
{
}

std::string IntObject::ToString()
{
    return std::to_string( data_ );
}

bool IntObject::BoolValue()
{
    return data_ != 0;
}

Object* IntObject::Add( Object* other, ExecutionContext* context )
{
    if( other->type_ == Int )
    {
        return new IntObject( data_ + reinterpret_cast<IntObject*>(other)->data_ );
    }
    if( other->type_ == Float )
    {
        return new FloatObject( data_ + reinterpret_cast<FloatObject*>(other)->data_ );
    }
    return ThrowAddNotImplemented( other->type_, context );
}

Object* IntObject::Subtract( Object* other, ExecutionContext* context )
{
    if( other->type_ == Int )
    {
        return new IntObject( data_ - reinterpret_cast<IntObject*>(other)->data_ );
    }
    if( other->type_ == Float )
    {
        return new FloatObject( data_ - reinterpret_cast<FloatObject*>(other)->data_ );
    }
    return ThrowSubtractNotImplemented( other->type_, context );
}

Object* IntObject::Multiply( Object* other, ExecutionContext* context )
{
    if( other->type_ == Int )
    {
        return new IntObject( data_ * reinterpret_cast<IntObject*>(other)->data_ );
    }
    if( other->type_ == Float )
    {
        return new FloatObject( data_ * reinterpret_cast<FloatObject*>(other)->data_ );
    }
    return ThrowMultiplyNotImplemented( other->type_, context );
}

Object* IntObject::Divide( Object* other, ExecutionContext* context )
{
    if( other->type_ == Int )
    {
        return new IntObject( data_ / reinterpret_cast<IntObject*>(other)->data_ );
    }
    if( other->type_ == Float )
    {
        return new FloatObject( data_ / reinterpret_cast<FloatObject*>(other)->data_ );
    }
    return ThrowDivideNotImplemented( other->type_, context );
}

BoolObject* IntObject::LessThan( Object* other, ExecutionContext* context )
{
    if( other->type_ == Int )
    {
        return new BoolObject( data_ < reinterpret_cast<IntObject*>(other)->data_ );
    }
    if( other->type_ == Float )
    {
        return new BoolObject( data_ < reinterpret_cast<FloatObject*>(other)->data_ );
    }
    ThrowLessThanNotImplemented( other->type_, context );
    return nullptr;
}

BoolObject* IntObject::Equals( Object* other, ExecutionContext* context )
{
    if( other->type_ == Int )
    {
        return new BoolObject( data_ == reinterpret_cast<IntObject*>(other)->data_ );
    }
    if( other->type_ == Float )
    {
        return new BoolObject( data_ == reinterpret_cast<FloatObject*>(other)->data_ );
    }
    return new BoolObject( false );
}
