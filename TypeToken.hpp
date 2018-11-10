#ifndef TYPE_TOKEN_HPP
#define TYPE_TOKEN_HPP

#include <string>

/**
 * The most basic token type
 * Everything is either a string (sequence of characters starting with a letter)
 * or a number (sequence of numbers) or an operator (anything else)
 */
class TypeToken
{
public:
    enum TokenType {Number, String, Operator};
    
    /**
     * Creates a new TypeToken
     * @param type the type of the token (Number, String or Operator)
     * @param content the string content of the token
     */
    TypeToken( TokenType type, std::string content );

    /**
     * Creates a new TypeToken
     * @param type the type of the token (Number, String or Operator)
     * @param content the char content of the token
     */
    TypeToken( TokenType type, char content );

    /**
     * Gets the type of the token as a human-readable string
     * @return the type of the token as a string
     */
    std::string GetTypeAsString();

    TokenType type_;
    std::string content_;
};

#endif