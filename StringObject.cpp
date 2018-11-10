#include "StringObject.hpp"
#include "IntObject.hpp"
#include "FloatObject.hpp"
#include "BoolObject.hpp"
#include "ExecutionContext.hpp"

StringObject::StringObject( std::string content )
    : Object( Object::String )
    , data_( content )
{
}

inline char CharEscapeReplace( char in )
{
    switch( in )
    {
        case 'n':
            return '\n';
        case 't':
            return '\t';
        case '\\':
            return '\\';
        default:
            return '?';
    }
}

std::string StringObject::ToString()
{
    std::string output;
    for( int i = 0; i < data_.length(); ++i )
    {
        char c = data_[i];
        if( c == '\\')
        {
            ++i;
            c = CharEscapeReplace( data_[i] );
        }
        output += c;
    }
    return output;
}

bool StringObject::BoolValue()
{
    return data_.length() != 0;
}

Object* StringObject::Add( Object* other, ExecutionContext* context )
{
    if( other->type_ == ObjectType::String )
    {
        return new StringObject( data_ + reinterpret_cast<StringObject*>(other)->ToString() );
    }
    if( other->type_ == ObjectType::Int )
    {
        return new StringObject( data_ + reinterpret_cast<IntObject*>(other)->ToString() );
    }
    if( other->type_ == ObjectType::Float )
    {
        return new StringObject( data_ + reinterpret_cast<FloatObject*>(other)->ToString() );
    }
    return ThrowAddNotImplemented( other->type_, context );
}

Object* StringObject::Multiply( Object* other, ExecutionContext* context )
{
    if( other->type_ == ObjectType::Int )
    {
        std::string content;
        for( int i = 0; i < reinterpret_cast<IntObject*>(other)->data_; ++i )
        {
            content += data_;
        }
        return new StringObject( content );
    }
    return ThrowMultiplyNotImplemented( other->type_, context );
}

BoolObject* StringObject::Equals( Object* other, ExecutionContext* context )
{
    if( other->type_ == String )
    {
        return new BoolObject( data_ == reinterpret_cast<StringObject*>(other)->data_ );
    }
    return new BoolObject( false );
}


Object* StringObject::Index( Object* other, ExecutionContext* context )
{
    if( other->type_ == Object::Int )
    {
        int index = reinterpret_cast<IntObject*>( other )->data_;
        if( index < 0 || index >= data_.length() )
        {
            context->SetException( new StringObject( "Index " + std::to_string( index ) + " Out Of Bounds!" ) );
            return nullptr;
        }
        return new StringObject( std::string("") + data_[index] );
    }
    return ThrowIndexNotImplemented( other->type_, context );
}