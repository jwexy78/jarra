#ifndef TRY_EXPRESSION_HPP
#define TRY_EXPRESSION_HPP

#include "Expression.hpp"
#include "Object.hpp"

class TryExpression : public Expression
{
public:
    TryExpression( Expression* condition, Expression* block );
    ~TryExpression();
    std::ostream& operator<<( std::ostream& os );
    Object* ToObject( ExecutionContext* context );
protected:
    Expression* condition_;
    Expression* block_;
};

#endif