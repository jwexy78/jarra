#ifndef EXPRESSIONIZER_HPP
#define EXPRESSIONIZER_HPP

#include <vector>
#include <sstream>
#include "Expression.hpp"

class Expressionizer
{
public:
    /**
     * Converts a string into an Expression
     * @return if the string could be understood
     * Note that if an error occurs, `expression` will be set to nullptr
     */
    static bool Expressionize( std::string content, Expression*& expression, std::string& error, bool print );
};

#endif