#include "EqualsExpression.hpp"
#include "BoolObject.hpp"

EqualsExpression::EqualsExpression( Expression* left, Expression* right )
    : Expression( Equals )
    , left_( left )
    , right_( right )
{}
EqualsExpression::~EqualsExpression()
{
    delete left_;
    delete right_;
    left_ = nullptr;
    right_ = nullptr;
}
std::ostream& EqualsExpression::operator<<( std::ostream& os )
{
    os << "[Equals: "; *left_ << os; os << ", "; *right_ << os; return os << "]";
}
Object* EqualsExpression::ToObject( ExecutionContext* context )
{
    Object* left = left_->ToObject( context );
    if( !left ) return nullptr;
    Object* right = right_->ToObject( context );
    if( !right )
    {
        left->Release();
        return nullptr;
    }
    left = left->Finalize( context );
    right = right->Finalize( context );
    BoolObject* ret = left->Equals( right, context );
    left->Release();
    right->Release();
    return ret;
}
