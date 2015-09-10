#include <iostream>
#include <string>
using namespace std;

const int UNKNOWN_ERROR = 1;
const int ERROR = 2;
const int PARSE_ERROR = 3;
const int MATH_ERROR = 4;

class Error {
	protected:
		string type = "Error";
		
	public:
		int id;
		string message;
		
		Error(string message) {
			this->id = ERROR;
			this->message = message;
		}
		Error(int id, string message) {
			this->id = id;
			this->message = message;
		}
		
		virtual void print() {
			cerr << this->message << endl;
		}
};

//const char POINTER_CHAR = '^';
const string POINTER_CHAR = "↑";

class MathError : public Error {
	public:
		int index = -1;
		MathError(int index, string message) : Error(MATH_ERROR, message) {
			this->type = "MathError";
			this->index = index;
		}
		
		virtual void print() {
			if (this->index >= 0) {
				cerr << "\033[0;31m" << this->type << " at character #" << this->index + 1 << ": ";
			} else {
				cerr << "\033[0;31m" << this->type << ": ";
			}
			cerr << this->message << "\033[0m" << endl;
		}
		virtual void print(int headerLength) {
			if (this->index >= 0) {
				// Show a cursor right under the character in question
				cerr << string(headerLength + this->index, ' ') << POINTER_CHAR << endl;
			}
			this->print();
		}
		
		static MathError integerTooLarge(int index, string integerValue) {
			return MathError(index, string() + "The number '" + integerValue + "' is much too big!");
		}
		static MathError floatDetected(int index) {
			return MathError(index, string() + "Floats are currently not allowed. The placement of this period would result in a non-integer number");
		}
		
		static MathError divisionByZero(int index) {
			return MathError(index, string() + "Cannot divide by zero!");
		}
		static MathError nonIntegerDivision(int index, int a, int b) {
			return MathError(index, string() + "Floats are currently not allowed. The operation '" + to_string(a) + "/" + to_string(b) + "' would result in a non-integer number");
		}
		static MathError nonIntegerDivision(int index) {
			return MathError(index, string() + "Floats are currently not allowed. The values must be integers");
		}
};

class ParseError : public Error {
	public:
		int index;
		ParseError(int index, string message) : Error(PARSE_ERROR, message) {
			this->type = "ParseError";
			this->index = index;
		}
		
		virtual void print() {
			if (this->index >= 0) {
				cerr << "\033[0;31m" << this->type << " at character #" << this->index + 1 << ": ";
			} else {
				cerr << "\033[0;31m" << this->type << ": ";
			}
			cerr << this->message << "\033[0m" << endl;
		}
		virtual void print(int headerLength) {
			if (this->index >= 0) {
				// Show a cursor right under the character in question
				cerr << string(headerLength + this->index, ' ') << POINTER_CHAR << endl;
			}
			this->print();
		}
		
		static ParseError noData(int index) {
			return ParseError(index, string() + "No text to parse");
		}
		
		static ParseError unknownOperator(int index, char opr) {
			return ParseError(index, string() + "Unexpected operator " + opr);
		}
		
		static ParseError unexpectedCharacter(int index, char character) {
			return ParseError(index, string() + "Unexpected character " + character);
		}
		static ParseError unexpectedInteger(int index) {
			return ParseError(index, string() + "Unexpected integer (did you add an unecessary space, or forget to add an operator between them?)");
		}
		static ParseError unexpectedOperator(int index, char opr) {
			return ParseError(index, string() + "Unexpected operator " + opr);
		}
		static ParseError unexpectedParentheses(int index) {
			return ParseError(index, string() + "Unexpected parentheses (expecting an operator instead)");
		}
		static ParseError unexpectedClosingParantheses(int index) {
			return ParseError(index, string() + "Closing parentheses found without a matching opening parentheses");
		}
		
		static ParseError expectedNumberBeforeOperator(int index, char opr) {
			return ParseError(index, string() + "A number is required before the " + opr + " operator");
		}
		static ParseError expectedNumberAfterOperator(int index, char opr) {
			return ParseError(index, string() + "A number is required after the " + opr + " operator");
		}
		
		static ParseError emptyParantheses(int index) {
			return ParseError(index, string() + "Nothing inside the parentheses");
		}
		static ParseError expectedClosingParantheses(int index) {
			return ParseError(index, string() + "Missing closing parentheses");
		}
		
};



