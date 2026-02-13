#include "PMergeMe.hpp"
#include "templates.hpp"
#include <string>
#include <iostream>
#include <iomanip>
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
}

void	PMergeMe::displaySorted()
{
	this->stopProcessingTimer();
	print(this->set);
}

void	PMergeMe::stopProcessingTimer()
{
	this->end = clock();
	this->processingTime = double(this->end - this->start) / CLOCKS_PER_SEC;
}

void	PMergeMe::fordJohnson()
{
	if (DEBUGGING)
	{
		std::cout << "\n" DEBUG "Before vector: ";
		print(this->vector);
		std::cout << MAGENTA;
	}
	clock_t	start = clock();
	std::vector<int> result = fordJohnsonTemplate(this->vector);
	clock_t	end = clock();
	double elapsed = double(end - start) / CLOCKS_PER_SEC;
	std::cout	<< std::fixed << std::setprecision(DISPLAYED_PRECISION);
	std::cout	<< BLUE "Time to process a range of "
				<< this->size
				<< " elements with std::vector<int> : "
				<< elapsed + this->processingTime
				<< " us\n";
	
	if (DEBUGGING)
	{
		std::cout << DEBUG "After vector:  ";
		print(result);
		std::cout << MAGENTA "\nBefore MyList: ";
		print(this->list);
		std::cout << MAGENTA;

	}
	start = clock();
	MyList<int> resultList = fordJohnsonTemplate(this->list);
	end = clock();
	elapsed = double(end - start) / CLOCKS_PER_SEC;
	std::cout	<< std::fixed << std::setprecision(DISPLAYED_PRECISION);
	std::cout	<< CYAN "Time to process a range of "
				<< this->size
				<< " elements with      MyList<int> : "
				<< elapsed + this->processingTime
				<< " us\n" RESET;
	if (DEBUGGING)
	{
		std::cout << DEBUG "After MyList:  ";
		print(resultList);
	}

}

