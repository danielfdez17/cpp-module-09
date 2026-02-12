#include "PMergeMe.hpp"
#include "utils.hpp"
#include <iostream>
#include <stdlib.h>
#include <limits.h>

#ifndef DEBUG
#define DEBUG false
#endif // DEBUG

int main(int ac, char **av)
{
	(void)av;
	if (ac == 1)
	{
		std::cerr << ERROR "At least one argument is needed!\n" RESET;
		return 1;
	}

	PMergeMe	merge;
	if (DEBUG)
	{
		std::cout << INFO "Before: ";
	}
	long n;
	for (int i = 1; i < ac; i++)
	{
		n = std::atol(av[i]);
		if (n < 0)
		{
			std::cerr << ERROR "Negative numbers are not allowed\n" RESET;
			return 1;
		}
		if (n < INT_MIN || n > INT_MAX)
		{
			std::cerr << ERROR << n << " is not an integer!\n" RESET;
		}
		if (DEBUG)
		{
			std::cout << n << " ";
		}
		merge.addNumber(n);
	}
	std::cout << GREEN "\nAfter:  ";
	if (DEBUG)
	{
		merge.displaySorted();
	}
	merge.sort1();
	merge.sort2();
	// merge.display1();
	// merge.display2();

	return 0;
}