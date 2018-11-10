#ifndef SEQUENCE_EXPRESSION_HPP
#define SEQUENCE_EXPRESSION_HPP

#include "Expression.hpp"
#include "Object.hpp"

class SequenceExpression : public Expression
{
public:
    SequenceExpression( Expression* left, Expression* right );
    ~SequenceExpression();
    std::ostream& operator<<( std::ostream& os );
    Object* ToObject( ExecutionContext* context );
protected:
    Expression* left_;
    Expression* right_;
};

#endif