#ifndef ASSIGN_EXPRESSION_HPP
#define ASSIGN_EXPRESSION_HPP

#include "Expression.hpp"
#include "Object.hpp"

class AssignExpression : public Expression
{
public:
    AssignExpression( Expression* left, Expression* right );
    ~AssignExpression();
    std::ostream& operator<<( std::ostream& os );
    Object* ToObject( ExecutionContext* context );
protected:
    Expression* left_;
    Expression* right_;
};

#endif