#include "ExecutionContext.hpp"
#include "Object.hpp"

ExecutionContext::ExecutionContext()
    : exception_( nullptr )
{
    // Push a base Global scope
    scopes_.push_back( std::unordered_map<std::string,Object*>() );
}

ExecutionContext::~ExecutionContext()
{
    while( scopes_.size() )
    {
        ExitScope();
    }
}

void ExecutionContext::SetException( Object* exception )
{
    if( !exception_ )
    {
        exception_ = exception;
    }
    else
    {
        exception->Release();
    }
}

Object* ExecutionContext::GetException()
{
    return exception_;
}

void ExecutionContext::ClearException()
{
    if( exception_ )
    {
        exception_->Release();
    }
    exception_ = nullptr;
}

void ExecutionContext::SetVariable( std::string key, Object* value )
{
    std::unordered_map<std::string,Object*>& scope = scopes_[scopes_.size() - 1];
    // If the key had an old Object value, release it.
    if( scope.find( key ) != scope.end() )
    {
        scope[key]->Release();
    }
    // Acquire and insert the value
    value->Acquire();
    scope[key] = value;
}

Object* ExecutionContext::GetVariable( std::string key, int maxScope ) const
{
    if( maxScope < 0 ) {
        maxScope = scopes_.size() - 1;
    }
    if( maxScope > scopes_.size() - 1 ) {
        maxScope = scopes_.size() - 1;
    }
    // Look through each scope for the variable, top town
    for( int i = maxScope; i >= 0; --i )
    {
        auto itr = scopes_[i].find( key );
        if( itr != scopes_[i].end() )
        {
            Object* var = itr->second;
            var->Acquire();
            return var;
        }
    }
    return nullptr;
}

void ExecutionContext::EnterScope()
{
    // Push an empty scope onto scopes
    scopes_.push_back( std::unordered_map<std::string,Object*>() );
}

void ExecutionContext::ExitScope()
{
    // Pop the highest scope, and releases every item in the scope
    std::unordered_map<std::string,Object*>& scope = scopes_[scopes_.size() - 1];
    for( auto i = scope.begin(); i != scope.end(); ++i )
    {
        i->second->Release();
    }
    scopes_.erase(scopes_.begin() + (scopes_.size() - 1) );
}

int ExecutionContext::GetCurrentScope() const
{
    return scopes_.size() - 1;
}