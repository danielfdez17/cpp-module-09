#include "PMergeMe.hpp"
#include "templates.hpp"
#include <string>
#include <iostream>
#include <list>

PMergeMe::PMergeMe() : start(clock()), size(0), processingTime(0.0) {}

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
	this->size++;
	this->end = clock();
}

void	PMergeMe::display() const
{
	std::cout << MAGENTA "std::vector<int>: ";
	print(this->vector);
	std::cout << MAGENTA "     MyList<int>: ";
	print(this->list);
}

void	PMergeMe::displaySorted() const
{
	print(this->set);
	// std::cout << "";
	// std::set<int>::iterator it = this->set.begin();
	// while (it != this->set.end())
	// {
	// 	std::cout << *it << " ";
	// 	++it;
	// }
	// std::cout << "\n";
}

void	PMergeMe::sortVector()
{
	std::cout << BLUE "Time to process a range of " << this->size << " elements with std::vector<int> : " << sortingTime(this->vector) + this->processingTime << " us\n";
	
}

void	PMergeMe::sortList()
{
	std::cout << CYAN "Time to process a range of " << this->size << " elements with      MyList<int> : " << sortingTime(this->list) + this->processingTime << " us\n" RESET;
}

void	PMergeMe::sort()
{
	this->sortVector();
	this->sortList();
	if (DEBUG)
	{
		this->display();
	}
}

void	PMergeMe::stopProcessingTimer()
{
	this->end = clock();
	this->processingTime = double(this->end - this->start) / CLOCKS_PER_SEC;
}
