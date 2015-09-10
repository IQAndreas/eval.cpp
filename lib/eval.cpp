#include <iostream>
#include <string>
#include "eval-errors.cpp"
using namespace std;

/* HEADERS */

// public
template <class T> T parseString(string s);

// private
template <class T> T parse(string s, int &currentIndex, int endIndex, bool insideParens);
template <class T> T getNumber(string s, int &currentIndex, int endIndex);

// Not sure how to handle templates in header
template <class A, class B> A eval(A a, char oper, B b);
template <class A, class B> A add(A a, B b);
template <class A, class B> A subtract(A a, B b);
template <class A, class B> A multiply(A a, B b);
template <class A, class B> A divide(A a, B b);

// Specialized templates
//template <> float getNumber(string s, int &currentIndex, int endIndex);
//template <> int getNumber(string s, int &currentIndex, int endIndex);
template <> int divide(int a, int b);

/* CODE */

template <class T>
T parseString(string s) {
	int currentIndex = 0;
	return parse<T>(s, currentIndex, s.size(), false);
}

/*int parse(string s) {
	
	// Make a copy of the availble tiles
	Tiles tiles(TOTAL_TILES);
	for (int i = 0; i < TOTAL_TILES; i++) {
		tileint main();
s[i] = chosenTiles[i];
	}
	
	parse(s, 0, s.size());
}*/

template <class T>
T parse(string s, int &currentIndex, int endIndex, bool insideParens) {
	
	const int LEFT = 1;
	const int OPERATOR = 2;
	const int RIGHT = 3;
	int expected = LEFT;
	
	T leftPolarity = 1;
	T leftValue = 0;
	char currentOperator;
	T rightPolarity = 1;
	T rightValue = 0;
	
	//for(char& c : str) {
	while(currentIndex < endIndex) {
	
		char c = s[currentIndex];
		//clog << currentIndex << "\t" << c << endl;
		
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
					leftValue = getNumber<T>(s, currentIndex, endIndex);
					expected = OPERATOR;
				}
				else if (expected == RIGHT) {
					rightValue = getNumber<T>(s, currentIndex, endIndex);
					leftValue = eval(leftPolarity * leftValue, currentOperator, rightPolarity * rightValue);
					//clog << "Evaluated to " << leftValue << endl;
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
			
			case '*':
			case '/':
				//clog << "Found operator " << c << endl;
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
				//clog << "Opening paren found at " << currentIndex << endl;
				if (expected == LEFT) {
					currentIndex++;
					leftValue = parse<T>(s, currentIndex, endIndex, true);
					//clog << "Result of parens was " << leftValue << endl;
					//clog << " Now at " << currentIndex << endl;
					expected = OPERATOR;
				} else if (expected == RIGHT) {
					currentIndex++;
					rightValue = parse<T>(s, currentIndex, endIndex, true);
					leftValue = eval(leftPolarity * leftValue, currentOperator, rightPolarity * rightValue);
					//clog << "Result of parens was " << rightValue << endl;
					//clog << " Now at " << currentIndex << endl;
					
					expected = OPERATOR;
				} else if (expected == OPERATOR) {
					throw ParseError::unexpectedParentheses(currentIndex);
				}
				break;
				
			case ')':
				//clog << "Closing paren found at " << currentIndex << endl;
				if (insideParens) {
					if (expected == LEFT) {
						throw ParseError::emptyParantheses(currentIndex);
					}
					else if (expected == OPERATOR) {
						currentIndex++;
						return leftPolarity * leftValue;
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
		
		//clog << currentIndex << "Lets' go again. Now expecting: " << expected << endl;
		//clog << currentIndex << "  left: " << leftPolarity * leftValue << endl;
		//clog << currentIndex << "  operator: " << currentOperator << endl;
		//clog << currentIndex << "  right: " << rightPolarity * rightValue << endl;
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
		return leftPolarity * leftValue;
	}
	else if (expected == RIGHT) {
		throw ParseError::expectedNumberAfterOperator(currentIndex, currentOperator);
	}
	
	// If this ever gets returned, something seriously f**ed up.
	throw Error(1, "Something done goofed. I have no idea why this error happened.");
	return -1;
}

template <class T>
T getNumber(string s, int &currentIndex, int endIndex) {
	
	//clog << "__getNumber(" << currentIndex << ", " << endIndex << ")__" << endl;
	
	bool done = false;
	string currentValue = "";
	char c;
	while(!done && (currentIndex < endIndex)) {
		c = s[currentIndex];
		//clog << currentIndex << "\t" << c << endl;
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
				currentValue += c;
				currentIndex++;
				break;
			case '+':
			case '-':
				
			default:
				done = true;
				break;
		}
	}
	
	if (currentValue == "") {
		throw ParseError::unexpectedCharacter(currentIndex, c);
	}
	
	try {
		//clog << "__returned:" << stoi(currentValue) << endl;
		return stoi(currentValue);
	} //catch (const std::out_of_range& oor) {
	catch (...) {
		throw MathError::integerTooLarge(currentIndex, currentValue);
	}
	

}

// 1: Division by 0 is forbidden
// 2: a must be divisible by b
template <class A, class B>
A eval(A a, char oper, B b) {
	//clog << "__eval(" << a << ", " << oper << ", " << b << ")__" << endl;
	switch (oper) {
		case '+': return add<A,B>(a, b);
		case '-': return subtract<A,B>(a, b);
		case '*': return multiply<A,B>(a, b);
		case '/': return divide<A,B>(a, b);
		//case '^': return xor_oper<A,B>(a, b);
		//case '%': return modulus<A,B>(a, b);
		
		default:
			throw ParseError::unknownOperator(-1, oper);
	}
}

template <class A, class B>
A add(A a, B b) {
	return a + b;
}

template <class A, class B>
A subtract(A a, B b) {
	return a - b;
}

template <class A, class B>
A multiply(A a, B b) {
	return a * b;
}

template <class A, class B>
A divide(A a, B b) {
	if (b == 0) {
		throw MathError::divisionByZero(-1);
	}
	
	return a / b;
}

template <>
int divide<int,int>(int a, int b) {
	if (b == 0) {
		throw MathError::divisionByZero(-1);
	}
	if (a % b != 0) {
		throw MathError::nonIntegerDivision(-1, a, b);
	}
	
	return a / b; // Already does integer division
}




