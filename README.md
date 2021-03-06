# Jarra
Version 0.0.3

The Jarra language is designed to be an imperitive, interpreted language where all code is the composition of primitive types and operators. The design is that everything is interpreted the same way regardless of context, which can be a little different from other languages.

## Syntax Overview

### Primitives

##### Int
Represents a standard 32-bit Integer. An integer is coded as a series of numerical numbers (0-9) in sequence NOT followed by a '.', possibly preceded by a '-' for negative numbers. The following are examples.

    5
    1234
    -567

##### Double
Represents a C Double. A double is coded the same as an Integer, but with a '.'. Examples:

    12.34
    -.009

##### String
Represents a sequence of characters. A String is coded as a series of characters inside of quotations.

    "hello!"
    "This is a string!"

##### Boolean
A boolean represents a value that is either True or False. For convenience, the `True` and `False` variables are defined as the True and False boolean values, however, they may be reassigned by bad programmers. We will assume this is not done though for the rest of the document.

##### None
The None primitive represents the lack of a value. Similar to Boolean, the `None` variable is initially set to the None primitive, but may be reassigned.

### Operators

As mentioned previously, everything in Jarra is the application of operators on primitives. Here is a rundown of the various primitive operators available. Note that, when an operator expects a left and right value, it will assume the `None` type if none is present.

##### `+`
Add two values. Numerical addition is used for numbers, concatenation is done for strings.

    4 + 2.3
        6.3
    "hello!" + 5
        "hello!5"
        
##### `-`
Subtract a number from another number.

    4-45
        -41
    3--4
        7
        
##### `*`
Multiple a number by another number. `String`*`Integer` also returns a string that is the initial string repeated `Integer` times.

    4 * 6
        24
    "a" * 5 
        "ababababab"

##### `/`
Divide a number by another number. Note that standard integer devision rules apply.

    100/5
        20
    6/4
        1
    6/4.0
        1.5
    
##### `==`
Checks for equality among two items.

    1.0 == 1
        True
    5 == 1
        False
    "abc" == "abc"
        True
    "abc" == 5
        False
    5 == "5"
        False

##### `&&`
Performs the logical `and` of two items. Note that every type has an implicit "truthy" value, so this may be used with all types.

    True && False
        False
    True && True
        True
    4 && 3
        True
    0 && 2
        False
    -1.1 && 2.3
        True
    "a" && ""
        False

##### `||`
Performs the logical `or` of two items. Note that every type has an implicit "truthy" value, so this may be used with all types.

    True || False
        True
    False || False
        False
    None || 1
        True

##### `()`
Parenthesis require the contained expression 
to be evaluated before operators are applied to whatever is returned by the `()`.

    2 * 3 + 4
        10
    2 * (3 + 4)
        14
    ()
        None
    
##### `!`
Performs the logical `not` on whatever follows.

    !False
        True
    !2
        False

##### `=`
Assigns a value to a variable, then returns the assigned value.

    a = 5
        5
    myVar = "abc"
        "abc"

##### `;`
The semicolon is the sequence operator. The left side expression is computed first; the result is discarded. Then, the right hand expression is computed and returned.

    1 ; 2
        2
    1 ; 2 ;
        None
    a = 5; a + 1
        6
    a = ( 5; 6 )
        6
    a = 6; b = ( a = a + 1; a ); b
        7

### Lists
A list is an ordered collection of other Jarra objects. A list can be made by using a comma `,` operator between two items, or by placing zero or 1 item(s) in brackets (`[]`). 
    `[]` is an empty list
    `[1]` is a list containing one element, the number 1
    `1,2` is a list containing two elements, the numbers 1 and 2
    `[1,2]` is the same as the above
    `1,2,3` is a list containing three elements
    `[1,2],3` is a list with two elements, a list of two elements as the first and the Integer 3 as the second
    `[[[]]]` is a list containing one item, which is a list containing one item, which is an empty list.
    
Items in a list can be accessed via the `[]` index operator when placed after the list. For example:

    [1,2,3][1]
        2
    [[1,2],3][0]
        [1,2]
    [[]][0]
        []

### Control Flow

##### `if`
The `if` operator allows a block of code to be executed only if some condition evaluates to true. It returns `None` if the condition is false, or the contained expression's result otherwise. The syntax is as follows.

    if( True ) { 5 }
        5
    if( False ) { 5 }
        None
Because of Jarra's "Everything is an operator" mentality, things like the following are valid.

    a = True; a = if( a ) { 5 }; a
        5
    a = False; a = if( a ) { 5 }; a
        None
    
##### `while`
The `while` keyword continues to execute the body of the expression while the condition evaluates to `True`. It returns the result of the last iteration of the loop run, or `None` if the loop is never run.

    a = 0; b = 0; while( !( a == 5 ) ) { a = a + 1; b = b - 1; b }
        -5

### Code Blocks

A code block is a Jarra object that references an expression but does not execute it. Any expression only wrapped in braces `{}` is a code block, and it can be passed around like a variable. To execute the block, the function operator (`()` after the block) is called. For example:

    { 1 + 2 }()
        3
    a = { 1 + 2 }; a()
        3
    a = { b }; a()
        None
    a = { b }; b = "hello!"; a()
        "hello!"

##### Variable Scoping
In Jarra, code blocks can be used similarly to functions in other languages. Unlike most languages though, Jarra does not have explicit parameters for these blocks. Instead, a variable scoping paradigm is used. Before the parameter of a function is executed, a new scope is created. The block is called in the new scope, and then the scope is deleted after the block returns. Note that because of this, code blocks cannot modify variables in an external scope, but they may read them.

    a = { b }; a( b = 2 )
        2
    a = { b = 4 }; b = 2; a(); b
        2
    a = { x + 1 }; a( x = 2 ) + a( x = 6 )
        10

### Built In Functions

In addition to code blocks, Jarra offers a number of built in functions.

##### `print`

Prints the string representation of an argument.

##### `println`

Prints the string representation of an argument, followed by a new line character.

##### `bool`

Converts the argument to a Boolean.

##### `str`

Converts the argument to a String.

##### `int`

Converts the argument to an Integer.

##### `float`

Converts the argument to a Float.

##### `len`

Returns the length of a list passed in as the argument.

##### `map`

Maps a function to a list. For convenience, it takes a single list of two elements where the second element is a list and returns a list containing the first element in the argument list called on every element in the second's list.

    map(int,["1","45","23"])
        [1, 45, 23]