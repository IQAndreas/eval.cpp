eval-test: 
	clear;
	# Make it if it doesn't exist
	g++ -std=c++11 src/eval-test.cpp -I 'lib/' -o bin/eval-test && time bin/eval-test;

