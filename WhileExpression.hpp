#ifndef WHILE_EXPRESSION_HPP
#define WHILE_EXPRESSION_HPP

#include "Expression.hpp"
#include "Object.hpp"

class WhileExpression : public Expression
{
public:
    WhileExpression( Expression* condition, Expression* block );
    ~WhileExpression();
    std::ostream& operator<<( std::ostream& os );
    Object* ToObject( ExecutionContext* context );
protected:
    Expression* condition_;
    Expression* block_;
};

#endif