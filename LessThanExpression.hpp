#ifndef LESSTHAN_EXPRESSION_HPP
#define LESSTHAN_EXPRESSION_HPP

#include "Expression.hpp"
#include "Object.hpp"

class LessThanExpression : public Expression
{
public:
    LessThanExpression( Expression* left, Expression* right );
    ~LessThanExpression();
    std::ostream& operator<<( std::ostream& os );
    Object* ToObject( ExecutionContext* context );
protected:
    Expression* left_;
    Expression* right_;
};

#endif