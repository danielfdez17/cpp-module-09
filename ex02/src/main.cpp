#include "PMergeMe.hpp"
#include "utils.hpp"
#include <iostream>
#include <stdlib.h>
#include <limits.h>

int main(int ac, char **av)
{
	if (ac == 1)
	{
		std::cerr << ERROR "At least one argument is needed!\n" RESET;
		return 0;
	}

	PMergeMe	merge;
	std::cout << YELLOW "Before: ";
	long n;
	for (int i = 1; i < ac; i++)
	{
		n = std::atol(av[i]);
		if (n < 0)
		{
			std::cerr << ERROR "Negative numbers are not allowed\n" RESET;
			return 0;
		}
		if (n < INT_MIN || n > INT_MAX)
		{
			std::cerr << ERROR << n << " is not an integer!\n" RESET;
			return 0;
		}
		if (i <= (MAX_SIZE / 2))
		{
			std::cout << n << " ";
		}
		else if (i >= ac - (MAX_SIZE / 2))
		{
			if (ac - 1 != MAX_SIZE && i == ac - (MAX_SIZE / 2))
				std::cout << "... ";
			std::cout << n << " ";
		}
		merge.addNumber(n);
	}
	std::cout << GREEN "\nAfter:  ";
	merge.displaySorted();
	merge.sort();
	std::cout << "\n" RESET;

	return 0;
}