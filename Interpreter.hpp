#ifndef INTERPRETER_H_
#define INTERPRETER_H_

#include <unordered_map>
#include <exception>
#include "Expressionizer.hpp"
#include "Object.hpp"
#include "BuiltIns.hpp"

class Interpreter
{
public:
    enum ExecutionResult { OK, PARSE_ERROR, RUNTIME_ERROR };
    static std::string QuickRun( std::string script );    

    Interpreter();
    ~Interpreter();

    ExecutionResult Run( std::string script, std::string& output, std::string& error, bool print = false );

private:
    ExecutionContext* context_;
};

#endif