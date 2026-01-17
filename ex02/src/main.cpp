#include "PMergeMe.hpp"
#include "utils.hpp"
#include <iostream>
#include <stdlib.h>

int main(int ac, char **av)
{
	(void)av;
	if (ac == 1)
	{
		std::cerr << RED "At least one argument is needed!\n" RESET;
		return 1;
	}

	PMergeMe	merge;
	
	std::cout << YELLOW "Before: ";
	int n;
	for (int i = 1; i < ac; i++)
	{
		n = std::atoi(av[i]);
		if (n < 0)
		{
			std::cerr << RED "Error: negative numbers are not allowed\n" RESET;
			return 1;
		}
		std::cout << n << " ";
		merge.addNumber(n);
	}
	std::cout << GREEN "\nAfter:  ";
	merge.displaySorted();
	merge.sort1();
	merge.sort2();

	return 0;
}