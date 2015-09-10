# The Magnificent Online Command-line Calculator

Please help me to debug it by throwing everything you can 
 at it. Currently, only integers are supported.
 
If you don't want to compile and run it locally, fire up
 your terminal and enter the following command:
 
    $ nc 173.18.215.230 9999

I have a RaspberryPi sitting next to me whose sole purpose
 is currently to act as _The Magnificent Online Command-line 
 Calculator_. You can even send commands directly to it,
 and pipe the data back.
 
If you want to try running the server-side code yourself,
 check out the `server` branch.

### Allowed operators

`+` Addition  
`-` Subtraction  
`*` Multiplication  
`/` Division (integer division only!)  

**parentheses** determine the order of operations  
**spaces** between numbers and operators are ignored  

### Usage and Examples

It can be run in one of two ways, **command-line mode** and **interactive mode**.

If any arguments are detected, it runs as **command-line mode**, treating all arguments as a calculator would. This output can be piped as you would with any other command.

	$ eval-test 1 + 2
	3
	$ eval-test 1+(-20)*46/-2
	437

If no arguments are passed, it runs as **interactive mode**
    
	$ eval-test
	Enter a calculation: 1+2
	 > 3
	Enter a calculation: 1+(-2)*4/-2
	 > 2

In interactive mode, press `CTRL+C` at any time to exit the program.

### Bugs and future work

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
     _(do you have any idea how hard tricky this is to do 
      elegantly and without repeated code?!? I'm going
      to have to re-write everything if I want some sort 
      of order of operations system! (which I may do))_
   * Only handles 32 bit signed integers
     _(max values of **-2,147,483,648** to **2,147,483,647**)_
   * No floats, only integer division is allowed
     _(this was on purpose, actually, since I created it
      for a very specific project. This could change now)_


