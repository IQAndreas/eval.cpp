#include <ostream>
#include <string>
#include "error.cpp"

const int UNKNOWN_ERROR = 1;
const int ERROR = 2;
const int PARSE_ERROR = 3;
const int MATH_ERROR = 4;

class MathError : public IndexedError {

	public:
		MathError(int index, std::string message) : IndexedError(MATH_ERROR, -1, index, message) {
			this->type = "MathError";
		}
	
	// static constructors:
		static MathError integerTooLarge(int index, std::string integerValue) {
			return MathError(index, std::string() + "The number '" + integerValue + "' is much too big!");
		}
		static MathError floatDetected(int index) {
			return MathError(index, std::string() + "Floats are currently not allowed." + NEWLINE + "(The placement of this period would result in a non-integer number)");
		}
		
		static MathError divisionByZero(int index) {
			return MathError(index, std::string() + "Cannot divide by zero!");
		}
		static MathError nonIntegerDivision(int index, int a, int b) {
			return MathError(index, std::string() + "Floats are currently not allowed." + NEWLINE + "(The operation '" + std::to_string(a) + "/" + std::to_string(b) + "' would result in a non-integer number)");
		}
};

class ParseError : public IndexedError {
	
	public:
		ParseError(int index, std::string message) : IndexedError(PARSE_ERROR, -1, index, message) {
			this->type = "ParseError";
		}
		
	// static constructors:
		static ParseError noData(int index) {
			return ParseError(index, std::string() + "No text to parse");
		}
		
		static ParseError unknownOperator(int index, char opr) {
			return ParseError(index, std::string() + "Unexpected operator " + opr);
		}
		
		static ParseError unexpectedCharacter(int index, char character) {
			return ParseError(index, std::string() + "Unexpected character " + character);
		}
		static ParseError unexpectedComma(int index) {
			return ParseError(index, std::string() + "Unexpected comma" + NEWLINE + "(Is it used as a thousand's separator? Please remove it)" + NEWLINE + "(Is it used as a decimal point? This is 'murica! We don't do silly things like that here.)");
		}
		static ParseError unexpectedInteger(int index) {
			return ParseError(index, std::string() + "Unexpected integer" + NEWLINE + "(Did you add an unecessary space, or forget to add an operator between them?)");
		}
		static ParseError unexpectedOperator(int index, char opr) {
			return ParseError(index, std::string() + "Unexpected operator " + opr);
		}
		static ParseError unexpectedParentheses(int index) {
			return ParseError(index, std::string() + "Unexpected parentheses" + NEWLINE + "(expecting an operator instead)");
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


