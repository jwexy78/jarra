#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <string>
#include <iostream>

#include "TypeToken.hpp"

/**
 * Class holding a complex token type
 * Types allowed:
 *  Int: An Integer
 *  Float: A floating-point number
 *  String: A sequence of characters
 *  QuotedString: A sequence of characters beginning and ending with "
 *  Operator: Anything else. Multi-char operators are allowed though
 */
class Token
{
public:
    enum TokenType {Int, Float, String, QuotedString, Operator};

    /**
     * Creates a new Token from a type and a content
     */
    Token( TokenType type, std::string content );

    /**
     * Creates a Token from a more basic TypeToken
     */
    Token( TypeToken typeToken );

    /**
     * Checks if the token has a specific type
     */
    bool operator==( const TokenType& type ) const;

    /**
     * Checks if a token has a given content as a string
     */
    bool operator==( const std::string& content ) const;

    /**
     * Checks if a token has a given content as a char
     */
    bool operator==( const char& content ) const;

    /**
     * Opposite of == for a char content
     */
    bool operator!=( const char& content ) const;

    /**
     * Returns a string that is this tokens content + some other string
     */
    std::string operator+( const std::string& content ) const;

    /**
     * Returns a string that is the concatenation of this token's content
     * and another token's content
     */
    std::string operator+( const Token& token ) const;

    /**
     * Returns a string that is the concatenation of a string and this token's content
     */
    friend std::string operator+( std::string string, const Token& token );

    friend std::ostream& operator<<( std::ostream& os, const Token& token );

    TokenType GetType();

    std::string GetContent();

    std::string GetTypeAsString() const;

private:
    TokenType type_;
    std::string content_;
};

#endif