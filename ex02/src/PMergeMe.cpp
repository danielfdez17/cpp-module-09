#include "PMergeMe.hpp"
#include "templates.hpp"
#include <string>
#include <iostream>
#include <iomanip>
#include <list>

PMergeMe::PMergeMe() : start(clock()), size(0), processingTime(0.0), extra(-1), mainV(0, 0), pendV(0, 0) {}

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
	std::cout << std::fixed << std::setprecision(DISPLAYED_PRECISION);
	std::cout << BLUE "Time to process a range of " << this->size << " elements with std::vector<int> : " << sortingTime(this->vector) + this->processingTime << " us\n";
	
}

void	PMergeMe::sortList()
{
	std::cout << std::fixed << std::setprecision(DISPLAYED_PRECISION);
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

// ? Jacobsthal sequence untill n
static std::vector<int>	generateTill(int n)
{
	std::vector<int>jacob(n, 0);
	// ? Base cases
	jacob[0] = 0;
	jacob[1] = 1;
	jacob[2] = 1;

	// ? Recursive case
	for (int i = 2; i < n; i++)
	{
		jacob[i] = jacob[i - 1] + (2 * jacob[i - 2]);
	}
	return jacob;
}

std::vector<int>	PMergeMe::jacobsthalSeq(int n) const
{
	std::vector<int> seq(0,0);
	std::vector<int> jacob = generateTill(n);
	
	for (size_t i = 1; i < jacob.size() - 1; i++)
	{
		int start = jacob[i];
		int end = n;
		if (i + 1 < jacob.size())
			end = jacob[i + 1];

		for (size_t j = std::min(end, n) - 1; j < (size_t)start; j++)
			seq.push_back(j);
	}

	return seq;
}

// ! this is the recursive function
void	PMergeMe::fordJohnson()
{
	if (this->size <= 1)
		return ;
	
		
	// ? Make pairs and sort by second component
	if (DEBUG)
		std::cout << "\nInserting: ";

	for (long i = 0; i < this->size - 1; i += 2)
	{
		if (i + 1 < this->size)
		{
			std::pair<int,int> p;
			if (this->vector[i] < this->vector[i + 1])
				p = std::make_pair(this->vector[i + 1], this->vector[i]);
			else
				p = std::make_pair(this->vector[i], this->vector[i + 1]);
			if (DEBUG)
				std::cout << "{" << p.first << "," << p.second << "} ";
			this->pairs.push_back(p);
		}
		else
			this->extra = this->vector[i];
	}

	// ? Split values
	for (size_t i = 0; i < this->pairs.size(); i++)
	{
		this->mainV.push_back(this->pairs[i].first);
		this->pendV.push_back(this->pairs[i].second);
	}

	if (DEBUG)
	{
		std::cout << "\nPrinting: ";
		for (size_t i = 0; i < this->mainV.size(); i++)
		{
			std::cout << "{" << this->mainV[i] << "," << this->pendV[i] << "} ";
		}
	}

	if (this->extra != -1)
	{
		this->pendV.push_back(this->extra);
		if (DEBUG)
			std::cout << "{" << this->extra << "} ";
	}
	std::cout << "\n";

	// ? Sort mainV recursively
	fordJohnson();
	// if (DEBUG)
	// 	print(this->mainV);
	// recursiveMergeSort(this->mainV, 0, this->mainV.size() - 1);
	// if (DEBUG)
	// 	print(this->mainV);
	
	// ? Insert pendV[0] at the beginning (mainV.push_front(pendV[0]))
	this->vector.insert(std::lower_bound(this->vector.begin(), this->vector.end(), pendV[0]), pendV[0]);
	// this->mainV.push_back(pendV[0]);
	// for (size_t i = this->mainV.size() - 1; i > 0; i--)
	// 	this->mainV[i] = this->mainV[i - 1];
	// this->mainV[0] = this->pendV[0];
	// if (DEBUG)
	// 	print(this->mainV);

	// ? Insert the remaining of pendV
	std::vector<int> jacob = jacobsthalSeq((int)this->pendV.size());
	print(jacob);
	return ;
	for (size_t i = 0; i < jacob.size(); i++)
	{
		if (i < this->pendV.size())
		{
			this->vector.insert(std::lower_bound(this->vector.begin(), this->vector.end(), this->pendV[i]), this->pendV[i]);
		}
	}
	if (this->extra != -1)
	{
		this->vector.insert(std::lower_bound(this->vector.begin(), this->vector.end(), this->extra), this->extra);
	}
	print(this->vector);

}

