#include "Expressionizer.hpp"
#include "Token.hpp"
#include "Tokenizer.hpp"
#include "UnknownExpression.hpp"

void RemoveWhitespaceTokens( std::vector<Token>& tokens )
{
    auto i = tokens.begin();
    while( i != tokens.end() )
    {
        if( *i == ' ' || *i == '\n' || *i == '\t' )
        {
            tokens.erase( i );
        }
        else
        {
            ++i;
        }
    }
}

bool Expressionizer::Expressionize( std::string content, Expression*& expression, std::string& error, bool print )
{
    std::vector<Token> tokens = Tokenizer::Tokenize( content );
    RemoveWhitespaceTokens( tokens );
    UnknownExpression unknownExpression( tokens );
    error = "";
    Expression* knownExpression = unknownExpression.ToKnownExpression( error );
    if( print )
    {
        std::cout << knownExpression << "\n";
    }

    if( error.length() )
    {
        // If an error occured
        delete knownExpression;
        expression = nullptr;
        return false;
    }
    else
    {
        expression = knownExpression;
        error = "";
        return true;
    }
}