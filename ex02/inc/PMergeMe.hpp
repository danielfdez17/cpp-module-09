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


	void	vectorMerge(long, long, long);
	void	vectorMergeSort(long, long);
	// void	listMerge(long, long, long);
	// void	listMergeSort(long, long);
	
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