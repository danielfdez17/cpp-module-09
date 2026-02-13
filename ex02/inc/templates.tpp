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
