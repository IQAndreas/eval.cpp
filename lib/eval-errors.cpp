#include <ostream>
#include <string>

const int UNKNOWN_ERROR = 1;
const int ERROR = 2;
const int PARSE_ERROR = 3;
const int MATH_ERROR = 4;

class Error {
	protected:
		std::string type = "Error";
		
	public:
		int id;
		std::string message;
		
		Error(std::string message) {
			this->id = ERROR;
			this->message = message;
		}
		Error(int id, std::string message) {
			this->id = id;
			this->message = message;
		}
		
		virtual void print() {
			std::cerr << this->message << std::endl;
		}
		virtual void print(std::ostream& out) {
			out << this->message << std::endl;
		}
};

//const char POINTER_CHAR = '^';
const std::string POINTER_CHAR = "↑";

class MathError : public Error {
	public:
		int index = -1;
		MathError(int index, std::string message) : Error(MATH_ERROR, message) {
			this->type = "MathError";
			this->index = index;
		}
		
		virtual void print() {
			this->print(std::cerr);
		}
		virtual void print(std::ostream& out) {
			if (this->index >= 0) {
				out << "\033[0;31m" << this->type << " at character #" << this->index + 1 << ": ";
			} else {
				out << "\033[0;31m" << this->type << ": ";
			}
			out << this->message << "\033[0m" << std::endl;
		}
		virtual void print(std::ostream& out, int headerLength) {
			if (this->index >= 0) {
				// Show a cursor right under the character in question
				out << std::string(headerLength + this->index, ' ') << POINTER_CHAR << std::endl;
			}
			this->print(out);
		}
		
		static MathError integerTooLarge(int index, std::string integerValue) {
			return MathError(index, std::string() + "The number '" + integerValue + "' is much too big!");
		}
		static MathError floatDetected(int index) {
			return MathError(index, std::string() + "Floats are currently not allowed. The placement of this period would result in a non-integer number");
		}
		
		static MathError divisionByZero(int index) {
			return MathError(index, std::string() + "Cannot divide by zero!");
		}
		static MathError nonIntegerDivision(int index, int a, int b) {
			return MathError(index, std::string() + "Floats are currently not allowed. The operation '" + std::to_string(a) + "/" + std::to_string(b) + "' would result in a non-integer number");
		}
		static MathError nonIntegerDivision(int index) {
			return MathError(index, std::string() + "Floats are currently not allowed. The values must be integers");
		}
};

class ParseError : public Error {
	public:
		int index;
		ParseError(int index, std::string message) : Error(PARSE_ERROR, message) {
			this->type = "ParseError";
			this->index = index;
		}
		
		virtual void print() {
			this->print(std::cerr);
		}
		virtual void print(std::ostream& out) {
			if (this->index >= 0) {
				out << "\033[0;31m" << this->type << " at character #" << this->index + 1 << ": ";
			} else {
				out << "\033[0;31m" << this->type << ": ";
			}
			out << this->message << "\033[0m" << std::endl;
		}
		virtual void print(std::ostream& out, int headerLength) {
			if (this->index >= 0) {
				// Show a cursor right under the character in question
				out << std::string(headerLength + this->index, ' ') << POINTER_CHAR << std::endl;
			}
			this->print(out);
		}
		
		static ParseError noData(int index) {
			return ParseError(index, std::string() + "No text to parse");
		}
		
		static ParseError unknownOperator(int index, char opr) {
			return ParseError(index, std::string() + "Unexpected operator " + opr);
		}
		
		static ParseError unexpectedCharacter(int index, char character) {
			return ParseError(index, std::string() + "Unexpected character " + character);
		}
		static ParseError unexpectedInteger(int index) {
			return ParseError(index, std::string() + "Unexpected integer (did you add an unecessary space, or forget to add an operator between them?)");
		}
		static ParseError unexpectedOperator(int index, char opr) {
			return ParseError(index, std::string() + "Unexpected operator " + opr);
		}
		static ParseError unexpectedParentheses(int index) {
			return ParseError(index, std::string() + "Unexpected parentheses (expecting an operator instead)");
		}
		static ParseError unexpectedClosingParantheses(int index) {
			return ParseError(index, std::string() + "Closing parentheses found without a matching opening parentheses");
		}
		
		static ParseError expectedNumberBeforeOperator(int index, char opr) {
			return ParseError(index, std::string() + "A number is required before the " + opr + " operator");
		}
		static ParseError expectedNumberAfterOperator(int index, char opr) {
			return ParseError(index, std::string() + "A number is required after the " + opr + " operator");
		}
		
		static ParseError emptyParantheses(int index) {
			return ParseError(index, std::string() + "Nothing inside the parentheses");
		}
		static ParseError expectedClosingParantheses(int index) {
			return ParseError(index, std::string() + "Missing closing parentheses");
		}
		
};


