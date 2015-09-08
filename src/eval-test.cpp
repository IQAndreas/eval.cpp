#include <iostream>
#include "eval.cpp"
using namespace std;

int main() {

	try {
	
		cout << "Enter a calculation: ";
		string input;
		while (getline(cin, input)) {
		
			int result = parseString(input);
			cout << " > " << result << endl;
		
			// And all over again
			cout << "Enter a calculation: ";
		}
	
	} catch (ParseError& e) {
		e.print(21);
	} catch (MathError& e) {
		e.print(21);
	} catch (Error& e) {
		e.print();
	}
	

}
