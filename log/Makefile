all: log_test.o log.o
	g++  -o log_test log_test.o log.o -std=c++11 -llog4cxx -lpthread

log_test.o: log_test.cc
	g++ -c log_test.cc -std=c++11

log.o: log.cc
	g++ -c log.cc -std=c++11

.PHONY: clean
clean:
	rm *.o log_test
	rm -r ./log