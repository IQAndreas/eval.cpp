#include <ostream>
#include <string>

class Error {
	
	protected:
		std::string type = "Error";
		int id = 1;
		std::string message = "";
		
	public:
		
		// Constructors:
		Error(int id, std::string message) {
			this->id = id;
			this->message = message;
		}
		
		// Getters:
		std::string getType() 	 { return this->type; }
		int getID() 			 { return this->id; }
		std::string getMessage() { return this->message; }
		
		// Methods:
		virtual void print() {
			this->print(std::cerr, true);
		}
		virtual void print(std::ostream& out, bool coloredOutput) {
			
			if (coloredOutput) {
					 // BOLD;RED foreground color       // Reset BOLD                               // Default foreground color
				out << "\033[1;31m" << this->getType() << "\033[21m" << ": " << this->getMessage() << "\033[39m" << std::endl;
			}
			else {
				out << this->getType() << ": " << this->getMessage() << std::endl;
			}
		}
};


// This is kind of bulls**t. I want to define these as static inside the IndexedError class.
// See http://stackoverflow.com/questions/1563897/c-static-constant-string-class-member
const char WHITESPACE_CHAR = ' ';
//const char POINTER_CHAR = '^';
const std::string POINTER_CHAR = "↑";
const std::string NEWLINE = "\n    "; // If an error message continues on a second line

// An error at a certain index in code or input
class IndexedError : public Error {
	
	protected:
	
		int lineNumber =     -1;
		int characterNumber = -1;
		
	public:
		
		// Constructors:
		IndexedError(int id, int line, int character, std::string message) : Error(id, message) {
			this->type = "IndexedError";
			this->lineNumber = line;
			this->characterNumber = character;
		}
		
		// Getters:
		
		// "Optional", both default to -1 if not set
		int getLineNumber()      { return this->lineNumber; }
		int getCharacterNumber() { return this->characterNumber; }
		
		// Methods:
		virtual void print(int headerLength) {
			this->print(std::cerr, true, headerLength);
		}
		virtual void print(std::ostream& out, bool coloredOutput, int headerLength) {
			// Show a cursor right under the character in question
			// (for now, just show the character number, not the line number)
			if (this->getCharacterNumber() >= 0) {
				out << std::string(headerLength + this->getCharacterNumber(), WHITESPACE_CHAR) << POINTER_CHAR << std::endl;
			}
			
			// Continue printing the error message as usual
			this->print(out, coloredOutput);
		}
		
		// This is really ugly code. :(
		// I don't know how to make it cleaner without some sort of "format" variable
		//  and code that injects values into that format.
		//  This would be a great place for Python's % operator.
		virtual void print(std::ostream& out, bool coloredOutput) {
			
			// TYPE
			if (coloredOutput) {
					 // BOLD;RED foreground color       // Reset BOLD
				out << "\033[1;31m" << this->getType() << "\033[21m";
			}
			else {
				out << this->getType();
			}
			
			// LOCATION (line and column)
			
			if ( (this->getLineNumber() >= 0) || (this->getCharacterNumber() >= 0) ) {
				out << " at"; 
			}
			
			if (this->getLineNumber() >= 0) {
				out << " line #" << this->getLineNumber() + 1;
			}
			if (this->getCharacterNumber() >= 0) {
				out << " character #" << this->getCharacterNumber() + 1;
			}
			
			out << ": ";
			
			// MESSAGE
			out << NEWLINE << this->getMessage();
			if (coloredOutput) {
				out << "\033[39m"; // Reset to default foreground color
			}
			
			// Flush everything
			out << std::endl;
		}
	
};



