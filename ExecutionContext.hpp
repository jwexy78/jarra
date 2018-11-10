#ifndef EXECUTION_CONTEXT_HPP
#define EXECUTION_CONTEXT_HPP

#include <unordered_map>
#include <vector>
#include "Object.hpp"

class ExecutionContext
{
public:
    ExecutionContext();
    ~ExecutionContext();
    /**
     * Sets an exception, if one is not already set
     */
    void SetException( Object* exception );
    Object* GetException();
    void ClearException();

    /**
     * Set a variable in the current scope
     */
    void SetVariable( std::string key, Object* value );

    /**
     * Get a reference to a variable, searching from the given scope down
     * or the top scope if the given scope is negative
     */
    Object* GetVariable( std::string key, int maxScope = -1 ) const;

    /**
     * Enter a new variable scope.
     * All new variables will now be made in the new scope
     */
    void EnterScope();

    /**
     * Leaves the last-level variable scope.
     * Erases all variables made in the old scope
     */
    void ExitScope();

    /**
     * Get the level of the current scope
     */
    int GetCurrentScope() const;

private:
    Object* exception_;
    std::vector<std::unordered_map<std::string,Object*> > scopes_;
};

#endif