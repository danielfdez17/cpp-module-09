#include "Date.hpp"
#include "utils.hpp"
#include <stdlib.h>

// ! year-month-date
Date::Date::Date() : year(0), month(1), day(1) {}

Date::Date::Date(std::string date)
{
	std::string yearStr, monthStr, dayStr;

	yearStr = date.substr(0, YEAR_SIZE);
	monthStr = date.substr(YEAR_SIZE + 1, MONTH_SIZE);
	dayStr = date.substr(YEAR_SIZE + 1 + MONTH_SIZE + 1, DAY_SIZE);
	
	this->year = strtol(yearStr.c_str(), NULL, 10);
	if (!validateYear(this->year))
		this->year = -1;
	this->month = strtol(monthStr.c_str(), NULL, 10);
	if (!validateMonth(this->month))
		this->month = -1;
	this->day = strtol(dayStr.c_str(), NULL, 10);
	if (!validateDayOfMonth(this->year, this->month, this->day))
		this->day = -1;
}

Date::Date::Date(int y, int m, int d) : year(y), month(m), day(d) {}

Date::Date::Date(Date const& copy)
{
	if (this != &copy)
	{
		this->year = copy.year;
		this->month = copy.month;
		this->day = copy.day;
	}
}
Date & Date::operator=(Date const& copy)
{
	if (this != &copy)
	{
		this->year = copy.year;
		this->month = copy.month;
		this->day = copy.day;
	}
	return *this;
}

bool	Date::operator<(Date const& other) const
{
	if (this->year != other.year)
		return this->year < other.year;
	if (this->month != other.month)
		return this->month < other.month;
	return this->day < other.day;
}

bool	Date::operator>(Date const& other) const
{
	if (this->year != other.year)
		return this->year > other.year;
	if (this->month != other.month)
		return this->month > other.month;
	return this->day > other.day;
}
bool	Date::operator<=(Date const& other) const
{
	return !(*this > other);
}
bool	Date::operator>=(Date const& other) const
{
	return !(*this < other);
}
bool	Date::operator==(Date const& other) const
{
	return this->year == other.year && this->month == other.month && this->day == other.day;
}

bool	Date::operator!=(Date const& other) const
{
	return this->year != other.year || this->month != other.month || this->day != other.day;
}

Date	&Date::operator--()
{
	if (this->day > 1)
	{
		this->day--;
	}
	else
	{
		if (this->month > 1)
		{
			this->month--;
			this->day = getDaysOfMonth(this->year, this->month);
		}
		else
		{
			this->year--;
			this->month = 12;
			this->day = getDaysOfMonth(this->year, this->month);
			if (this->year < 0 || this->month < 1 || this->day < 1)
			{
				this->year = 0;
				this->month = 1;
				this->day = 1;
			}
		}
	}
	return *this;
}

Date::~Date() {}

long	Date::getYear() const { return this->year; }

long	Date::getMonth() const { return this->month; }

long	Date::getDay() const { return this->day; }

void	Date::print() const
{
	std::cout << this->year << "-" 
			  << (this->month < 10 ? "0" : "") << this->month << "-" 
			  << (this->day < 10 ? "0" : "") << this->day;
}

std::ostream& operator<<(std::ostream& os, const Date& date)
{
	os << date.getYear() << "-" 
	   << (date.getMonth() < 10 ? "0" : "") << date.getMonth() << "-" 
	   << (date.getDay() < 10 ? "0" : "") << date.getDay();
	return os;
}
