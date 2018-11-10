#include "FloatObject.hpp"
#include "IntObject.hpp"
#include "BoolObject.hpp"

FloatObject::FloatObject( float data )
    : Object( Object::Float )
    , data_( data )
{
}

std::string FloatObject::ToString()
{
    std::string str = std::to_string( data_ );
    str.erase( str.find_last_not_of('0') + 1, std::string::npos );
    if( str[str.length() - 1] == '.' )
    {
        return str + "0";
    }
    return str;
}

bool FloatObject::BoolValue()
{
    return data_ != 0;
}

Object* FloatObject::Add( Object* other, ExecutionContext* context )
{
    if( other->type_ == Int )
    {
        return new FloatObject( data_ + reinterpret_cast<IntObject*>(other)->data_ );
    }
    if( other->type_ == Float )
    {
        return new FloatObject( data_ + reinterpret_cast<FloatObject*>(other)->data_ );
    }
    return ThrowAddNotImplemented( other->type_, context );
}

Object* FloatObject::Subtract( Object* other, ExecutionContext* context )
{
    if( other->type_ == Int )
    {
        return new FloatObject( data_ - reinterpret_cast<IntObject*>(other)->data_ );
    }
    if( other->type_ == Float )
    {
        return new FloatObject( data_ - reinterpret_cast<FloatObject*>(other)->data_ );
    }
    return ThrowSubtractNotImplemented( other->type_, context );
}

Object* FloatObject::Multiply( Object* other, ExecutionContext* context )
{
    if( other->type_ == Int )
    {
        return new FloatObject( data_ * reinterpret_cast<IntObject*>(other)->data_ );
    }
    if( other->type_ == Float )
    {
        return new FloatObject( data_ * reinterpret_cast<FloatObject*>(other)->data_ );
    }
    return ThrowMultiplyNotImplemented( other->type_, context );
}

Object* FloatObject::Divide( Object* other, ExecutionContext* context )
{
    if( other->type_ == Int )
    {
        return new FloatObject( data_ / reinterpret_cast<IntObject*>(other)->data_ );
    }
    if( other->type_ == Float )
    {
        return new FloatObject( data_ / reinterpret_cast<FloatObject*>(other)->data_ );
    }
    return ThrowDivideNotImplemented( other->type_, context );
}

BoolObject* FloatObject::Equals( Object* other, ExecutionContext* context )
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