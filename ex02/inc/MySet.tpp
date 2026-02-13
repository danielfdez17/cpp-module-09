#include "MySet.hpp"
#include <iostream>

template <typename T>
MySet<T>::MySet() : std::set<T>()
{
}

template <typename T>
MySet<T>::MySet(MySet const& copy) : std::set<T>(copy)
{
}

template <typename T>
MySet<T> &MySet<T>::operator=(MySet<T> const& copy)
{
	if (this != &copy)
	{
		std::set<T>::operator=(copy);
	}
	return *this;
}

template <typename T>
MySet<T>::~MySet()
{
}

template <typename T>
T	&MySet<T>::operator[](int idx)
{
	if (idx < 0 || idx >= static_cast<long>(this->size()))
		throw std::out_of_range("Index out of range");

	typename std::set<T>::iterator it = this->begin();
	std::advance(it, idx);
	return *it;
}

template <typename T>
T	MySet<T>::operator[](int idx) const
{
	if (idx < 0 || idx >= static_cast<long>(this->size()))
		throw std::out_of_range("Index out of range");

	typename std::set<T>::const_iterator it = this->begin();
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
