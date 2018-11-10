#include "SequenceExpression.hpp"

SequenceExpression::SequenceExpression( Expression* left, Expression* right )
    : Expression( Sequence )
    , left_( left )
    , right_( right )
{}
SequenceExpression::~SequenceExpression()
{
    delete left_;
    delete right_;
    left_ = nullptr;
    right_ = nullptr;
}
std::ostream& SequenceExpression::operator<<( std::ostream& os )
{
    os << "[Sequence: "; *left_ << os; os << ", "; *right_ << os; return os << "]";
}
Object* SequenceExpression::ToObject( ExecutionContext* context )
{
    Object* left = left_->ToObject( context );
    if( !left ) return nullptr;
    left = left->Finalize( context );
    left->Release();
    Object* right = right_->ToObject( context );
    if( !right )
        return nullptr;
    right = right->Finalize( context );
    return right;
}
