#include "VariableExpression.hpp"
#include "ExecutionContext.hpp"
#include "StringObject.hpp"
#include "WeakReferenceObject.hpp"

VariableExpression::VariableExpression( std::string value )
    : Expression( Variable )
    , value_( value )
{}
std::ostream& VariableExpression::operator<<( std::ostream& os )
{
    return os << "[Variable: " << value_ << "]";
}
Object* VariableExpression::ToObject( ExecutionContext* context )
{
    WeakReferenceObject* reference = new WeakReferenceObject( context->GetCurrentScope(), GetValue(), nullptr );
    return reference;
    /*
    Object* value = context->GetVariable( GetValue() );
    if( !value )
    {
        context->SetException( new StringObject( "Variable '" + GetValue() + "' has no value" ) );
        return nullptr;
    }
    return value;
    */
}
std::string VariableExpression::GetValue()
{
    return value_;
}
