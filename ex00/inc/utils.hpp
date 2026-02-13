#pragma once
#ifndef __UTILS__
#define __UTILS__

#include <iostream> // ! DO NOT REMOVE

#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define WHITE "\033[37m"
#define INFO YELLOW << "[INFO] "
#define ERROR RED << "[ERROR] "
#define OK GREEN << "[OK] "
#define BAD_INPUT "Bad input => "
#define NOT_POSITIVE "Not a positive number"
#define TOO_LARGE_NUMBER "Too large number"

const size_t		YEAR_SIZE = 4;
const size_t		MONTH_SIZE = 2;
const size_t		DAY_SIZE = 2;
const size_t		DATE_SIZE = YEAR_SIZE + 1 + MONTH_SIZE + 1 + DAY_SIZE;
const char			HYPHEN = '-';

const int MAX_YEAR = 2027;
const int MAX_MONTH = 12;
const int MAX_VALUE = 1000;
const int MIN_VALUE = 0;

static inline bool validateYear(int year)
{
	return year >= 0 && year <= MAX_YEAR;
}

static inline bool	validateMonth(int month)
{
	return month > 0 && month <= MAX_MONTH;
}

static inline bool validateDayOfMonth(int year, int month, int days)
{
	if (days <= 0)
		return false;
	switch (month)
	{
		case 1:
			return days <= 31;
		case 2:
			if (year % 4 == 0)
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
			if (year == 2024)
				std::cout << "bisiesto\n";
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

#endif // __UTILS__