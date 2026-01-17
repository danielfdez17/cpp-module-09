#include "RPN.hpp"
#include "utils.hpp"
#include <iostream>

int main(int ac, char **av)
{
	(void)av;
	if (ac != 2)
	{
		std::cerr << RED "RPN as an argument needed!\n" RESET;
		return 1;
	}

	RPN	rpn(av[1]);
	
	return 0;
}