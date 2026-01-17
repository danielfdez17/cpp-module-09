#include "BitcoinExchange.hpp"
#include "utils.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>

int main(int ac, char **av)
{
	(void)av;
	if (ac != 2)
	{
		std::cerr << RED "File as an argument needed!\n" RESET;
		return 1;
	}

	BitcoinExchange	btc;
	// ! read CSV and populate BTC

	std::ifstream	csvFile("data.csv");

	if (!csvFile.is_open())
	{
		std::cerr << RED "Could not open data.csv file!\n" RESET;
		return 1;
	}

	std::string		line;
	std::getline(csvFile, line); // ? skip header
	while (std::getline(csvFile, line))
	{
		size_t	sepPos = line.find(',');
		if (sepPos == std::string::npos)
			continue;
		std::string	date = line.substr(0, sepPos);
		std::string	valueStr = line.substr(sepPos + 1);
		float		value = strtof(valueStr.c_str(), NULL);
		// std::cout << "Date: " << date << " Value: " << value << "\n";
		btc.addDateValue(date, value);
	}
	
	csvFile.close();

	std::ifstream	file(av[1]);

	if (!file.is_open())
	{
		std::cerr << RED "Could not open file!\n" RESET;
		return 1;
	}

	
	std::getline(file, line); // ? read line
	while (std::getline(file, line))
	{
		if (!validateInput(line))
		{
			std::cerr << RED "Error: bad input => " << line << "\n" RESET;
			continue;
		}
		size_t	sepPos = line.find('|');
		std::string	date = line.substr(0, sepPos - 1);
		std::string	valueStr = line.substr(sepPos + 2);
		float		value = strtof(valueStr.c_str(), NULL);
		btc.displayFactor(date, value);
	}

	file.close();
	
	return 0;
}