#include "BitcoinExchange.hpp"
#include "utils.hpp"

BitcoinExchange::Date::Date() : year(0), month(1), day(1) {}

BitcoinExchange::Date::Date(std::string date)
{
	std::string yearStr, monthStr, dayStr;

	yearStr = date.substr(0, YEAR_SIZE);
	monthStr = date.substr(YEAR_SIZE + 1, MONTH_SIZE);
	dayStr = date.substr(YEAR_SIZE + 1 + MONTH_SIZE + 1, DAY_SIZE);
	
	this->year = std::strtol(yearStr.c_str(), NULL, 10);
	if (!validateYear(this->year))
		this->year = -1;
	this->month = std::strtol(monthStr.c_str(), NULL, 10);
	if (!validateMonth(this->month))
		this->month = -1;
	this->day = std::strtol(dayStr.c_str(), NULL, 10);
	if (!validateDayOfMonth(this->month, this->day))
		this->day = -1;
}

BitcoinExchange::Date::Date(int y, int m, int d) : year(y), month(m), day(d) {}

BitcoinExchange::Date::Date(Date const& copy)
{
	if (this != &copy)
	{
		this->year = copy.year;
		this->month = copy.month;
		this->day = copy.day;
	}
}
BitcoinExchange::Date & BitcoinExchange::Date::operator=(Date const& copy)
{
	if (this != &copy)
	{
		this->year = copy.year;
		this->month = copy.month;
		this->day = copy.day;
	}
	return *this;
}
BitcoinExchange::Date::~Date() {}

long	BitcoinExchange::Date::getYear() const { return this->year; }

long	BitcoinExchange::Date::getMonth() const { return this->month; }

long	BitcoinExchange::Date::getDay() const { return this->day; }
