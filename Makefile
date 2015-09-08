eval-test: 
	clear;
	@g++ -std=c++11 src/eval-test.cpp -I 'lib/' -o bin/eval-test && printf "\033[1;4;32m%-${COLUMNS}s\033[00m" "Compiled successfully" && echo -n "\n\n" && bin/eval-test;
	@echo -n "\n\n";

