#include "BitcoinExchange.hpp"
#include <string>

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
	i++;
	if (i < dateSize && date[i] != HYPHEN)
		return false;

	// ? process month
	while (i < dateSize && isdigit(date[i]))
		i++;
	if (i != YEAR_SIZE + 1 + DATE_SIZE)
		return false;
	
	// ? process second hyphen
	i++;
	if (i < dateSize && date[i] != HYPHEN)
		return false;
	
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
	{
		std::cerr << RED "There is not data!\n" RESET;
		return 0.0;
	}
	Date d(key);
	// ! while(dates.find() != dates.end())
	// ! { return *it}
	return 0.0;
}

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(BitcoinExchange const& copy) { (void) copy;}

BitcoinExchange & BitcoinExchange::operator=(BitcoinExchange const& copy) { (void) copy; return *this ;}

BitcoinExchange::~BitcoinExchange() {}

void	BitcoinExchange::addDateValue(std::string key, float value)
{
	if (!isValidDate(key))
	{
		std::cerr << RED "Error: bad input => " << key << "\n" RESET;
		return;
	}
	if (value < MIN_VALUE)
	{
		std::cerr << RED "Error: not a positive number.\n" RESET;
		return;
	}
	if (value > MAX_VALUE)
	{
		std::cerr << RED "Error: too large number.\n" RESET;
		return;
	}
	this->dates.insert(std::make_pair(Date(key), value));
}

void	BitcoinExchange::displayFactor(std::string key, float value)
{
	if (!isValidDate(key))
	{
		std::cerr << RED "Error: bad input => " << key << "\n" RESET;
		return;
	}
	if (value < MIN_VALUE)
	{
		std::cerr << RED "Error: not a positive number.\n" RESET;
		return;
	}
	if (value > MAX_VALUE)
	{
		std::cerr << RED "Error: too large number.\n" RESET;
		return;
	}
	float factor = findValueOfDateOrClosestDate(key);
	std::cout << GREEN << key << " => " << value << " = " << value * factor << "\n" RESET;
}
