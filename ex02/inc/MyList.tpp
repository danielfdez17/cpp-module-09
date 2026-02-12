#include "MyList.hpp"
#include <iostream>

template <typename T>
MyList<T>::MyList() : std::list<T>()
{
}

template <typename T>
MyList<T>::MyList(MyList const& copy) : std::list<T>(copy)
{
}

template <typename T>
MyList<T> &MyList<T>::operator=(MyList<T> const& copy)
{
	if (this != &copy)
	{
		std::list<T>::operator=(copy);
	}
	return *this;
}

template <typename T>
MyList<T>::~MyList()
{
}

template <typename T>
T	&MyList<T>::operator[](int idx)
{
	if (idx < 0 || idx >= static_cast<long>(this->size()))
		throw std::out_of_range("Index out of range");

	typename std::list<T>::iterator it = this->begin();
	std::advance(it, idx);
	return *it;
}

template <typename T>
T	MyList<T>::operator[](int idx) const
{
	if (idx < 0 || idx >= static_cast<long>(this->size()))
		throw std::out_of_range("Index out of range");

	typename std::list<T>::const_iterator it = this->begin();
	std::advance(it, idx);
	return *it;
}

// ! conflicts with std::string class
// template <typename Container>
// std::ostream &operator<<(std::ostream &out, const Container&c)
// {
// 	typename Contaienr::const_iterator it;
// 	for (it = c.begin(); it != c.end(); it++)
// 		out << *it << " ";
// 	return out;
// }
