#include <iostream>
#include <string>
#include "eval-errors.cpp"
using namespace std;

/* HEADERS */

// public
int parseString(string s);

// private
int parse(string s, int &currentIndex, int endIndex, bool insideParens);
int getInteger(string s, int &currentIndex, int endIndex);

int eval(int a, char oper, int b);
int add(int a, int b);
int subtract(int a, int b);
int multiply(int a, int b);
int divide(int a, int b);

/* CODE */

int parseString(string s) {
	int currentIndex = 0;
	return parse(s, currentIndex, s.size(), false);
}

/*int parse(string s) {
	
	// Make a copy of the availble tiles
	Tiles tiles(TOTAL_TILES);
	for (int i = 0; i < TOTAL_TILES; i++) {
		tiles[i] = chosenTiles[i];
	}
	
	parse(s, 0, s.size());
}*/

int parse(string s, int &currentIndex, int endIndex, bool insideParens) {
	
	const int LEFT = 1;
	const int OPERATOR = 2;
	const int RIGHT = 3;
	int expected = LEFT;
	
	int leftPolarity = 1;
	int leftInteger = 0;
	char currentOperator;
	int rightPolarity = 1;
	int rightInteger = 0;
	
	//for(char& c : str) {
	while(currentIndex < endIndex) {
	
		char c = s[currentIndex];
		//cout << currentIndex << "\t" << c << endl;
		
		switch (c) {
			case ' ':
				// Ignore spaces
				currentIndex++;
				break;
			
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				if (expected == LEFT) {
					leftInteger = getInteger(s, currentIndex, endIndex);
					expected = OPERATOR;
				}
				else if (expected == RIGHT) {
					rightInteger = getInteger(s, currentIndex, endIndex);
					leftInteger = eval(leftPolarity * leftInteger, currentOperator, rightPolarity * rightInteger);
					//cout << "Evaluated to " << leftInteger << endl;
					expected = OPERATOR;
				}
				else if (expected == OPERATOR) {
					throw ParseError::unexpectedInteger(currentIndex);
				}
				break;
			
			case '+': // Can be used as either an operator or just whatever, dude
				if ( (expected == LEFT) || (expected == RIGHT) ) {
					currentIndex++;
				} else if (expected == OPERATOR) {
					currentOperator = c;
					currentIndex++;
					expected = RIGHT;
				}
				break;
			case '-': // Can be used as either an operator or to switch polarity
				// This techincally allows you to do wonky things
				//  like evaluate '--++--+-1' to '-1'
				if (expected == LEFT) {
					leftPolarity *= -1;
					currentIndex++;
				} else if (expected == RIGHT) {
					rightPolarity *= -1;
					currentIndex++;
				} else if (expected == OPERATOR) {
					currentOperator = c;
					currentIndex++;
					expected = RIGHT;
				}
				break;
			
			 // Can be used for polarity, but why bother? Just throw an error message instead.
			case '*':
			case '/':
				//cout << "Found operator " << c << endl;
				if (expected == LEFT) {
					throw ParseError::expectedNumberBeforeOperator(currentIndex, c);
				}
				if (expected == RIGHT) {
					throw ParseError::unexpectedOperator(currentIndex, c);
				}
				else if (expected == OPERATOR) {
					currentOperator = c;
					currentIndex++;
					expected = RIGHT;
				}
				break;
				
			case '(':
				//cout << "Opening paren found at " << currentIndex << endl;
				if (expected == LEFT) {
					currentIndex++;
					leftInteger = parse(s, currentIndex, endIndex, true);
					//cout << "Result of parens was " << leftInteger << endl;
					//cout << " Now at " << currentIndex << endl;
					expected = OPERATOR;
				} else if (expected == RIGHT) {
					currentIndex++;
					rightInteger = parse(s, currentIndex, endIndex, true);
					leftInteger = eval(leftPolarity * leftInteger, currentOperator, rightPolarity * rightInteger);
					//cout << "Result of parens was " << rightInteger << endl;
					//cout << " Now at " << currentIndex << endl;
					
					expected = OPERATOR;
				} else if (expected == OPERATOR) {
					throw ParseError::unexpectedParentheses(currentIndex);
				}
				break;
				
			case ')':
				//cout << "Closing paren found at " << currentIndex << endl;
				if (insideParens) {
					if (expected == LEFT) {
						throw ParseError::emptyParantheses(currentIndex);
					}
					else if (expected == OPERATOR) {
						currentIndex++;
						return leftPolarity * leftInteger;
					}
					else if (expected == RIGHT) {
						throw ParseError::expectedNumberAfterOperator(currentIndex, currentOperator);
					}
				} else {
					throw ParseError::unexpectedClosingParantheses(currentIndex);
				}
				break;
			
			default:
				throw ParseError::unexpectedCharacter(currentIndex, c);
				break;
		}
		
		//cout << currentIndex << "Lets' go again. Now expecting: " << expected << endl;
		//cout << currentIndex << "  left: " << leftPolarity * leftInteger << endl;
		//cout << currentIndex << "  operator: " << currentOperator << endl;
		//cout << currentIndex << "  right: " << rightPolarity * rightInteger << endl;
	}
	
	// All out of string
	if (insideParens) {
		throw ParseError::expectedClosingParantheses(currentIndex);
	}
	
	if (expected == LEFT) {
		throw ParseError::noData(currentIndex);
	}
	else if (expected == OPERATOR) {
		// This is how it should end!
		return leftPolarity * leftInteger;
	}
	else if (expected == RIGHT) {
		throw ParseError::expectedNumberAfterOperator(currentIndex, currentOperator);
	}
	
	// If this ever gets returned, something seriously f**ed up.
	throw Error(ID, "Something done goofed. I have no idea why this error happened.");
	return -1;
}

int getInteger(string s, int &currentIndex, int endIndex) {
	
	//cout << "__getInteger(" << currentIndex << ", " << endIndex << ")__" << endl;
	
	bool done = false;
	string currentInteger = "";
	char c;
	while(!done && (currentIndex < endIndex)) {
		c = s[currentIndex];
		//cout << currentIndex << "\t" << c << endl;
		switch (c) {
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				currentInteger += c;
				currentIndex++;
				break;
			case '+':
			case '-':
				
			default:
				done = true;
				break;
		}
	}
	
	if (currentInteger == "") {
		throw ParseError::unexpectedCharacter(currentIndex, c);
	}
	
	try {
		//cout << "__returned:" << stoi(currentInteger) << endl;
		return stoi(currentInteger);
	} //catch (const std::out_of_range& oor) {
	catch (...) {
		throw MathError::integerTooLarge(currentIndex, currentInteger);
	}
	

}

// 1: Division by 0 is forbidden
// 2: a must be divisible by b
int eval(int a, char oper, int b) {
	//cout << "__eval(" << a << ", " << oper << ", " << b << ")__" << endl;
	switch (oper) {
		case '+': return add(a, b);
		case '-': return subtract(a, b);
		case '*': return multiply(a, b);
		case '/': return divide(a, b);
		
		default:
			throw ParseError::unknownOperator(-1, oper);
	}
}

int add(int a, int b) {
	return a + b;
}

int subtract(int a, int b) {
	return a - b;
}

int multiply(int a, int b) {
	return a * b;
}

int divide(int a, int b) {
	if (b == 0) {
		throw MathError::divisionByZero(-1);
	}
	if (a % b != 0) {
		throw MathError::nonIntegerDivision(-1, a, b);
	}
	
	return a / b; // Already does integer division
}


