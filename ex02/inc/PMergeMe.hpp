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

	int		getValueAt(std::list<int>const&, long) const;
	void	setValueAt(std::list<int>&, long, int);

	void	vectorMerge(long, long, long);
	void	vectorMergeSort(long, long);
	void	listMerge(long, long, long);
	void	listMergeSort(long, long);
	
public:
	PMergeMe();
	PMergeMe(PMergeMe const& copy);
	PMergeMe & operator=(PMergeMe const& copy);
	~PMergeMe();

	void				addNumber(int n);
	void				displaySorted() const;
	void				sortVector();
	void				sortList();
	void				stopProcessingTimer();
	std::vector<int>	getVector() const;
	MyList<int>			getList() const;
};

std::ostream &operator<<(std::ostream &out, PMergeMe const&algo);

#endif // __PMERGEME_HPP__