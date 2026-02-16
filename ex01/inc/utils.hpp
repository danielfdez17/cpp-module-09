#pragma once
#ifndef __COLORS__
#define __COLORS__

#include <iostream>
#include <iomanip>

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

#define DIVISION_BY_0 "Division by 0 is not allowed! Good try he he"
#define EMPTY_STACK "The stack is empty due to a bad input!"
#define BAD_INPUT "The stack has more than one value due to a bad input!"

#ifndef DEBUG
#define DEBUG false
#endif

static inline bool isOp(char c)
{
	return c == '+' || c == '*' || c == '-' || c == '/';
}

static inline bool isValidChar(char c)
{
	return c == ' ' || isOp(c) || isdigit(c);
}

static inline void	printFloatValue(float value)
{
	long long longValue = static_cast<long long>(value);
	if (value - longValue != 0.0f)
		std::cout << std::fixed << std::setprecision(2);
	std::cout << value << std::setprecision(0);
}

#endif // __COLORS__