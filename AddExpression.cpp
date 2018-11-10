#include "AddExpression.hpp"
#include "Logger.hpp"

AddExpression::AddExpression( Expression* left, Expression* right )
    : Expression( Add )
    , left_( left )
    , right_( right )
{}
AddExpression::~AddExpression()
{
    delete left_;
    delete right_;
    left_ = nullptr;
    right_ = nullptr;
}
std::ostream& AddExpression::operator<<( std::ostream& os )
{
    os << "[Add: "; *left_ << os; os << ", "; *right_ << os; return os << "]";
}
Object* AddExpression::ToObject( ExecutionContext* context )
{
    LOG( "evaluating left expression" );
    Object* left = left_->ToObject( context );
    if( !left )
    {
        LOG( "error occured in left expression" );
        return nullptr;
    }
    LOG( "evaluating right expression" );
    Object* right = right_->ToObject( context );
    if( !right )
    {
        LOG( "error occured in left expression" );
        left->Release();
        return nullptr;
    }
    left = left->Finalize();
    right = right->Finalize();
    LOG( "calling add on left = " + left->ToString() + ", right = " + right->ToString() );
    Object* ret = left->Add( right, context );
    left->Release();
    right->Release();
    return ret;
}
