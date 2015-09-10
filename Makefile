eval-test: 
	clear;
	@g++ -std=c++11 src/eval-test.cpp -I 'lib/' -o bin/eval-test && printf "\033[1;4;32m%-${COLUMNS}s\033[00m" "Compiled successfully" && echo -n "\n\n" && bin/eval-test;
	@echo -n "\n\n";

eval-server:
	clear;
	@g++ -std=c++11 src/eval-server.cpp -I 'lib/' -o server/eval-server && printf "\033[1;4;32m%-${COLUMNS}s\033[00m" "Compiled successfully" && echo -n "\nServer running on 127.0.0.1:9999\n" && tcpserver 0 9999 server/server.sh;
	@echo -n "\n\n";

eval-server-raspbian:
	clear;
	@g++-4.8 -std=c++11 src/eval-server.cpp -I 'lib/' -o server/eval-server && printf "\033[1;4;32m%-${COLUMNS}s\033[00m" "Compiled successfully" && echo -n "\nServer running on 127.0.0.1:9999\n" && tcpserver 0 9999 server/server.sh;
