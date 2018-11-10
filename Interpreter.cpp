#include "Interpreter.hpp"
#include "Logger.hpp"

Interpreter::Interpreter()
    : context_( new ExecutionContext() )
{
    BuiltIns::SetupBuiltins( context_ );
}

Interpreter::~Interpreter()
{
    delete context_;
}

Interpreter::ExecutionResult Interpreter::Run( std::string script, std::string& output, std::string& error, bool print )
{
    LOG( "Running Script: " + script );
    Expression* expression = nullptr;
    if( !Expressionizer::Expressionize( script, expression, error, print ) )
    {
        LOG( "Failed to parse expression: " + error );
        return Interpreter::PARSE_ERROR;
    }

    Object* evaluated = expression->ToObject( context_ );
    delete expression;

    if( context_->GetException() )
    {
        error = context_->GetException()->ToString();
        context_->ClearException();
        output = "";
        LOG( "Runtime Error: " + error );
        return Interpreter::RUNTIME_ERROR;
    }
    evaluated = evaluated->Finalize( context_ );

    error = "";
    output = evaluated->ToString();
    evaluated->Release();
    LOG( "Execution Terminated with Result: " + output );
    return Interpreter::OK;
}