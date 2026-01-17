#include "PMergeMe.hpp"
#include <string>
#include <iostream>

void	PMergeMe::swap(int &a, int &b)
{
	int tmp = a;
	a = b;
	b = tmp;
}

PMergeMe::PMergeMe() : start(clock()), size(0)
{
}

PMergeMe::PMergeMe(PMergeMe const &copy) { (void)copy; }

PMergeMe &PMergeMe::operator=(PMergeMe const &copy)
{
	(void)copy;
	return *this;
}

PMergeMe::~PMergeMe() {}

void	PMergeMe::addNumber(int n)
{
	if (this->set.find(n) != this->set.end())
		return;
	this->set.insert(n);
	this->vector.push_back(n);
	this->list.push_back(n);
}

void	PMergeMe::displaySorted() const
{
	std::set<int>::iterator it = this->set.begin();
	while (it != this->set.end())
	{
		std::cout << *it << " ";
		++it;
	}
	std::cout << "\n";
}

void	PMergeMe::sort1()
{
	
	this->end1 = clock();
	double elapsed = double(this->end1 - this->start) / CLOCKS_PER_SEC;
	std::cout << "Time to process a range of " << this->set.size() << " elements with std::vector<int> : " << elapsed << " us\n";
}

void	PMergeMe::sort2()
{
	
	this->end2 = clock();
	double elapsed = double(this->end2 - this->start) / CLOCKS_PER_SEC;
	std::cout << "Time to process a range of " << this->set.size() << " elements with std::list<int>   : " << elapsed << " us\n";
}

