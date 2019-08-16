all:
	g++ -std=c++11 -Wall -O2 src/evaluator.cpp -o evaluator_long_double -static-libstdc++ -static-libgcc