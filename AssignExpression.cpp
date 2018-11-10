#include "AssignExpression.hpp"
#include "VariableExpression.hpp"
#include "ReferenceObject.hpp"
#include "ExecutionContext.hpp"
#include "StringObject.hpp"

AssignExpression::AssignExpression( Expression* left, Expression* right )
    : Expression( Assign )
    , left_( left )
    , right_( right )
{}
AssignExpression::~AssignExpression()
{
    delete left_;
    delete right_;
    left_ = nullptr;
    right_ = nullptr;
}
std::ostream& AssignExpression::operator<<( std::ostream& os )
{
    os << "[Assign: "; *left_ << os; os << ", "; *right_ << os; return os << "]";
}
Object* AssignExpression::ToObject( ExecutionContext* context )
{
    /*
    if( left_->type_ == Variable )
    {
        Object* right = right_->ToObject( context );
        if( !right ) return nullptr;
        right = right->Finalize();
        context->SetVariable( reinterpret_cast<VariableExpression*>( left_ )->GetValue(), right );
        return right;
    }
    */
    Object* left = left_->ToObject( context );
    if( !left )
    {
        return nullptr;
    }
    if( left->type_ == Object::Reference || left->type_ == Object::WeakReference )
    {
        Object* right = right_->ToObject( context );
        if( !right )
        {
            left->Release();
            return nullptr;
        }
        right = right->Finalize();
        Object* toReturn = left->Assign( right, context );
        toReturn = toReturn->Finalize();
        return toReturn;
    }
    context->SetException( new StringObject( "Expected Variable or Reference on left side of assignment" ) );
    return nullptr;
}
