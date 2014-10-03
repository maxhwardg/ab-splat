all:
	g++ -o ab-splat main.cpp ./vienna/libRNA.a -std=c++11 -O2
