#include <ostream>

//     ####  WARNING  ####
// This file contains the character ESC character (\033 in octal 0x1B in hex)
// in raw, unescaped form. This may cause problems if you try to 'cat' the file,
// or other some editors which expect everything to contain nice, neat, human-readable
// characters.

const char* HELP_MESSAGE_COLORED = R"(
[1;30;107m                                                          [0m
[1;30;107m                 THE  MAGNIFICENT  ONLINE                 [0m
[1;30;107m                 COMMAND-LINE  CALCULATOR                 [0m
[1;30;107m                                                          [0m
    
Please help me to debug it by throwing everything you can 
at it. Submit bugs or ideas to the following GitHub repo:
   * [4;36mhttp://www.github.com/IQAndreas/eval.cpp[0m
    
[1mExamples[0m
    
  [1;39m  1 + 2         [0m
  [1;93m  > 3           [0m
  [1;39m  1+(-20)*46/-2 [0m
  [1;93m  > 437         [0m
   
[1mAllowed operators[0m
    
    [1;92m+[0m Addition
    [1;91m-[0m Subtraction
    [1;93m*[0m Multiplication
    [1;94m/[0m Division [37m(integer division only!)[0m
    
    [1;37mparentheses[0m determine the order of operations
    [1;97mspaces[0m between numbers and operators are ignored
  
Only integers are allowed at the current time (no floats) but this may change.
    
Press [1;37mCTRL+C[0m at any time to exit the program.
)";

const char* HELP_MESSAGE = R"(
                                                          
                 THE  MAGNIFICENT  ONLINE                 
                 COMMAND-LINE  CALCULATOR                 
                                                          
    
Please help me to debug it by throwing everything you can 
at it. Submit bugs or ideas to the following GitHub repo:
   * http://www.github.com/IQAndreas/eval.cpp
    
Examples
    
    1 + 2         
    > 3           
    1+(-20)*46/-2 
    > 437         
   
Allowed operators
    
    + Addition
    - Subtraction
    * Multiplication
    / Division (integer division only!)
    
    parentheses determine the order of operations
    spaces between numbers and operators are ignored
  
Only integers are allowed at the current time (no floats) but this may change.
    
Press CTRL+C at any time to exit the program.
)";


void printHelpMessage(std::ostream& out, bool colored) {
	if (colored) {
		out << HELP_MESSAGE_COLORED << std::flush;
	}
	else {
		out << HELP_MESSAGE << std::flush;
	}
}

