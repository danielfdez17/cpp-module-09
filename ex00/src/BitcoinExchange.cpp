#include "BitcoinExchange.hpp"
#include <iostream>
#include <iomanip>
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
	// std::cout << date << "\n";
	return (d.getYear() >= 0 && d.getMonth() > 0 && d.getDay() > 0);
}

float	BitcoinExchange::findClosestValueForDate(std::string key)
{
	if (this->dates.size() == 0)
		throw std::runtime_error("There is no data!");

	if (!isValidDate(key))
		throw std::runtime_error(this->stringConcat(BAD_INPUT, key));

	Date d(key);
	std::map<Date, float>::iterator it = this->dates.upper_bound(d);
	if (it == this->dates.begin())
		throw std::runtime_error("No earlier data found!");
	--it;

	std::cout << OK << "Found closest date {" << it->first << ",";
	this->printFloatValue(it->second);
	std::cout << "}: " RESET;
	return it->second;
}

BitcoinExchange::BitcoinExchange() : firstDate(true), minimumDate(MAX_YEAR, MAX_MONTH, MAX_DAY) {}

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
	while (std::getline(database, line))
	{
		if (line == "date,exchange_rate")
		{
			if (DEBUGGING)
				std::cout << DEBUG "found database file header\n" RESET;
			continue;
		}
		size_t	sepPos = line.find(',');
		if (sepPos == std::string::npos)
			continue;
		std::string	date = line.substr(0, sepPos);
		std::string	valueStr = line.substr(sepPos + 1);
		float		value = strtof(valueStr.c_str(), NULL);
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
	while (std::getline(input, line))
	{
		try
		{
			if (line == "date | value")
			{
				if (DEBUGGING)
					std::cout << DEBUG "found input file header\n" RESET;
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
	if (this->firstDate)
	{
		this->minimumDate = Date(key);
		this->firstDate = false;
	}
	else
	{
		if (Date(key) < this->minimumDate)
			this->minimumDate = Date(key);
	}
	this->dates.insert(std::make_pair(Date(key), value));
}

void	BitcoinExchange::displayFactor(std::string input)
{
	size_t		sepPos		=	input.find('|');
	std::string	key			=	input.substr(0, sepPos - 1);
	std::string	valueStr	=	input.substr(sepPos + 2);
	if (!validateValue(valueStr))
		throw std::runtime_error(this->stringConcat(BAD_INPUT, input));
	float		value		=	strtof(valueStr.c_str(), NULL);

	if (!isValidDate(key))
		throw std::runtime_error(this->stringConcat(BAD_INPUT, input));
	if (value < MIN_VALUE)
		throw std::runtime_error(NOT_POSITIVE);
	if (value > MAX_VALUE)
		throw std::runtime_error(TOO_LARGE_NUMBER);

	try
	{
		float factor = findClosestValueForDate(key);
		std::cout << GREEN << key << " => ";
		this->printFloatValue(value);
		std::cout << " = ";
		this->printFloatValue(value * factor);
		std::cout << "\n" RESET;
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

void BitcoinExchange::printFloatValue(float value)
{
	long longValue = static_cast<long>(value);
	if (value - longValue == 0.0f)
	{
		std::cout << value;
	}
	else
	{
		std::cout << std::fixed << std::setprecision(2) << value;
	}
	std::cout << std::setprecision(0);
}
