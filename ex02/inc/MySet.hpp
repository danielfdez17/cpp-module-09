#pragma once
#ifndef __MYSET_HPP__
#define __MYSET_HPP__

#include "utils.hpp"
#include <iostream>
#include <set>
#include <stdexcept>

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