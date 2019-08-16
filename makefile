all:
	g++ -std=c++11 -Wall -O2 src/evaluator.cpp -o evaluator -static-libstdc++ -static-libgcc