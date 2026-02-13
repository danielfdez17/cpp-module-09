#pragma once
#ifndef __MYSET_HPP__
#define __MYSET_HPP__

#include "utils.hpp"
#include <iostream>
#include <set>
#include <stdexcept>

// struct ComPair
// {
// 	// bool operator()(const int&a, const int&b)
// 	// {
// 	// 	return a < b;
// 	// }
	
// 	bool operator()(const std::pair<int, int>& a, const std::pair<int, int>& b)
// 	{
// 		// ! strictly sorted
// 		if (a.second != b.second)
// 			return a.second < b.second;
// 		return a.first < b.first;
// 	}
// };

// template <typename T, class Comparator = std::less<T> >
// class MySet : public std::set<T, Comparator>
template <typename T>
class MySet : public std::set<T>
{
private:

public:
	MySet();
	MySet(MySet const& copy);
	MySet & operator=(MySet const& copy);
	~MySet();

	T	&operator[](int idx);
	T	operator[](int idx) const;
	
};

#include "MySet.tpp"

#endif // __MYSET_HPP__