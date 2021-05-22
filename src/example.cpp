#include <iostream>
#include "DebugLogger.h"

//example of using debug logger

/**
 * This is a header only library, so all you have to do is copy the headers into your project and you can use it!
 * The cmake code here is for compiling this demo
 * */
int main() {
    //create logger
    DebugLogger logger;

    //set prefix (prefix can only use internal variables and cannot deal with parameters)
    //prefixes can be set for each individual level, but this example won't deal with that as it's probably not an important feature
    //prefix follows the same formatting options as the normal trace prints
    logger.setPrefix("");
    logger.trace("notice how this only prints the text shown here, if we change the prefix it will change");

    //if we add a prefix, it appears before every log message (one can be set for each individual level, but again, we wont use that in this demo)
    //to use that, simply add a parameter indicating the level for the prefix
    logger.setPrefix("This is a prefix: ");
    logger.trace("This text should appear after the prefix");
    logger.setPrefix("");

    //now let's talk about internal variables
    //there are several internal variables indicated in the documentation.
    //to use these internal variables, use a double bracket -> [] and write the name of the variable inside [variableName]
    logger.trace("[lmc]: internal variable lmc(level message count) indicates the number of messages that have been sent to the current level");
    //there are many default internal variables (please read the documentation for more details)

    //these variables can be used in PREFIXES!
    //NOTE: the variable indicator can be escaped with itself, so [[ will output [ and ]] will output ]
    logger.setPrefix("[ln]-[[[lmc]]]: ");
    logger.trace("This prints the current level's name followed by a dash and the current number of messages in this level");

    //you can create your own internal variables!!
    //you just need a logger object, a pointer to the variable, as well as a type and size (int32 and int64 are DIFFERENT)
    int var1 = 100;
    long long var2 = 1000;
    //add the vars
    logger.addVariable("var1", &var1, DebugVarType::INTEGER32); //int32 because its a 32 bit integer
    logger.addVariable("var2", &var2, DebugVarType::INTEGER64); //this time its a 64 bit integer
    logger.trace("32 bit var: [var1], 64 bit var: [var2]");

    //PRINTING arguments
    //this works a lot like printf where you write the format, and pass each variable in separately
    //there are various types of varaibles that can be printed indicated in the documentation. Each one has its printf alias and a more readable version
    //use a variable with curly braces. These can be escaped in the same was as the brackets
    logger.trace("char: ({char}), int: ({d}), another int: ({int})", 'B', 16, -1);

    //FORMATING options
    //each argument and variable is formatted the exact same way, but the available formatting options vary between types
    //for details on this, read the docs. Invalid formatting options will be ignored. Repeated options will be overridden
    logger.trace("Takes 10 spaces ({10d}), 10 spaces right justified ({>10d})", 10, 10);
    //notice how the arguments took up the same space, but the '>' told the system to move the text to the right
    //another example
    logger.trace("Lots of options on string: ({10>^str}), unsigned int: ({+d}), another unsigned int: ({u})", "text", -1, -1);
    //'^' capitalizes the string or char, '+' makes an integer unsigned. You can also use the unsigned types like: uint, u, ulong, ul, etc

    //you can see the same formatting options can be applied to variables
    //let me show you how to lowercase the text with '$'
    logger.trace("normal: [ln], formatted: [$ln]");

    //formatting options may be applied in any order as long as they don't conflict. The main one that could conflict is the fill zero formatter.
    //that one is marked with a 0, so what could happen is if you put that right after the space option, it will treat it as part of the number
    //heres how to use it properly and how to print in hex
    logger.trace("0x{>08xint}, 0x{X0long 16}", 0xDEAD, 0xBEEF);
    //by putting the zero specified before the space count, it treated it properly. As well as that, putting it after the x also works
    //notice how it doesn't matter where you put the space parameter as long as it cannot be confused with the type specifier or variable name. That's why there must be a space if you put it after
    //NOTE: the capitalization doesn't work on hex numbers. You have to use lowercase x or X to change the case.

    //FORMATTING floats

    //lets combine what we learned 
    //this is the default prefix. 
    //prints the name with 3 characters, prints the elapsed time in milliseconds to 2 decimal places, then prints the current level's message count with five digits filling in zeros
    logger.setPrefix("[3ln]~[.2etl] [[[>05lmc]]]: ");
    double testVar = 100.156;
    logger.addVariable("testVar", &testVar, DebugVarType::FLOAT64);

    //there is one more spacing option for floats. If you add a number after a decimal point, then it indicates the number of spaces taken by the decimals
    //.2 would indicate 2 decimals of precision.
    //the first number in the spacing represents the total amount of space used by the float. For example 10.2 will use 10 spaces min, but will use at most 2 decimal places of precision
    logger.trace("{str}: ([10.2testVar])", "Current testVar value");
    testVar = -0.12338;
    logger.trace("{str}: [.4testVar], param 2 {{{>+3uint}}}, capitalized char: {^char}", "Now it's something different", 10, 'a');

    //print the total program time using internal variables
    //this prints the total time in milliseconds
    logger.trace("The program has taken [.2tl]");

    //of course you can use the other levels such as warning, critical, and error
    //this tutorial only made use of trace
    //this may seem harder to read than printf, but it's actually more logical, more customizable with the prefix and variables, and provides a couple more formatting options.
    //its a learning curve in the same way as printf, but it's better in many ways except speed. It compares to cout in terms of speed.

    return 0;
}