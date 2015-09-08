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
	
	} catch (int e) {
		
		if (errorCharacter >= 0) {
			// 21 is the size of the "header"
			cout << string(errorCharacter+21, ' ') << "^" << endl;
			cout << "Error at #" << errorCharacter+1 << ": ";
		} else {
			cout << "Error: ";
		}
		
		cout << errorMessage << endl;
		return 1;
	}
	

}
