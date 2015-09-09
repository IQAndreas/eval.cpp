#include <iostream>
#include <signal.h>
#include "eval.cpp"
using namespace std;

/* HEADERS */

int main();
void sigint(int sig);

/* CODE */

int main() {
	
	// Detect when the user presses CTRL+C on their keyboard
	signal(SIGINT, sigint);
	
	const string INPUT_LINE = "Enter a calculation: ";
	const int INPUT_LINE_LENGTH = 21;
	
	try {
	
		cout << INPUT_LINE;
		string input;
		while (getline(cin, input)) {
		
			int result = parseString<int>(input);
			cout << "\033[1;93m > " << result << "\033[0m" << endl;
		
			// And all over again
			cout << INPUT_LINE;
		}
	
	} catch (ParseError& e) {
		e.print(INPUT_LINE_LENGTH);
		exit (e.id);
	} catch (MathError& e) {
		e.print(INPUT_LINE_LENGTH);
		exit (e.id);
	} catch (Error& e) {
		e.print();
		exit (e.id);
	} catch (...) {
		cerr << endl;
		cerr << "Whoops, there was an unkown error; I have no idea what happened!" << endl;
		cerr << "I would really appreciate it if you reported it to me, and let me know " << endl;
		cerr << "what you did and how to reproduce it:" << endl;
		cerr << "   * \033[4;36mhttps://github.com/IQAndreas/eval.cpp/issues\033[0m" << endl;
		exit(EXIT_FAILURE);
	}
	
	// Technically, this line should never execute unless we change the way
	//  the above while loop works.
	exit(EXIT_SUCCESS);
}

void sigint(int sig) {
	// Pressed CTRL+C. All good.
	cout << endl;
    exit(EXIT_SUCCESS);
}


