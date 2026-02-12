#include "PMergeMe.hpp"
#include <string>
#include <iostream>
#include <list>

int	PMergeMe::getValueAt(std::list<int>const& lst, long index) const
{
	if (index < 0 || index >= static_cast<long>(lst.size()))
		throw std::out_of_range("Index out of range");
	
	std::list<int>::const_iterator it = lst.begin();
	std::advance(it, index);
	return *it;
}

void	PMergeMe::setValueAt(std::list<int>& lst, long index, int value)
{
	if (index < 0 || index >= static_cast<long>(lst.size()))
		throw std::out_of_range("Index out of range");
	
	std::list<int>::iterator it = lst.begin();
	std::advance(it, index);
	*it = value;
}

void	PMergeMe::listMerge(long begin, long mid, long end)
{
	// long left = mid - begin + 1;
	// long right = end - mid;

	// std::list<int> leftList, rightList;

	// // ? split stage
	// for (long i = 0; i < left; i++)
	// 	leftList.push_back(this->getValueAt(this->list, begin + i));
	// for (long i = 0; i < right; i++)
	// 	rightList.push_back(this->getValueAt(this->list, mid + 1 + i));
	
	// long i = 0, j = 0, k = begin;
	
	// // ? merge stage
	// while (i < left && j < right)
	// {
	// 	if (this->getValueAt(leftList, i) <= this->getValueAt(rightList, j))
	// 	{
	// 		this->setValueAt(this->list, k, this->getValueAt(leftList, i));
	// 		i++;
	// 	}
	// 	else
	// 	{
	// 		this->setValueAt(this->list, k, this->getValueAt(rightList, j));
	// 		j++;
	// 	}
	// 	k++;
	// }

	// // ? copy remaining values
	// while (i < left)
	// {
	// 	this->setValueAt(this->list, k, this->getValueAt(leftList, i));
	// 	i++;
	// 	k++;
	// }

	// while (j < right)
	// {
	// 	this->setValueAt(this->list, k, this->getValueAt(rightList, j));
	// 	j++;
	// 	k++;
	// }
	long left = mid - begin + 1;
	long right = end - mid;

	MyList<int> leftList, rightList;

	// ? split stage
	for (long i = 0; i < left; i++)
		leftList.push_back(this->vector[begin + i]);
	for (long i = 0; i < right; i++)
		rightList.push_back(this->vector[mid + 1 + i]);
	
	long i = 0, j = 0, k = begin;
	
	// ? merge stage
	while (i < left && j < right)
	{
		if (leftList[i] <= rightList[j])
		{
			this->vector[k] = leftList[i];
			i++;
		}
		else
		{
			this->vector[k] = rightList[j];
			j++;
		}
		k++;
	}

	// ? copy remaining values
	while (i < left)
	{
		this->vector[k] = leftList[i];
		i++;
		k++;
	}

	while (j < right)
	{
		this->vector[k] = rightList[j];
		j++;
		k++;
	}
}

void	PMergeMe::listMergeSort(long begin, long end)
{
	if (begin >= end)
		return;
	
	long mid = begin + (end - begin) / 2;
	this->listMergeSort(begin, mid);
	this->listMergeSort(mid + 1, end);
	this->listMerge(begin, mid, end);
}

void	PMergeMe::vectorMerge(long begin, long mid, long end)
{
	long left = mid - begin + 1;
	long right = end - mid;

	std::vector<int> leftVector, rightVector;

	// ? split stage
	for (long i = 0; i < left; i++)
		leftVector.push_back(this->vector[begin + i]);
	for (long i = 0; i < right; i++)
		rightVector.push_back(this->vector[mid + 1 + i]);
	
	long i = 0, j = 0, k = begin;
	
	// ? merge stage
	while (i < left && j < right)
	{
		if (leftVector[i] <= rightVector[j])
		{
			this->vector[k] = leftVector[i];
			i++;
		}
		else
		{
			this->vector[k] = rightVector[j];
			j++;
		}
		k++;
	}

	// ? copy remaining values
	while (i < left)
	{
		this->vector[k] = leftVector[i];
		i++;
		k++;
	}

	while (j < right)
	{
		this->vector[k] = rightVector[j];
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
	std::set<int>::iterator it = this->set.begin();
	while (it != this->set.end())
	{
		std::cout << *it << " ";
		++it;
	}
	std::cout << "\n";
}

void	PMergeMe::sortVector()
{
	this->start = clock();
	this->vectorMergeSort(0, this->size - 1);
	this->end = clock();
	double elapsed = double(this->end - this->start) / CLOCKS_PER_SEC;
	std::cout << BLUE "Time to process a range of " << this->size << " elements with std::vector<int> : " << elapsed + this->processingTime << " us\n";
}

void	PMergeMe::sortList()
{
	this->start = clock();
	this->listMergeSort(0, this->size - 1);
	// this->vectorMergeSort(0, this->size - 1);
	this->end = clock();
	double elapsed = double(this->end - this->start) / CLOCKS_PER_SEC;
	std::cout << CYAN "Time to process a range of " << this->size << " elements with std::list<int>   : " << elapsed + this->processingTime << " us\n" RESET;
}

void	PMergeMe::stopProcessingTimer()
{
	this->end = clock();
	this->processingTime = double(this->end - this->start) / CLOCKS_PER_SEC;
}

std::vector<int>	PMergeMe::getVector() const { return this->vector; }
MyList<int>			PMergeMe::getList() const { return this->list; }

std::ostream &operator<<(std::ostream &out, PMergeMe const&algo)
{
	out << MAGENTA "std::vector<int>: ";
	for (std::vector<int>::const_iterator it = algo.getVector().begin(); it != algo.getVector().end(); it++)
		out << *it << " ";
	out << MAGENTA "\nMyList<int>: ";
	for (MyList<int>::const_iterator it = algo.getList().begin(); it != algo.getList().end(); it++)
		out << *it << " ";
	return out;
}
