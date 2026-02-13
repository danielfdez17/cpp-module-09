#pragma once
#ifndef __COLORS__
#define __COLORS__

#include <iostream>
#include <vector>

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
#define DEBUG MAGENTA << "[DEBUG] "

#ifndef DEBUGGING
#define DEBUGGING false
#endif // DEBUGGING

const int MAX_SIZE = 20;
const int DISPLAYED_PRECISION = 7;

// ? Jacobsthal sequence until n
static inline std::vector<int>	generateTill(int n)
{
	std::vector<int> jacob;

	// ? Base cases
	jacob.push_back(0);
	jacob.push_back(1);

	// ? Recursive case
	for (int i = 2; i < n; i++)
	{
		jacob.push_back(jacob[i - 1] + (2 * jacob[i - 2]));
	}
	return jacob;
}

static inline std::vector<int>	jacobsthalSeq(int n)
{
	std::vector<int> seq;
	std::vector<int> jacob = generateTill(n + 2); // Generate enough Jacobsthal numbers
	
	for (size_t i = 1; i < jacob.size() && jacob[i] <= n; i++)
	{
		// ? Skip if this Jacobsthal number is the same as previous (duplicate)
		if (i > 1 && jacob[i] == jacob[i - 1])
			continue;
			
		int start = (i == 1) ? 0 : jacob[i - 1];
		int end = jacob[i];
		size_t lower = static_cast<size_t>(start);
		size_t upper = static_cast<size_t>(std::min(end, n - 1));
		
		for (size_t j = upper; j > lower; j--)
			seq.push_back(j);
	}

	return seq;
}

#endif // __COLORS__