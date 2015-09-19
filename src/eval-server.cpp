#include <iostream>
#include <fstream>
#include <signal.h>
#include "eval.cpp"

/* CONSTANTS */

const std::string PROJECT_URL = "https://github.com/IQAndreas/eval.cpp/issues";

/* HEADERS */

int main(int argc, char *argv[]);

void sigint(int sig);
void unknownError();

/* CODE */

int main(int argc, char *argv[]) {
	
	// Force entering interactive mode when running on the server
	// The first argument is going to be the name of the log file.
	std::string logFilename = (argc <= 1) ? "server/eval-server.log" : argv[1];
	std::ofstream log( logFilename, std::ios_base::app );
	
	const std::string INPUT_LINE = "Enter a calculation: ";
	const std::string INPUT_LINE_END = "";
	const std::string OUTPUT_LINE = "\033[1;93m > ";
	const std::string OUTPUT_LINE_END = "\033[0m";
	
	// Used for debugging when displaying the error message
	const int INPUT_LINE_LENGTH = 21;
	
	try {
		
		// Detect when the user presses CTRL+C on their keyboard
		signal(SIGINT, sigint);
		
		std::cout << INPUT_LINE;
		std::string input = "";
		while (getline(std::cin, input)) {
			std::cout << INPUT_LINE_END;
			
			// Save what they entered to the log file
			log << " > " << input << "\n"; // Don't flush it yet
			
			// Detect special commands
			if (input == "") {
				// No text entered
				// Act the same way as Bash, and just show another empty line
			}
			else if ( input == "exit" || input == "quit") {
				exit(EXIT_SUCCESS);
			}
			else {
				// No special command entered. Parse the text that was entered as usual.
				int result = parseString<int>(input);
				std::cout << OUTPUT_LINE << result << OUTPUT_LINE_END << std::endl;
			}
			
			// And all over again
			std::cout << INPUT_LINE;
		}
	
	} catch (ParseError& e) {
		e.print(log, false, 3);
		e.print(std::cerr, true, INPUT_LINE_LENGTH);
		exit (e.getID());
	} catch (MathError& e) {
		e.print(log, false, 3);
		e.print(std::cerr, true, INPUT_LINE_LENGTH);
		exit (e.getID());
	} catch (Error& e) {
		e.print(log, false);
		e.print(std::cerr, true);
		exit (e.getID());
	} catch (...) {
		log << "\033[0;31m!!!!!!!!!!!!!!! UNKNOWN ERROR !!!!!!!!!!!!!!!\033[0m" << std::endl;
		unknownError();
		exit(EXIT_FAILURE);
	}
	
	// Technically, this line should never execute unless we change the way
	//  the above while loop works.
	exit(EXIT_SUCCESS);
}

void sigint(int sig) {
	// Pressed CTRL+C. All good.
	std::cout << std::endl;
    exit(EXIT_SUCCESS);
}

void unknownError() {
	std::cerr << std::endl;
	std::cerr << "Whoops, there was an unkown error; I have no idea what happened!" << std::endl;
	std::cerr << "I would really appreciate it if you reported it to me, and let me know " << std::endl;
	std::cerr << "what you did and how to reproduce it:" << std::endl;
	std::cerr << "   * \033[4;36m" << PROJECT_URL << "\033[0m" << std::endl;
}


