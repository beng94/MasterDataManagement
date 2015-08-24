all:
	-g++ -ffast-math -O3 -g0 -std=c++11 -fopenmp -Wall csvparser.h csvparser.c entity.hpp \
	entity.cpp double_metaphone.h double_metaphone.cc \
	Address.h Address.cpp name.hpp name.cpp tax.hpp tax.cpp \
	string_handle.hpp string_handle.cpp \
	main/statistics1.hpp main/statistics1.cpp main/main.cpp -o OUT

debug:
	g++ -g -std=c++11 -fopenmp -Wall csvparser.h csvparser.c entity.hpp \
	entity.cpp double_metaphone.h double_metaphone.cc \
	Address.h Address.cpp name.hpp name.cpp tax.hpp tax.cpp \
	string_handle.hpp string_handle.cpp \
	main/statistics1.hpp main/statistics1.cpp main/main.cpp -o OUT
