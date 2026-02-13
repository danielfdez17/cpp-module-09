#include "PMergeMe.hpp"

template <typename Container>
void	recursiveMergeSort(Container &c, long begin, long end)
{
	if (begin >= end)
		return;
	
	long mid = begin + (end - begin) / 2;
	recursiveMergeSort(c, begin, mid);
	recursiveMergeSort(c, mid + 1, end);
	mergeSort(c, begin, mid, end);
}

template <typename Container>
void	mergeSort(Container &c, long begin, long mid, long end)
{
	long left = mid - begin + 1;
	long right = end - mid;

	std::vector<int> leftVector, rightVector;

	// ? split stage
	for (long i = 0; i < left; i++)
		leftVector.push_back(c[begin + i]);
	for (long i = 0; i < right; i++)
		rightVector.push_back(c[mid + 1 + i]);
	
	long i = 0, j = 0, k = begin;
	
	// ? merge stage
	while (i < left && j < right)
	{
		if (leftVector[i] <= rightVector[j])
		{
			c[k] = leftVector[i];
			i++;
		}
		else
		{
			c[k] = rightVector[j];
			j++;
		}
		k++;
	}

	// ? copy remaining values
	while (i < left)
	{
		c[k] = leftVector[i];
		i++;
		k++;
	}

	while (j < right)
	{
		c[k] = rightVector[j];
		j++;
		k++;
	}
}

template <typename Container>
void	print(Container const&c)
{
	size_t cSize = c.size();
	if (cSize > MAX_SIZE)
	{
		size_t i;
		for (i = 0; i < MAX_SIZE / 2; i++)
			std::cout << c[i] << " ";
		std::cout << "... ";
		for (i = cSize - (MAX_SIZE / 2); i < cSize; i++)
			std::cout << c[i] << " ";
	}
	else
	{
		for (typename Container::const_iterator it = c.begin(); it != c.end(); it++)
			std::cout << *it << " ";
	}
	std::cout << "\n" RESET;
}

template <typename Container>
double	sortingTime(Container &c)
{
	clock_t	start = clock();
	recursiveMergeSort(c, 0, c.size() - 1);
	clock_t	end = clock();
	return double(end - start) / CLOCKS_PER_SEC;
}

// template <typename Container>
// Container fordJohnson(Container &c)
// {
// 	if (c.size() <= 1)
// 		return c;

// 	// ? Make pairs and sort by second component
// 	if (DEBUG)
// 		std::cout << "\nInserting: ";

// 	std::vector<std::pair<int, int>> pairs;
// 	int oddValue = -1;

// 	for (long i = 0; i < c.size() - 1; i += 2)
// 	{
// 		if (i + 1 < c.size())
// 		{
// 			std::pair<int,int> p;
// 			if (c[i] < c[i + 1])
// 				p = std::make_pair(c[i + 1], c[i]);
// 			else
// 				p = std::make_pair(c[i], c[i + 1]);
// 			if (DEBUG)
// 				std::cout << "{" << p.first << "," << p.second << "} ";
// 			pairs.push_back(p);
// 		}
// 		else
// 			oddValue = c[i];
// 	}

// 	Container mainChain;
// 	Container pendingChain;
	
// 	// ? Split values
// 	for (size_t i = 0; i < pairs.size(); i++)
// 	{
// 		mainChain.push_back(pairs[i].first);
// 		pendingChain.push_back(pairs[i].second);
// 	}

// 	if (DEBUG)
// 	{
// 		std::cout << "\nPrinting: ";
// 		for (size_t i = 0; i < mainChain.size(); i++)
// 		{
// 			std::cout << "{" << mainChain[i] << "," << pendingChain[i] << "} ";
// 		}
// 	}

// 	if (oddValue != -1)
// 	{
// 		pendingChain.push_back(oddValue);
// 		if (DEBUG)
// 			std::cout << "{" << oddValue << "} ";
// 	}
// 	std::cout << "\n";

// 	// ? Sort mainV recursively
// 	Container mainSorted = fordJohnson(mainChain);
// 	// fordJohnson();
// 	// if (DEBUG)
// 	// 	print(this->mainV);
// 	// recursiveMergeSort(this->mainV, 0, this->mainV.size() - 1);
// 	// if (DEBUG)
// 	// 	print(this->mainV);
// 	Container result = mainSorted; // todo: review

// 	// ? Insert pendV[0] at the beginning (mainV.push_front(pendV[0]))
// 	result.insert(std::lower_bound(this->vector.begin(), this->vector.end(), pendV[0]), pendV[0]);
// 	// this->mainV.push_back(pendV[0]);
// 	// for (size_t i = this->mainV.size() - 1; i > 0; i--)
// 	// 	this->mainV[i] = this->mainV[i - 1];
// 	// this->mainV[0] = this->pendV[0];
// 	// if (DEBUG)
// 	// 	print(this->mainV);

// 	// ? Insert the remaining of pendV
// 	std::vector<int> jacob = jacobsthalSeq((int)this->pendV.size());
// 	print(jacob);
// 	return ;
// 	for (size_t i = 0; i < jacob.size(); i++)
// 	{
// 		if (i < this->pendV.size())
// 		{
// 			this->vector.insert(std::lower_bound(this->vector.begin(), this->vector.end(), this->pendV[i]), this->pendV[i]);
// 		}
// 	}
// 	if (this->extra != -1)
// 	{
// 		this->vector.insert(std::lower_bound(this->vector.begin(), this->vector.end(), this->extra), this->extra);
// 	}
// 	print(this->vector);

// }

// ? Jacobsthal sequence until n
static std::vector<int>	generateTill(int n)
{
	std::vector<int> jacob;
	// jacob.reserve(n);
	// ? Base cases
	jacob.push_back(0);
	jacob.push_back(1);
	jacob.push_back(1);

	// ? Recursive case
	for (int i = 3; i < n; i++)
	{
		jacob.push_back(jacob[i - 1] + (2 * jacob[i - 2]));
		// jacob[i] = jacob[i - 1] + (2 * jacob[i - 2]);
	}
	return jacob;
}

static std::vector<int>	jacobsthalSeq(int n)
{
	std::vector<int> seq;
	std::vector<int> jacob = generateTill(n + 3); // Generate enough Jacobsthal numbers
	
	for (size_t i = 1; i < jacob.size() && jacob[i] <= n; i++)
	{
		// Skip if this Jacobsthal number is the same as previous (duplicate)
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

std::vector<int> fordJohnsonV(const std::vector<int>&v)
{
	if (v.size() <= 1)
		return v;

	// ? Make pairs and sort by second component
	if (DEBUG)
		std::cout << "\nInserting: ";

	std::vector<std::pair<int, int> > pairs;
	bool hasOddValue = v.size() % 2 != 0;
	int oddValue = v[v.size() - 1];

	for (size_t i = 0; i < v.size() - 1; i += 2)
	{
		// if (i + 1 < v.size())
		// {
		std::pair<int,int> p;
		if (v[i] < v[i + 1])
			p = std::make_pair(v[i + 1], v[i]);
		else
			p = std::make_pair(v[i], v[i + 1]);
		if (DEBUG)
			std::cout << "{" << p.first << "," << p.second << "} ";
		pairs.push_back(p);
		// }
		// else
		// 	oddValue = v[i];
	}
	
	// ? Sort pairs by first element to maintain pairing
	std::sort(pairs.begin(), pairs.end());
	
	std::vector<int> mainChain;
	std::vector<int> pendingChain;
	
	// ? Split sorted pairs
	for (size_t i = 0; i < pairs.size(); i++)
	{
		mainChain.push_back(pairs[i].first);
		pendingChain.push_back(pairs[i].second);
	}

	if (DEBUG)
	{
		std::cout << "\nAfter sorting pairs: ";
		for (size_t i = 0; i < mainChain.size(); i++)
		{
			std::cout << "{" << mainChain[i] << "," << pendingChain[i] << "} ";
		}
	}

	if (hasOddValue)
	{
		pendingChain.push_back(oddValue);
		if (DEBUG)
			std::cout << "{" << oddValue << "} ";
	}

	// ? Recursively sort mainChain
	std::vector<int> mainSorted = fordJohnsonV(mainChain);

	std::vector<int> result = mainSorted;

	// ? Insert pendV[0] at the beginning (mainV.push_front(pendV[0]))
	result.insert(std::lower_bound(result.begin(), result.end(), pendingChain[0]), pendingChain[0]);

	// ? Insert the remaining of pendV
	std::vector<int> jacob = jacobsthalSeq((int)pendingChain.size());
	for (size_t i = 0; i < jacob.size(); i++)
	{
		if (static_cast<size_t>(jacob[i]) < pendingChain.size())
		{
			result.insert(std::lower_bound(result.begin(), result.end(), pendingChain[jacob[i]]), pendingChain[jacob[i]]);
		}
	}

	// Note: oddValue is already in pendingChain and inserted via Jacobsthal loop
	// print(result);

	return result;
}