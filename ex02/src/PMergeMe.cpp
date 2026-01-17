#include "PMergeMe.hpp"
#include <string>
#include <iostream>

// void	PMergeMe::listMerge(long begin, long mid, long end)
// {
// 	long left = mid - begin + 1;
// 	long right = end - mid;

// 	std::list<int> vLeft, vRight;

// 	// ? split stage
// 	for (long i = 0; i < left; i++)
// 		vLeft.push_back(this->list[begin + i]);
// 	for (long i = 0; i < right; i++)
// 		vRight.push_back(this->vector[mid + 1 + i]);
	
// 	long i = 0, j = 0, k = begin;
	
// 	// ? merge stage
// 	while (i < left && j < right)
// 	{
// 		if (vLeft[i] <= vRight[j])
// 		{
// 			this->vector[k] = vLeft[i];
// 			i++;
// 		}
// 		else
// 		{
// 			this->vector[k] = vRight[j];
// 			j++;
// 		}
// 		k++;
// 	}

// 	// ? copy remaining values
// 	while (i < left)
// 	{
// 		this->vector[k] = vLeft[i];
// 		i++;
// 		k++;
// 	}

// 	while (j < right)
// 	{
// 		this->vector[k] = vRight[j];
// 		j++;
// 		k++;
// 	}
// }

// void	PMergeMe::listMergeSort(long begin, long end)
// {
// 	if (begin >= end)
// 		return;
	
// 	long mid = begin + (end - begin) / 2;
// 	this->listMergeSort(begin, mid);
// 	this->listMergeSort(mid + 1, end);
// 	this->listMerge(begin, mid, end);
// }

void	PMergeMe::vectorMerge(long begin, long mid, long end)
{
	long left = mid - begin + 1;
	long right = end - mid;

	std::vector<int> vLeft, vRight;

	// ? split stage
	for (long i = 0; i < left; i++)
		vLeft.push_back(this->vector[begin + i]);
	for (long i = 0; i < right; i++)
		vRight.push_back(this->vector[mid + 1 + i]);
	
	long i = 0, j = 0, k = begin;
	
	// ? merge stage
	while (i < left && j < right)
	{
		if (vLeft[i] <= vRight[j])
		{
			this->vector[k] = vLeft[i];
			i++;
		}
		else
		{
			this->vector[k] = vRight[j];
			j++;
		}
		k++;
	}

	// ? copy remaining values
	while (i < left)
	{
		this->vector[k] = vLeft[i];
		i++;
		k++;
	}

	while (j < right)
	{
		this->vector[k] = vRight[j];
		j++;
		k++;
	}
}

void	PMergeMe::vectorMergeSort(long begin, long end)
{
	if (begin >= end)
		return;
	
	long mid = begin + (end - begin) / 2;
	this->vectorMergeSort(begin, mid);
	this->vectorMergeSort(mid + 1, end);
	this->vectorMerge(begin, mid, end);
}

PMergeMe::PMergeMe() : start(clock()), size(0) {}

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
	this->end2 = clock();
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
	this->vectorMergeSort(0, this->size - 1);
	std::cout << MAGENTA "vector: ";
	for (long i = 0 ; i < this->size; i++)
		std::cout << this->vector[i] << " ";
	std::cout << "\n" RESET;
	this->end1 = clock();
	double elapsed = double(this->end1 - this->start) / CLOCKS_PER_SEC;
	std::cout << BLUE "Time to process a range of " << this->size << " elements with std::vector<int> : " << elapsed << " us\n";
}

void	PMergeMe::sort2()
{
	// std::cout << MAGENTA "list  : ";
	// for (std::list<int>::iterator it = this->list.begin() ; it != this->list.end(); ++it)
	// 	std::cout << *it << " ";
	// std::cout << "\n" RESET;
	// this->end2 = clock();
	double elapsed = double(this->end2 - this->start) / CLOCKS_PER_SEC;
	std::cout << CYAN "Time to process a range of " << this->size << " elements with std::set<int>    : " << elapsed << " us\n" RESET;
}

