#pragma once
#ifndef __PMERGEME_HPP__
#define __PMERGEME_HPP__

#include "utils.hpp"
#include <iostream>
#include <vector>
#include <list>
#include <set>
#include <ctime>

class PMergeMe
{
private:

	std::vector<int>	vector;
	std::list<int>		list;
	std::set<int>		set;
	clock_t				start;
	clock_t				end1;
	clock_t				end2;
	long				size;
	void	swap(int &, int &);
	
public:
	PMergeMe();
	PMergeMe(PMergeMe const& copy);
	PMergeMe & operator=(PMergeMe const& copy);
	~PMergeMe();

	void	addNumber(int n);
	void	displaySorted() const;
	void	sort1();
	void	sort2();
};

#endif // __PMERGEME_HPP__