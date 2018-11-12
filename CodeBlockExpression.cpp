#include "CodeBlockExpression.hpp"
#include "CodeBlockObject.hpp"

CodeBlockExpression::CodeBlockExpression( Expression* content )
    : Expression( CodeBlock )
    , content_( content )
{
}

CodeBlockExpression::~CodeBlockExpression()
{
}

std::ostream& CodeBlockExpression::operator<<( std::ostream& os )
{
    os << "[CodeBlock: "; *content_ << os; return os << "]";
}

Object* CodeBlockExpression::ToObject( ExecutionContext* context )
{
    return new CodeBlockObject( content_ );
}
