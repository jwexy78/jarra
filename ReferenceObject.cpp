#include "ReferenceObject.hpp"

ReferenceObject::ReferenceObject( Object** reference, Object* root )
    : Object( Reference )
    , reference_( reference )
    , root_( root )
{
    root->Acquire();
}

std::string ReferenceObject::ToString()
{
    return "Reference!!! (This shouldn't ever happen)";
}

bool ReferenceObject::BoolValue()
{
    return false;
}

Object* ReferenceObject::Assign( Object* other, ExecutionContext* context )
{
    if( *reference_ )
    {
        (*reference_)->Release();
    }
    *reference_ = other;
    (*reference_)->Acquire();
    return other;
}

Object* ReferenceObject::Finalize( const ExecutionContext* )
{
    Object* toReturn = *reference_;
    toReturn->Acquire();
    Release();
    return toReturn;
}

void ReferenceObject::Destroy()
{    
    root_->Release();
}