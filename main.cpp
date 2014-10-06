#include <iostream>
#include <cstdlib>
#include "ab-splat.h"


int main(int argc, char **argv)
{
	std::cout
		<< "Enter your RNA sequence into the standard input stream..." 
		<< std::endl
		<< "Note that user defined values for a and b can be set as command line arguments." 
		<< std::endl
		<< "If these are not set, default values will be used (a = 24, b = 1.8)."
		<< std::endl
		<< "For example, use './ab-splat 28 1.5' for a=28 and b=1.5."
		<< std::endl
		<< "Note that a must be an integer value, and b must be a float."
		<< std::endl;
	int a = 24;
	double b = 1.8;
	if (argc == 3) {
		a = atoi(argv[1]);
		b = atof(argv[2]);
		std::cout << "a=" << a << ", b=" << b << std::endl;
	}
	while (std::cin.good()) {
		std::string rna;
		std::cin >> rna;
		std::cout << ab_splat(a, b, rna) << std::endl;
		std::cin >> std::ws;
	}
	return 0;
}
