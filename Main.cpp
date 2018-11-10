#include "Expressionizer.hpp"
#include "Interpreter.hpp"
#include "Logger.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <streambuf>

#define NAME "Jarra"
#define VERSION "0.0.2"

// Command-line variables
bool runScript = false;
std::string script;

bool runFile = false;
std::string filename;

bool runInteractive = true;

bool printResults = true;

bool printHeader = true;

void printUsage()
{
    std::cout << "\n\tUsage: ./jarra [file] [flags...]\n\n";
    std::cout << "\t\t-nh: don't print the jarra header\n";
    std::cout << "\t\t-help: show the help menu\n";
    std::cout << "\n";
}

bool parseArgs( int argc, char** argv )
{
    if( argc == 1 ) {
        return true;
    }
    int flagStart = 1;
    // Check if first arg is a file
    if( argv[1][0] != '-' ) {
        runFile = true;
        filename = argv[1];
        printResults = false;
        runInteractive = false;
        printHeader = false;
        flagStart = 2;
    }

    for( int i = flagStart; i < argc; ++i )
    {
        if( !strcmp( argv[i], "-i" ) ) {
            runInteractive = true;
        } else if( !strcmp( argv[i], "-nh" ) ) {
            printHeader = false;
        } else if( !strcmp( argv[i], "-s" ) ) {
            runScript = true;
            i++;
            script = argv[i];
            runInteractive = false;
        } else {
            return false;
        }
    }
    return true;
}

int main( int argc, char** argv )
{
    Interpreter interpreter;

    if( !parseArgs( argc, argv ) ) {
        printUsage();
        return 1;
    }

    Logger::Log( NAME " main() starting" );

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