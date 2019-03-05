#include "BuiltIns.hpp"
#include "FunctionObject.hpp"
#include "NoneObject.hpp"
#include "BoolObject.hpp"
#include "FloatObject.hpp"
#include "IntObject.hpp"
#include "StringObject.hpp"
#include "ListObject.hpp"
#include <iostream>
#include <stdlib.h>

#define ADD_BUILTIN(name,objtype) \
    obj = new objtype;\
    context->SetVariable( name, obj );\
    obj->Release();

class PrintObject : public FunctionObject
{
public:
    Object* Call( Object* parameter, ExecutionContext* context )
    {
        std::string str = parameter->ToString();
        std::cout << str;
        return new NoneObject();
    }
};

class PrintlnObject : public FunctionObject
{
public:
    Object* Call( Object* parameter, ExecutionContext* context )
    {
        std::string str = parameter->ToString();
        std::cout << str << "\n";
        return new NoneObject();
    }
};

class GetLineObject : public FunctionObject
{
public:
    Object* Call( Object* parameter, ExecutionContext* context )
    {
        std::string str;
        if( getline( std::cin, str ) )
        {
            return new StringObject( str );
        }
        else
        {
            context->SetException( new StringObject( "Error reading from stdin" ) );
            return nullptr;
        }
    }
};

class TruthObject : public FunctionObject
{
public:
    Object* Call( Object* parameter, ExecutionContext* context )
    {
        return new BoolObject( parameter->BoolValue() );
    }
};

class LenObject : public FunctionObject
{
public:
    Object* Call( Object* parameter, ExecutionContext* context )
    {
        if( parameter->type_ == List )
        {
            ListObject* list = reinterpret_cast<ListObject*>( parameter );
            return new IntObject( list->contents_.size() );
        }
        context->SetException( new StringObject( "'len' can only be called on a list" ) );
        return nullptr;
    }
};

class StrObject : public FunctionObject
{
public:
    Object* Call( Object* parameter, ExecutionContext* context )
    {
        return new StringObject( parameter->ToString() );
    }
};

class IntFunctionObject : public FunctionObject
{
public:
    Object* Call( Object* parameter, ExecutionContext* context )
    {
        if( parameter->type_ == Int )
        {
            IntObject* obj = reinterpret_cast<IntObject*>( parameter );
            return new IntObject( obj->data_ );
        }
        if( parameter->type_ == Float )
        {
            FloatObject* obj = reinterpret_cast<FloatObject*>( parameter );
            return new IntObject( (int)obj->data_ );
        }
        if( parameter->type_ == String )
        {
            StringObject* obj = reinterpret_cast<StringObject*>( parameter );
            std::string contents = obj->data_;
            size_t len;
            int val;
            try
            {
                val = stoi( contents, &len );
            }
            catch( std::exception e )
            {
                len = -1;
            }
            if( len != contents.length() )
            {
                context->SetException( new StringObject( "Could not parse '" + contents + "' as an Integer" ) );
                return nullptr;
            }
            return new IntObject( val );
        }
        if( parameter->type_ == Bool )
        {
            BoolObject* obj = reinterpret_cast<BoolObject*>( parameter );
            return new IntObject( obj->value_ ? 1 : 0 );
        }
        context->SetException( new StringObject( "Invalid parameter type to 'int'" ) );
        return nullptr;
    }
};

class FloatFunctionObject : public FunctionObject
{
public:
    Object* Call( Object* parameter, ExecutionContext* context )
    {
        if( parameter->type_ == Int )
        {
            IntObject* obj = reinterpret_cast<IntObject*>( parameter );
            return new FloatObject( obj->data_ );
        }
        if( parameter->type_ == Float )
        {
            FloatObject* obj = reinterpret_cast<FloatObject*>( parameter );
            return new FloatObject( obj->data_ );
        }
        if( parameter->type_ == String )
        {
            StringObject* obj = reinterpret_cast<StringObject*>( parameter );
            std::string contents = obj->data_;
            size_t len;
            float val;
            try
            {
                val = stof( contents, &len );
            }
            catch( std::exception e )
            {
                len = -1;
            }
            if( len != contents.length() )
            {
                context->SetException( new StringObject( "Could not parse '" + contents + "' as an Integer" ) );
                return nullptr;
            }
            return new FloatObject( val );
        }
        if( parameter->type_ == Bool )
        {
            BoolObject* obj = reinterpret_cast<BoolObject*>( parameter );
            return new FloatObject( obj->value_ ? 1.0 : 0.0 );
        }
        context->SetException( new StringObject( "Invalid parameter type to 'int'" ) );
        return nullptr;
    }
};


class SystemObject : public FunctionObject
{
public:
    Object* Call( Object* parameter, ExecutionContext* context )
    {
        if( parameter->type_ == String )
        {
            StringObject* obj = reinterpret_cast<StringObject*>( parameter );
            std::string contents = obj->data_;
            int ret = system( contents.c_str() );
            return new IntObject( ret );
        }
        context->SetException( new StringObject( "Invalid parameter type to 'system' - a string is required" ) );
        return nullptr;
    }
};

class MapObject : public FunctionObject
{
public:
    Object* Call( Object* parameter, ExecutionContext* context )
    {
        if( parameter->type_ == List )
        {
            ListObject* argument = reinterpret_cast<ListObject*>( parameter );
            if( argument->contents_.size() != 2 ) {
                context->SetException( "`map` requires a list of two arguments" );
                return nullptr;
            }

            if( argument->contents_[1]->type_ != List ) {
                context->SetException( "`map` requires the second value in the argument list to be a list" );
                return nullptr;
            }
            ListObject* list = reinterpret_cast<ListObject*>( argument->contents_[1] );
            Object* functor = argument->contents_[0];
            functor = functor->Finalize( context );

            ListObject* output = new ListObject();
            for( Object* obj : list->contents_ ) {
                Object* result = functor->Call( obj, context );
                if( !result ) {
                    output->Release();
                    return nullptr;
                }
                result = result->Finalize( context );
                output->Append( result );
            }
            return output;
        }
        context->SetException( new StringObject( "Invalid parameter type to 'map' - a list is required" ) );
        return nullptr;
    }
};

void BuiltIns::SetupBuiltins( ExecutionContext* context )
{
    Object* obj;

    // Pre-Defined Variables
    ADD_BUILTIN( "True", BoolObject( true ) );
    ADD_BUILTIN( "False", BoolObject( false ) );
    ADD_BUILTIN( "None", NoneObject() );
    ADD_BUILTIN( "Pi", FloatObject( 3.1415926536 ) );
    ADD_BUILTIN( "e", FloatObject( 2.718281828 ) );
    // Print
    ADD_BUILTIN( "print", PrintObject() );
    ADD_BUILTIN( "println", PrintlnObject() );
    // Conversions
    ADD_BUILTIN( "bool", TruthObject() );
    ADD_BUILTIN( "str", StrObject() );
    ADD_BUILTIN( "int", IntFunctionObject() );
    ADD_BUILTIN( "float", FloatFunctionObject() );
    // List Operations
    ADD_BUILTIN( "len", LenObject() );
    ADD_BUILTIN( "map", MapObject() );

    ADD_BUILTIN( "readline", GetLineObject() );

    ADD_BUILTIN( "system", SystemObject() );
}