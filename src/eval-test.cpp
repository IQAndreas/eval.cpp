#include <iostream>
#include <signal.h>
#include "eval.cpp"
using namespace std;

/* CONSTANTS */

const std::string PROJECT_URL = "https://github.com/IQAndreas/eval.cpp/issues";

/* HEADERS */

int main(int argc, char *argv[]);

int interactiveMode();
int commandLineMode(std::string input);

void sigint(int sig);
void unknownError();

/* CODE */

int main(int argc, char *argv[]) {
	
	// Enter interactive mode if less than one argument is provided
	//  (the first argument is the name of the command)
	if (argc <= 1) {
		interactiveMode();
	}
	else {
		
		// Join all arguments, ignoring spaces
		// EDIT: Ignore the first argument. Is value is 'bin/eval-test'
		std::string input = "";
		for (int i = 1; i < argc; i++) {
			input += argv[i];
		}
		
		commandLineMode(input);
	}
}

int commandLineMode(std::string input) {

	try {
		
		int result = parseString<int>(input);
		cout << result << endl;
	
	} catch (ParseError& e) {
		cerr << input << endl;
		e.print(cerr, 0);
		exit (e.id);
	} catch (MathError& e) {
		cerr << input << endl;
		e.print(cerr, 0);
		exit (e.id);
	} catch (Error& e) {
		e.print(cerr);
		exit (e.id);
	} catch (...) {
		unknownError();
		exit(EXIT_FAILURE);
	}
	
	// If we made it this far, it means the value parsed and printed successfully!
	exit(EXIT_SUCCESS);
}

int interactiveMode() {
	
	const std::string INPUT_LINE = "Enter a calculation: ";
	const std::string INPUT_LINE_END = "";
	const std::string OUTPUT_LINE = "\033[1;93m > ";
	const std::string OUTPUT_LINE_END = "\033[0m";
	
	// Used for debugging when displaying the error message
	const int INPUT_LINE_LENGTH = 21;
	
	try {
		
		// Detect when the user presses CTRL+C on their keyboard
		signal(SIGINT, sigint);
		
		cout << INPUT_LINE;
		std::string input = "";
		while (getline(cin, input)) {
			
			cout << INPUT_LINE_END;
			
			int result = parseString<int>(input);
			cout << OUTPUT_LINE << result << OUTPUT_LINE_END << endl;
	
			// And all over again
			cout << INPUT_LINE;
		}
	
	} catch (ParseError& e) {
		e.print(cerr, INPUT_LINE_LENGTH);
		exit (e.id);
	} catch (MathError& e) {
		e.print(cerr, INPUT_LINE_LENGTH);
		exit (e.id);
	} catch (Error& e) {
		e.print(cerr);
		exit (e.id);
	} catch (...) {
		unknownError();
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

void unknownError() {
	cerr << endl;
	cerr << "Whoops, there was an unkown error; I have no idea what happened!" << endl;
	cerr << "I would really appreciate it if you reported it to me, and let me know " << endl;
	cerr << "what you did and how to reproduce it:" << endl;
	cerr << "   * \033[4;36m" << PROJECT_URL << "\033[0m" << endl;
}


