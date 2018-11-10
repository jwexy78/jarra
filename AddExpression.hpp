#ifndef ADD_EXPRESSION_HPP
#define ADD_EXPRESSION_HPP

#include "Expression.hpp"
#include "Object.hpp"

class AddExpression : public Expression
{
public:
    AddExpression( Expression* left, Expression* right );
    ~AddExpression();
    std::ostream& operator<<( std::ostream& os );
    Object* ToObject( ExecutionContext* context );
protected:
    Expression* left_;
    Expression* right_;
};

#endif