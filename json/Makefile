all: config_manager_test.o config_manager.o
	g++  -o config_manager_test config_manager_test.o config_manager.o -std=c++11

config_manager_test.o: config_manager_test.cc
	g++ -c config_manager_test.cc -std=c++11

config_manager.o: config_manager.cc
	g++ -c config_manager.cc -std=c++11

.PHONY: clean
clean:
	rm *.o config_manager_test