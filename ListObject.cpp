#include "ListObject.hpp"
#include "IntObject.hpp"
#include "StringObject.hpp"
#include "ExecutionContext.hpp"
#include "ReferenceObject.hpp"

ListObject::ListObject()
    : Object( Object::List )
    , finalized_( false )
{
}

ListObject::ListObject( Object* left, Object* right )
    : Object( List )
    , finalized_( false )
{
    Append( left );
    Append( right );
}

ListObject::ListObject( ListObject* other )
    : Object( List )
    , finalized_( other->finalized_ )
{
    for( auto i = other->contents_.begin(); i != other->contents_.end(); ++i )
    {
        Append( *i );
    }
}

std::string ListObject::ToString()
{
    if( !contents_.size() )
    {
        return "[]";
    }
    auto i = contents_.begin();
    std::string output = "[" + (*i)->ToString();
    ++i;
    for( ; i != contents_.end(); ++i )
    {
        output += ", " + (*i)->ToString();
    }
    return output + "]";
}

bool ListObject::BoolValue()
{
    return contents_.size() != 0;
}

Object* ListObject::Join( Object* other, ExecutionContext* context )
{
    if( finalized_ )
    {
        ListObject* joined = new ListObject( this, other );
        return joined;
    }
    else
    {
        ListObject* joined = new ListObject( this );
        joined->Append( other );
        return joined;
    }
}

void ListObject::Append( Object* other )
{
    other->Acquire();
    contents_.push_back( other );
}

Object* ListObject::Index( Object* other, ExecutionContext* context )
{
    if( other->type_ == Object::Int )
    {
        int index = reinterpret_cast<IntObject*>( other )->data_;
        if( index < 0 || index >= contents_.size() )
        {
            context->SetException( new StringObject( "Index " + std::to_string( index ) + " Out Of Bounds!" ) );
            return nullptr;
        }
        return new ReferenceObject( &contents_[index], this );
    }
    return ThrowIndexNotImplemented( other->type_, context );
}

ListObject* ListObject::Finalize( const ExecutionContext* )
{
    finalized_ = true;
    return this;
}

void ListObject::Destroy()
{    
    for( auto i = contents_.begin(); i != contents_.end(); ++i )
    {
        (*i)->Release();
    }
}