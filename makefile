all:
	g++ -std=c++11 -Wall csvparser.h csvparser.c entity.hpp \
	entity.cpp double_metaphone.h double_metaphone.cc \
	Address.h Address.cpp main/entity_container.hpp main/entity_container.cpp \
	main/statistics.hpp main/statistics.cpp main/main.cpp -o OUT

debug:
	g++ -g -std=c++11 -Wall csvparser.h csvparser.c entity.hpp \
	entity.cpp double_metaphone.h double_metaphone.cc \
	Address.h Address.cpp main/entity_container.hpp main/entity_container.cpp \
	main/statistics.hpp main/statistics.cpp main/main.cpp -o OUT
