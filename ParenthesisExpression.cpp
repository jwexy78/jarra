#include "ParenthesisExpression.hpp"

ParenthesisExpression::ParenthesisExpression( Expression* content )
    : Expression( Parenthesis )
    , content_( content )
{}
ParenthesisExpression::~ParenthesisExpression()
{
    delete content_;
    content_ = nullptr;
}
std::ostream& ParenthesisExpression::operator<<( std::ostream& os )
{
    os << "[Parenthesis: "; *content_ << os; return os << "]";
}
Object* ParenthesisExpression::ToObject( ExecutionContext* context )
{
    Object* content = content_->ToObject( context );
    if( !content )
    {
        return nullptr;
    }
    content = content->Finalize( context );
    return content;
}
