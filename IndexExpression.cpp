#include "IndexExpression.hpp"

IndexExpression::IndexExpression( Expression* caller, Expression* parameter )
    : Expression( Index )
    , caller_( caller )
    , parameter_( parameter )
{}
IndexExpression::~IndexExpression()
{
    delete caller_;
    caller_ = nullptr;
    delete parameter_;
    parameter_ = nullptr;
}
std::ostream& IndexExpression::operator<<( std::ostream& os )
{
    os << "[Index: " ; *caller_ << os; os << ", "; *parameter_ << os; return os << "]";
}
Object* IndexExpression::ToObject( ExecutionContext* context )
{
    Object* caller = caller_->ToObject( context );
    if( !caller )
    {
        return nullptr;
    }
    Object* parameter = parameter_->ToObject( context );
    if( !parameter )
    {
        caller->Release();
        return nullptr;
    }
    caller = caller->Finalize();
    parameter = parameter->Finalize();
    Object* ret = caller->Index( parameter, context );
    caller->Release();
    parameter->Release();
    return ret;
}
