all: mysql_test.o mysql.o
	g++  -g -o mysql_test mysql_test.o mysql.o -std=c++11 -lmysqlpp

mysql_test.o: mysql_test.cc
	g++ -c mysql_test.cc -std=c++11

mysql.o: mysql.cc
	g++ -c mysql.cc -std=c++11

.PHONY: clean
clean:
	rm *.o mysql_test