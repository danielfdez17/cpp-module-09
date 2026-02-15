#include "PMergeMe.hpp"

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
Container	fordJohnsonTemplate(Container const& container)
{
	if (container.size() <= 1)
		return container;

	// ? Make pairs and sort by second component
	if (DEBUGGING)
		std::cout << "\nInserting: ";

	std::vector<std::pair<int, int> > pairs;
	bool hasOddValue = container.size() % 2 != 0;
	int oddValue = container[container.size() - 1];

	for (size_t i = 0; i < container.size() - 1; i += 2)
	{
		std::pair<int,int> p;
		if (container[i] < container[i + 1])
			p = std::make_pair(container[i + 1], container[i]);
		else
			p = std::make_pair(container[i], container[i + 1]);
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

	Container mainChain;
	Container pendingChain;
	
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
	Container result = fordJohnsonTemplate(mainChain);

	// ? Insert pendingChain[0] at the beginning (mainV.push_front(pendingChain[0]))
	result.insert(std::lower_bound(result.begin(), result.end(), pendingChain[0]), pendingChain[0]);

	// ? Insert the remaining of pendingChain
	std::vector<int> jacob = jacobsthalSeq((int)pendingChain.size());
	for (size_t i = 0; i < jacob.size(); i++)
	{
		if (static_cast<size_t>(jacob[i]) < pendingChain.size())
		{
			result.insert(std::lower_bound(result.begin(), result.end(), pendingChain[jacob[i]]), pendingChain[jacob[i]]);
		}
	}

	return result;
}

