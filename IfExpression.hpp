#ifndef IF_EXPRESSION_HPP
#define IF_EXPRESSION_HPP

#include "Expression.hpp"
#include "Object.hpp"

class IfExpression : public Expression
{
public:
    IfExpression( Expression* condition, Expression* block );
    ~IfExpression();
    std::ostream& operator<<( std::ostream& os );
    Object* ToObject( ExecutionContext* context );
protected:
    Expression* condition_;
    Expression* block_;
};

#endif