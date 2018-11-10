#include "Expressionizer.hpp"
#include "Interpreter.hpp"
#include "Logger.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <streambuf>

#define NAME "Jarra"
#define VERSION "0.0.2"

int main( int argc, char** argv )
{
    Interpreter interpreter;

    bool runFile = false;
    std::string filename;

    bool print = false;
    bool printHeader = true;

    bool runScript = false;
    std::string script;

    bool runInteractive = true;
    bool printResults = true;

    Logger::Log( NAME " main() starting" );

    for( int i = 1; i < argc; ++i )
    {
        Logger::Log( "Processing Flag: " + std::string( argv[i] ) );
        if( !strcmp( argv[i], "-p" ) )
        {
            print = true;
        }
        else if( !strcmp( argv[i], "-f" ) )
        {
            runFile = true;
            printHeader = false;
            filename = argv[i+1];
            i++;
            runInteractive = false;
            printResults = false;
        }
        else if( !strcmp( argv[i], "-s" ) )
        {
            runScript = true;
            printHeader = false;
            script = argv[i+1];
            i++;
            runInteractive = false;
            printResults = false;
        }
        else if( !strcmp( argv[i], "-i" ) )
        {
            runInteractive = true;
        }
        else if( !strcmp( argv[i], "-r" ) )
        {
            printResults = true;
        }
        else if( !strcmp( argv[i], "-nh" ) )
        {
            printHeader = false;
        }
        else
        {
            std::cerr << "'" << argv[i] << "' is not a valid flag\n";
            return 1;
        }
    }

    std::string output;
    std::string error;

    if( runFile )
    {
        std::ifstream ostr( filename );
        std::stringstream buffer;
        buffer << ostr.rdbuf();

        std::string contents = buffer.str();

        Logger::Log( "Running File: '" + filename + "'" );

        Interpreter::ExecutionResult result = interpreter.Run( contents, output, error, false );
        if( result == Interpreter::ExecutionResult::OK )
        {
            if( printResults )
            {
                std::cout << output << "\n";
            }
        }
        else
        {
            std::cout << error << "\n";
            return 1;
        }
    }

    if( runScript )
    {
        Interpreter::ExecutionResult result = interpreter.Run( script, output, error, false );
        if( result == Interpreter::ExecutionResult::OK )
        {
            if( printResults )
            {
                std::cout << output << "\n";
            }
        }
        else
        {
            std::cout << error << "\n";
            return 1;
        }
    }

    if( runInteractive )
    {
        if( printHeader )
        {
            std::cout << NAME " Interpreter\nVersion " VERSION "\n";
        }
        std::string str;
        while( getline( std::cin, str ) )
        {
            Interpreter::ExecutionResult result = interpreter.Run( str, output, error, false );
            if( result == Interpreter::ExecutionResult::OK )
            {
                if( printResults )
                {
                    std::cout << output << "\n";
                }
            }
            else if( result == Interpreter::ExecutionResult::PARSE_ERROR )
            {
                std::cout << "Parse Error: " << error << "\n";
            }
            else if( result == Interpreter::ExecutionResult::RUNTIME_ERROR )
            {
                std::cout << "Runtime Error: " << error << "\n";
            }
        }
    }
}