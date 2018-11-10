#ifndef LIST_EXPRESSION_HPP
#define LIST_EXPRESSION_HPP

#include "Expression.hpp"
#include "Object.hpp"

class ListExpression : public Expression
{
public:
    ListExpression( Expression* left, Expression* right );
    ~ListExpression();
    std::ostream& operator<<( std::ostream& os );
    Object* ToObject( ExecutionContext* context );
protected:
    Expression* left_;
    Expression* right_;
};

#endif