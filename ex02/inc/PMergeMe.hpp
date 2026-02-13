#pragma once
#ifndef __PMERGEME_HPP__
#define __PMERGEME_HPP__

#include "MyList.hpp"
#include "MySet.hpp"
#include "utils.hpp"
#include <iostream>
#include <vector>
#include <list>
#include <set>
#include <algorithm>
#include <ctime>

class PMergeMe
{
private:

	clock_t								start;
	clock_t								end;
	long								size;
	double								processingTime;

	std::vector<int>					vector;
	MyList<int>							list;
	MySet<int>							set;
	
	void				stopProcessingTimer();

	PMergeMe(PMergeMe const& copy);
	PMergeMe & operator=(PMergeMe const& copy);

public:
	PMergeMe();
	~PMergeMe();

	void				addNumber(int n);
	void				displaySorted();
	void				fordJohnson();
};

#endif // __PMERGEME_HPP__