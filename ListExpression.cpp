#include "ListExpression.hpp"
#include "ListObject.hpp"

ListExpression::ListExpression( Expression* left, Expression* right )
    : Expression( Sequence )
    , left_( left )
    , right_( right )
{}
ListExpression::~ListExpression()
{
    delete left_;
    delete right_;
    left_ = nullptr;
    right_ = nullptr;
}
std::ostream& ListExpression::operator<<( std::ostream& os )
{
    os << "[List: "; *left_ << os; os << ", "; *right_ << os; return os << "]";
}
Object* ListExpression::ToObject( ExecutionContext* context )
{
    Object* left = left_->ToObject( context );
    if( !left )
    {
        return nullptr;
    }
    Object* right = right_->ToObject( context );
    if( !right )
    {
        left->Release();
        return nullptr;
    }
    if( left->type_ == Object::List )
    {
        ListObject* leftAsList = reinterpret_cast<ListObject*>( left );
        return leftAsList->Join( right, context );
    }
    else
    {
        ListObject* list = new ListObject();
        list->Append( left );
        list->Append( right );
        return list;
    }
}
