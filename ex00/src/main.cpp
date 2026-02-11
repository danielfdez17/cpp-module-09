#include "BitcoinExchange.hpp"
#include "utils.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>

int main(int ac, char **av)
{
	if (ac != 2)
	{
		std::cerr << RED "File as an argument needed!\n" RESET;
		return 1;
	}

	try
	{
		BitcoinExchange	btc;
		btc.readDatabase();
		btc.readInputFile(av[1]);
	}
	catch(const std::exception& e)
	{
		std::cerr << ERROR << e.what() << "\n" RESET;
	}

	return 0;
}