#ifndef TOKENIZER_HPP
#define TOKENIZER_HPP

#include <vector>
#include <string>
#include "Token.hpp"

class Tokenizer
{
public:
    /**
     * Tokenize a string into a list of Tokens
     */
    static std::vector<Token> Tokenize( std::string content );
};

#endif