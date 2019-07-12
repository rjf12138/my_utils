all: xml.o test_xml.o
	g++ -o test_xml xml.o test_xml.o -std=c++11 -lxerces-c

xml.o: xml.cc
	g++ -c xml.cc -std=c++11

test_xml.o: test_xml.cc
	g++ -c test_xml.cc -std=c++11

.PHONY: clean
clean:
	rm *.o test_xml