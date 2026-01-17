#pragma once
#ifndef __COLORS__
#define __COLORS__

#include <iostream>

#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define WHITE "\033[37m"

const size_t		YEAR_SIZE = 4;
const size_t		MONTH_SIZE = 2;
const size_t		DAY_SIZE = 2;
const size_t		DATE_SIZE = YEAR_SIZE + 1 + MONTH_SIZE + 1 + DAY_SIZE;
const char			HYPHEN = '-';

const int MAX_YEAR = 2025;
const int MAX_MONTH = 12;
const int MAX_VALUE = 10000;
const int MIN_VALUE = 0;

static inline bool validateYear(int year)
{
	return year >= 0 && year <= MAX_YEAR;
}

static inline bool	validateMonth(int month)
{
	return month > 0 && month <= MAX_MONTH;
}

static inline bool validateDayOfMonth(int month, int days)
{
	if (days <= 0)
		return false;
	switch (month)
	{
		case 1:
			return days <= 31;
		case 2:
			if (month % 4 == 0)
				return days <= 29;
			return days <= 28;
		case 3:
			return days <= 31;
		case 4:
			return days <= 30;
		case 5:
			return days <= 31;
		case 6:
			return days <= 30;
		case 7:
			return days <= 31;
		case 8:
			return days <= 31;
		case 9:
			return days <= 30;
		case 10:
			return days <= 31;
		case 11:
			return days <= 30;
		case 12:
			return days <= 31;
		default:
			return false;
	}
}

static inline int getDaysOfMonth(int year, int month)
{
	switch (month)
	{
		case 1:
			return 31;
		case 2:
			if (year % 4 == 0)
				return 29;
			return 28;
		case 3:
			return 31;
		case 4:
			return 30;
		case 5:
			return 31;
		case 6:
			return 30;
		case 7:
			return 31;
		case 8:
			return 31;
		case 9:
			return 30;
		case 10:
			return 31;
		case 11:
			return 30;
		case 12:
			return 31;
		default:
			return 0;
	}
}

static inline bool validateInput(std::string input)
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

#endif // __COLORS__