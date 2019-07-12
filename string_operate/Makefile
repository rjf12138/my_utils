all: str_util_test.o str_util.o
	g++  -o str_util_test str_util_test.o str_util.o -std=c++11

str_util_test.o: str_util_test.cc
	g++ -c str_util_test.cc -std=c++11

str_util.o: str_util.cc
	g++ -c str_util.cc -std=c++11

.PHONY: clean
clean:
	rm *.o str_util_test