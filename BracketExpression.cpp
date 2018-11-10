#include "BracketExpression.hpp"
#include "ListObject.hpp"

BracketExpression::BracketExpression( Expression* content )
    : Expression( Bracket )
    , content_( content )
{}
BracketExpression::~BracketExpression()
{
    delete content_;
    content_ = nullptr;
}
std::ostream& BracketExpression::operator<<( std::ostream& os )
{
    os << "[Brackets: "; *content_ << os; return os << "]";
}
Object* BracketExpression::ToObject( ExecutionContext* context )
{
    if( content_->type_ == Expression::Empty )
    {
        return (new ListObject())->Finalize();
    }
    Object* content = content_->ToObject( context );
    if( !content )
    {
        return nullptr;
    }
    if( content->type_ == Object::List && !reinterpret_cast<ListObject*>( content )->finalized_ )
    {
        // If it's an infinalized list such as 'a,b', the []'s are just
        // order of operations, so do nothing
        content = content->Finalize();
        return content;
    }
    else
    {
        // Otherwise, put content in a new list and return the list
        content = content->Finalize();
        ListObject* lobj = new ListObject();
        lobj->Append( content );
        content->Release();
        lobj = lobj->Finalize();
        return lobj;
    }
}
