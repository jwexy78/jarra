#include "WeakReferenceObject.hpp"
#include "StringObject.hpp"
#include "Logger.hpp"
#include "NoneObject.hpp"
#include "ExecutionContext.hpp"

WeakReferenceObject::WeakReferenceObject( int scope, std::string name, Object* root )
    : Object( Object::WeakReference )
    , scope_( scope )
    , name_( name )
    , root_( root )
{
    if( root_ )
    {
        root_->Acquire();
    }
}
std::string WeakReferenceObject::ToString()
{
    return "WeakReference @ " + THIS_STR;
    return "WeakReference (SHOULD NEVER APPEAR)";
}
bool WeakReferenceObject::BoolValue()
{
    return false;
}
Object* WeakReferenceObject::Assign( Object* other, ExecutionContext* context )
{
    LOG( "assigning weak reference @ " + THIS_STR );
    context->SetVariable( name_, other );
    return other;
}
Object* WeakReferenceObject::Finalize( const ExecutionContext* context )
{
    LOG( "finalizing weak reference @ " + THIS_STR );
    return context->GetVariable( name_, scope_ );
}

void WeakReferenceObject::Destroy()
{    
    if( root_ )
    {
        root_->Release();
    }
}
