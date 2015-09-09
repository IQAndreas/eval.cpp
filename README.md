# The Magnificent Online
# Command-line Calculator

Please help me to debug it by throwing everything you can 
 at it. If it returns a "readable" error message (such as
 _"Nothing inside the parentheses"_, that's okay, and means
 I know about the problem, and am handling it properly.
 The types of bugs you should tell me about are:
   * Incorrect values returned by calculations
   * Just quitting or crashing for no reason whatsoever
   * Feature requests

Submit bugs or ideas to the following GitHub repo:

   * http://www.github.com/IQAndreas/eval.cpp

**Known issues:**

   * Order of operations is ignored; everything is parsed
     from left to right, regardless of operator type.
     (do you have any idea how hard tricky this is to do 
      elegantly and without repeated code?!? I'm going
      to have to re-write everything if I want some sort 
      of order of operations system! (which I may do))
   * Only handles 32 bit signed integers
     (max values of **-2,147,483,648** to **2,147,483,647**)
   * No floats, only integer division is allowed
     (this was on purpose, actually, since I created it
      for a very specific project. This could change now)

###Allowed operators

**+** Addition  
**-** Subtraction  
**\*** Multiplication  
**/** Division (integer division only!)  

**parentheses** determine the order of operations  
**spaces** between numbers and operators are ignored  
	
### Examples

	1+2
	_> 3_
	1+(-2)*4/-2
	_> 2_

Press `CTRL+C` at any time to exit the program.

