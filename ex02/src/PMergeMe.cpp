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
	// this->end = clock();
}

void	PMergeMe::display() const
{
	std::cout << MAGENTA "std::vector<int>: ";
	print(this->vector);
	std::cout << MAGENTA "     MyList<int>: ";
	print(this->list);
}

void	PMergeMe::displaySorted()
{
	this->stopProcessingTimer();
	print(this->set);
}

void	PMergeMe::sortVector()
{
	std::cout	<< std::fixed << std::setprecision(DISPLAYED_PRECISION);
	std::cout	<< BLUE "Time to process a range of "
				<< this->size
				<< " elements with std::vector<int> : not fully counted"
				<< this->processingTime
				<< " us\n";
	
}

void	PMergeMe::sortList()
{
	std::cout	<< std::fixed << std::setprecision(DISPLAYED_PRECISION);
	std::cout	<< CYAN "Time to process a range of "
				<< this->size
				<< " elements with      MyList<int> : not fully counted"
				<< this->processingTime
				<< " us\n" RESET;
}

void	PMergeMe::sort()
{
	this->sortVector();
	this->sortList();
	if (DEBUGGING)
	{
		std::cout << DEBUG;
		this->display();
		std::cout << RESET;
	}
}

void	PMergeMe::stopProcessingTimer()
{
	this->end = clock();
	this->processingTime = double(this->end - this->start) / CLOCKS_PER_SEC;
}

// ? Jacobsthal sequence until n
static std::vector<int>	generateTill(int n)
{
	std::vector<int> jacob;

	// ? Base cases
	jacob.push_back(0);
	jacob.push_back(1);

	// ? Recursive case
	for (int i = 2; i < n; i++)
	{
		jacob.push_back(jacob[i - 1] + (2 * jacob[i - 2]));
	}
	return jacob;
}

std::vector<int>	PMergeMe::jacobsthalSeq(int n) const
{
	std::vector<int> seq;
	std::vector<int> jacob = generateTill(n + 2); // Generate enough Jacobsthal numbers
	
	for (size_t i = 1; i < jacob.size() && jacob[i] <= n; i++)
	{
		// ? Skip if this Jacobsthal number is the same as previous (duplicate)
		if (i > 1 && jacob[i] == jacob[i - 1])
			continue;
			
		int start = (i == 1) ? 0 : jacob[i - 1];
		int end = jacob[i];
		size_t lower = static_cast<size_t>(start);
		size_t upper = static_cast<size_t>(std::min(end, n - 1));
		
		for (size_t j = upper; j > lower; j--)
			seq.push_back(j);
	}

	return seq;
}

std::vector<int> PMergeMe::fordJohnson(const std::vector<int>&vector)
{
	if (vector.size() <= 1)
		return vector;

	// ? Make pairs and sort by second component
	if (DEBUGGING)
		std::cout << "\nInserting: ";

	std::vector<std::pair<int, int> > pairs;
	bool hasOddValue = vector.size() % 2 != 0;
	int oddValue = vector[vector.size() - 1];

	for (size_t i = 0; i < vector.size() - 1; i += 2)
	{
		std::pair<int,int> p;
		if (vector[i] < vector[i + 1])
			p = std::make_pair(vector[i + 1], vector[i]);
		else
			p = std::make_pair(vector[i], vector[i + 1]);
		if (DEBUGGING)
			std::cout << "{" << p.first << "," << p.second << "} ";
		pairs.push_back(p);
	}
	
	if (DEBUGGING)
	{
		std::cout << "\nBefore sorting pairs: ";
		for (size_t i = 0; i < pairs.size(); i++)
		{
			std::cout << "{" << pairs[i].first << "," << pairs[i].second << "} ";
		}
		std::cout << "\n";
	}
	// ? Sort pairs by first element to maintain pairing
	std::sort(pairs.begin(), pairs.end());

	if (DEBUGGING)
	{
		std::cout << "After sorting pairs: ";
		for (size_t i = 0; i < pairs.size(); i++)
		{
			std::cout << "{" << pairs[i].first << "," << pairs[i].second << "} ";
		}
		std::cout << "\n";
	}

	std::vector<int> mainChain;
	std::vector<int> pendingChain;
	
	// ? Split sorted pairs
	for (size_t i = 0; i < pairs.size(); i++)
	{
		mainChain.push_back(pairs[i].first);
		pendingChain.push_back(pairs[i].second);
	}

	if (hasOddValue)
	{
		pendingChain.push_back(oddValue);
		if (DEBUGGING)
			std::cout << "OddValue: {" << oddValue << "}\n";
	}

	// ? Recursively sort mainChain
	std::vector<int> mainSorted = fordJohnson(mainChain);

	std::vector<int> result = mainSorted;

	// ? Insert pendV[0] at the beginning (mainV.push_front(pendV[0]))
	result.insert(std::lower_bound(result.begin(), result.end(), pendingChain[0]), pendingChain[0]);

	// ? Insert the remaining of pendV
	std::vector<int> jacob = this->jacobsthalSeq((int)pendingChain.size());
	for (size_t i = 0; i < jacob.size(); i++)
	{
		if (static_cast<size_t>(jacob[i]) < pendingChain.size())
		{
			result.insert(std::lower_bound(result.begin(), result.end(), pendingChain[jacob[i]]), pendingChain[jacob[i]]);
		}
	}

	return result;
}

MyList<int> PMergeMe::fordJohnson(const MyList<int>&list)
{
	if (list.size() <= 1)
		return list;

	// ? Make pairs and sort by second component
	if (DEBUGGING)
		std::cout << "\nInserting: ";

	std::vector<std::pair<int, int> > pairs;
	bool hasOddValue = list.size() % 2 != 0;
	int oddValue = list[list.size() - 1];

	for (size_t i = 0; i < list.size() - 1; i += 2)
	{
		std::pair<int,int> p;
		if (list[i] < list[i + 1])
			p = std::make_pair(list[i + 1], list[i]);
		else
			p = std::make_pair(list[i], list[i + 1]);
		if (DEBUGGING)
			std::cout << "{" << p.first << "," << p.second << "} ";
		pairs.push_back(p);
	}
	
	if (DEBUGGING)
	{
		std::cout << "\nBefore sorting pairs: ";
		for (size_t i = 0; i < pairs.size(); i++)
		{
			std::cout << "{" << pairs[i].first << "," << pairs[i].second << "} ";
		}
		std::cout << "\n";
	}
	// ? Sort pairs by first element to maintain pairing
	std::sort(pairs.begin(), pairs.end());

	if (DEBUGGING)
	{
		std::cout << "After sorting pairs: ";
		for (size_t i = 0; i < pairs.size(); i++)
		{
			std::cout << "{" << pairs[i].first << "," << pairs[i].second << "} ";
		}
		std::cout << "\n";
	}

	MyList<int> mainChain;
	MyList<int> pendingChain;
	
	// ? Split sorted pairs
	for (size_t i = 0; i < pairs.size(); i++)
	{
		mainChain.push_back(pairs[i].first);
		pendingChain.push_back(pairs[i].second);
	}

	if (DEBUGGING)
	{
		std::cout << "\nAfter sorting pairs: ";
		for (size_t i = 0; i < mainChain.size(); i++)
		{
			std::cout << "{" << mainChain[i] << "," << pendingChain[i] << "} ";
		}
		std::cout << "\n";
	}

	if (hasOddValue)
	{
		pendingChain.push_back(oddValue);
		if (DEBUGGING)
			std::cout << "OddValue: {" << oddValue << "}\n";
	}

	// ? Recursively sort mainChain
	MyList<int> mainSorted = fordJohnson(mainChain);

	MyList<int> result = mainSorted;

	// ? Insert pendV[0] at the beginning (mainV.push_front(pendV[0]))
	result.insert(std::lower_bound(result.begin(), result.end(), pendingChain[0]), pendingChain[0]);

	// ? Insert the remaining of pendV
	std::vector<int> jacob = this->jacobsthalSeq((int)pendingChain.size());
	for (size_t i = 0; i < jacob.size(); i++)
	{
		if (static_cast<size_t>(jacob[i]) < pendingChain.size())
		{
			result.insert(std::lower_bound(result.begin(), result.end(), pendingChain[jacob[i]]), pendingChain[jacob[i]]);
		}
	}

	return result;
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
	std::vector<int> result = fordJohnson(this->vector);
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
	MyList<int> resultList = fordJohnson(this->list);
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

