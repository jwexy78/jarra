#include "WeakReferenceObject.hpp"
#include "StringObject.hpp"
#include "Logger.hpp"
#include "NoneObject.hpp"

WeakReferenceObject::WeakReferenceObject( std::unordered_map<std::string,Object*>* reference, std::string name, Object* root )
    : Object( Object::WeakReference )
    , reference_( reference )
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
    auto itr = reference_->find( name_ );
    if( itr != reference_->end() && itr->second )
    {
        (itr->second)->Release();
    }
    (*reference_)[name_] = other;
    other->Acquire();
    return other;
}
Object* WeakReferenceObject::Finalize()
{
    LOG( "finalizing weak reference @ " + THIS_STR );
    auto itr = reference_->find( name_ );
    if( itr != reference_->end() && itr->second )
    {
        (itr->second)->Acquire();
        Release();
        return itr->second;
    }
    return new NoneObject();
    return nullptr; // *** NOTE! The Error Message Must be Set By Whatever Calls This!
}

void WeakReferenceObject::Destroy()
{    
    if( root_ )
    {
        root_->Release();
    }
}
