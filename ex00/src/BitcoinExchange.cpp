#include "BitcoinExchange.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <stdexcept>

bool	BitcoinExchange::isValidDate(std::string date)
{
	size_t	i = 0, dateSize = date.size();

	if (dateSize != DATE_SIZE)
		return false;

	// ? process year
	while (i < dateSize && isdigit(date[i]))
		i++;
	if (i != YEAR_SIZE)
		return false;

	// ? process first hyphen
	if (i < dateSize && date[i] != HYPHEN)
		return false;
	i++;

	// ? process month
	while (i < dateSize && isdigit(date[i]))
		i++;
	if (i != YEAR_SIZE + 1 + MONTH_SIZE)
		return false;

	// ? process second hyphen
	if (i < dateSize && date[i] != HYPHEN)
		return false;
	i++;

	// ? process day
	while (i < dateSize && isdigit(date[i]))
		i++;
	if (i != DATE_SIZE)
		return false;

	Date d(date);
	return (d.getYear() >= 0 && d.getMonth() > 0 && d.getDay() > 0);
}

float	BitcoinExchange::findValueOfDateOrClosestDate(std::string key)
{
	if (this->dates.size() == 0)
		throw std::runtime_error("There is no data!");

	Date d(key);
	std::map<Date, float>::iterator it = this->dates.lower_bound(d);
	// std::map<Date, float>::iterator	it = this->dates.find(d);
	// while (it == this->dates.end())
	// {
	// 	--d;
	// 	it = this->dates.find(d);
	// }
	--it;
	if (it == this->dates.end())
		throw std::runtime_error("No data found");
	d = it->first;
	std::cout << OK << "Found closest date {";
	d.print();
	std::cout << "," << it->second << "}: " RESET;
	return it->second;
	return 0.0;
}

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(BitcoinExchange const& copy) { (void) copy;}

BitcoinExchange & BitcoinExchange::operator=(BitcoinExchange const& copy) { (void) copy; return *this ;}

BitcoinExchange::~BitcoinExchange() {}

bool BitcoinExchange::validateInput(std::string input)
{
	size_t	sepPos = input.find('|');
	if (sepPos == std::string::npos)
		return false;

	std::string	date = input.substr(0, sepPos - 1);
	size_t		dateSize = date.size();

	if (dateSize != DATE_SIZE)
		return false;

	std::string	valueStr = input.substr(sepPos + 2);
	if (valueStr.empty())
		return false;
	return true;
}

void	BitcoinExchange::readDatabase()
{
	std::ifstream	database("data.csv");

	if (!database.is_open())
		throw std::runtime_error("Could not opven data.csv file");

	std::string		line;
	// std::getline(database, line); // ? skip header
	while (std::getline(database, line))
	{
		if (line == "date,exchange_rate")
		{
			// std::cout << INFO "found database file header\n" RESET;
			continue;
		}
		size_t	sepPos = line.find(',');
		if (sepPos == std::string::npos)
			continue;
		std::string	date = line.substr(0, sepPos);
		std::string	valueStr = line.substr(sepPos + 1);
		float		value = strtof(valueStr.c_str(), NULL);
		// std::cout << "Date: " << date << " Value: " << value << "\n";
		try
		{
			this->addDateValue(date, value);
		}
		catch(const std::exception& e)
		{
			std::cerr << ERROR << e.what() << "\n\n" RESET;
		}

	}

	database.close();
}

void	BitcoinExchange::readInputFile(std::string file)
{
	std::ifstream	input(file.c_str());

	if (!input.is_open())
		throw std::runtime_error("Could not open " + file);

	std::string line;
	// std::getline(input, line); // ? read line
	while (std::getline(input, line))
	{
		try
		{
			if (line == "date | value")
			{
				// std::cout << INFO "found input file header\n" RESET;
				continue;
			}
			std::cout << INFO << "Processing '" << line << "': \n" RESET;
			if (!this->validateInput(line))
				throw std::runtime_error(this->stringConcat(BAD_INPUT, line));
			this->displayFactor(line);
			std::cout << "\n";
		}
		catch(const std::exception& e)
		{
			std::cerr << ERROR << e.what() << "\n\n" RESET;
		}
	}

	input.close();
}

void	BitcoinExchange::addDateValue(std::string key, float value)
{
	if (!isValidDate(key))
		throw std::runtime_error(this->stringConcat(BAD_INPUT, key));
	if (value < MIN_VALUE)
		throw std::runtime_error(NOT_POSITIVE);

	this->dates.insert(std::make_pair(Date(key), value));
}

void	BitcoinExchange::displayFactor(std::string input)
{
	size_t		sepPos		=	input.find('|');
	std::string	key			=	input.substr(0, sepPos - 1);
	std::string	valueStr	=	input.substr(sepPos + 2);
	float		value		=	strtof(valueStr.c_str(), NULL);

	if (!isValidDate(key))
		throw std::runtime_error(this->stringConcat(BAD_INPUT, input));
	if (value < MIN_VALUE)
		throw std::runtime_error(NOT_POSITIVE);
	if (value > MAX_VALUE)
		throw std::runtime_error(TOO_LARGE_NUMBER);

	try
	{
		float factor = findValueOfDateOrClosestDate(key);
		std::cout << GREEN << key << " => " << value << " = " << value * factor << "\n" RESET;
	}
	catch(const std::exception& e)
	{
		std::cerr << ERROR << e.what() << "\n" RESET;
	}

}

std::string	BitcoinExchange::stringConcat(std::string a, std::string b)
{
	return a + b;
}
