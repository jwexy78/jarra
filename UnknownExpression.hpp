#ifndef UNKNOWN_EXPRESSION_HPP
#define UNKNOWN_EXPRESSION_HPP

#include "Expression.hpp"
#include "Token.hpp"
#include <vector>
#include <sstream>

class UnknownExpression : public Expression
{
public:
    UnknownExpression( std::vector<Token> );
    Expression* ToKnownExpression( std::string& );
    std::ostream& operator<<( std::ostream& os );
    std::stringstream& operator<<( std::stringstream& os );
    Object* ToObject( ExecutionContext* );

private:
    std::vector<Token> tokens_;
};



#endif