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
