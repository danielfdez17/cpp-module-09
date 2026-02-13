#pragma once
#ifndef __PMERGEME_HPP__
#define __PMERGEME_HPP__

#include "MyList.hpp"
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
	// std::list<int>		list;
	MyList<int>			list;
	std::set<int>		set;
	clock_t				start;
	clock_t				end;
	long				size;
	double				processingTime;
	
	PMergeMe(PMergeMe const& copy);
	PMergeMe & operator=(PMergeMe const& copy);

	void				sortVector();
	void				sortList();

public:
	PMergeMe();
	~PMergeMe();

	void				addNumber(int n);
	void				displaySorted() const;
	void				sort();
	void				stopProcessingTimer();
};




#endif // __PMERGEME_HPP__