all:
	g++ -std=c++11 -Wall csvparser.h csvparser.c data.hpp data.cpp input.hpp input.cpp main.cpp -o OUT

debug:
	g++ -g -std=c++11 -Wall csvparser.h csvparser.c data.hpp data.cpp input.hpp input.cpp main.cpp -o OUT

