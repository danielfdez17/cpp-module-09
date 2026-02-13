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

void	PMergeMe::displaySorted() const
{
	std::cout << MAGENTA "std::vector<int>: ";
	print(this->vector);
	std::cout << MAGENTA "     MyList<int>: ";
	print(this->list);
	if (DEBUG)
	{
		std::cout << MAGENTA "  std::set<int>: ";
		std::set<int>::iterator it = this->set.begin();
		while (it != this->set.end())
		{
				std::cout << *it << " ";
				++it;
			}
		std::cout << "\n";
		}
	}

void	PMergeMe::sortVector()
{
	this->start = clock();
	recursiveMergeSort(this->vector, 0, this->size - 1);
	this->end = clock();
	double elapsed = double(this->end - this->start) / CLOCKS_PER_SEC;
	std::cout << BLUE "Time to process a range of " << this->size << " elements with std::vector<int> : " << elapsed + this->processingTime << " us\n";
}

void	PMergeMe::sortList()
{
	this->start = clock();
	recursiveMergeSort(this->list, 0, this->size - 1);
	this->end = clock();
	double elapsed = double(this->end - this->start) / CLOCKS_PER_SEC;
	std::cout << CYAN "Time to process a range of " << this->size << " elements with      MyList<int> : " << elapsed + this->processingTime << " us\n" RESET;
}

void	PMergeMe::sort()
{
	this->sortVector();
	this->sortList();
}

void	PMergeMe::stopProcessingTimer()
{
	this->end = clock();
	this->processingTime = double(this->end - this->start) / CLOCKS_PER_SEC;
}
