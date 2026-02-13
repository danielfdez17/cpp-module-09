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
	
	void				sortVector();
	void				sortList();
	void				stopProcessingTimer();
	void				display() const;
	std::vector<int>	fordJohnson(const std::vector<int>&v);
	MyList<int>			fordJohnson(const MyList<int>&v);

public:
	PMergeMe();
	PMergeMe(PMergeMe const& copy);
	PMergeMe & operator=(PMergeMe const& copy);
	~PMergeMe();

	void				addNumber(int n);
	void				displaySorted();
	void				sort();
	void				fordJohnson();
	std::vector<int>	jacobsthalSeq(int n) const;
};

#endif // __PMERGEME_HPP__