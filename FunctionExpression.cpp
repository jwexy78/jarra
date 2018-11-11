#include "FunctionExpression.hpp"
#include "ExecutionContext.hpp"

FunctionExpression::FunctionExpression( Expression* caller, Expression* parameter )
    : Expression( Parenthesis )
    , caller_( caller )
    , parameter_( parameter )
{}
FunctionExpression::~FunctionExpression()
{
    delete caller_;
    caller_ = nullptr;
    delete parameter_;
    parameter_ = nullptr;
}
std::ostream& FunctionExpression::operator<<( std::ostream& os )
{
    os << "[Function: " ; *caller_ << os; os << ", "; *parameter_ << os; return os << "]";
}
Object* FunctionExpression::ToObject( ExecutionContext* context )
{
    Object* caller = caller_->ToObject( context );
    if( !caller )
    {
        return nullptr;
    }
    caller = caller->Finalize( context );
    context->EnterScope();
    Object* parameter = parameter_->ToObject( context );
    if( !parameter )
    {
        context->ExitScope();
        caller->Release();
        return nullptr;
    }
    parameter = parameter->Finalize( context );
    Object* ret = caller->Call( parameter, context );
    ret = ret->Finalize( context );
    caller->Release();
    parameter->Release();
    context->ExitScope();
    return ret;
}
