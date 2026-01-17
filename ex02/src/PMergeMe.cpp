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
	long left = mid - begin + 1;
	long right = end - mid;

	std::list<int> leftList, rightList;

	// ? split stage
	for (long i = 0; i < left; i++)
		leftList.push_back(this->getValueAt(this->list, begin + i));
	for (long i = 0; i < right; i++)
		rightList.push_back(this->getValueAt(this->list, mid + 1 + i));
	
	long i = 0, j = 0, k = begin;
	
	// ? merge stage
	while (i < left && j < right)
	{
		if (this->getValueAt(leftList, i) <= this->getValueAt(rightList, j))
		{
			this->setValueAt(this->list, k, this->getValueAt(leftList, i));
			i++;
		}
		else
		{
			this->setValueAt(this->list, k, this->getValueAt(rightList, j));
			j++;
		}
		k++;
	}

	// ? copy remaining values
	while (i < left)
	{
		this->setValueAt(this->list, k, this->getValueAt(leftList, i));
		i++;
		k++;
	}

	while (j < right)
	{
		this->setValueAt(this->list, k, this->getValueAt(rightList, j));
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
	this->end1 = clock();
	double elapsed = double(this->end1 - this->start) / CLOCKS_PER_SEC;
	std::cout << BLUE "Time to process a range of " << this->size << " elements with std::vector<int> : " << elapsed << " us\n";
}

void	PMergeMe::display1() const
{
	std::cout << MAGENTA "vector: ";
	for (long i = 0 ; i < this->size; i++)
		std::cout << this->vector[i] << " ";
	std::cout << "\n" RESET;
}

void	PMergeMe::sort2()
{

	this->end2 = clock();
	double elapsed = double(this->end2 - this->start) / CLOCKS_PER_SEC;
	std::cout << CYAN "Time to process a range of " << this->size << " elements with std::set<int>    : " << elapsed << " us\n" RESET;
}
void	PMergeMe::display2() const
{
	std::cout << MAGENTA "list  : ";
	for (long i = 0 ; i < this->size; i++)
		std::cout << this->getValueAt(this->list, i) << " ";
	// for (std::list<int>::iterator it = this->list.begin() ; it != this->list.end(); ++it)
	// 	std::cout << *it << " ";
	std::cout << "\n" RESET;
}
