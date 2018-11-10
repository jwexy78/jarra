#include "TypeToken.hpp"

TypeToken::TypeToken( TokenType type, std::string content )
    : type_( type )
    , content_( content )
{
}

TypeToken::TypeToken( TokenType type, char content )
    : type_( type )
    , content_( std::string() + content )
{
}

std::string TypeToken::GetTypeAsString()
{
    switch( type_ )
    {
        case Number:
            return "Number";
        case String:
            return "String";
        case Operator:
            return "Operator";
    }
}