#include "DivideExpression.hpp"

DivideExpression::DivideExpression( Expression* left, Expression* right )
    : Expression( Divide )
    , left_( left )
    , right_( right )
{}
DivideExpression::~DivideExpression()
{
    delete left_;
    delete right_;
    left_ = nullptr;
    right_ = nullptr;
}
std::ostream& DivideExpression::operator<<( std::ostream& os )
{
    os << "[Divide: "; *left_ << os; os << ", "; *right_ << os; return os << "]";
}
Object* DivideExpression::ToObject( ExecutionContext* context )
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
    Object* ret = left->Divide( right, context );
    left->Release();
    right->Release();
    return ret;
}
