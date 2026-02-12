#pragma once
#ifndef __MYLIST_HPP__
#define __MYLIST_HPP__

#include "utils.hpp"
#include <iostream>
#include <vector>
#include <list>
#include <set>
#include <ctime>
#include <stdexcept>

template <typename T>
class MyList : public std::list<T>
{
private:

public:
	MyList();
	MyList(MyList const& copy);
	MyList & operator=(MyList const& copy);
	~MyList();

	T	&operator[](int idx);
	T	operator[](int idx) const;
	
};

#include "MyList.tpp"

#endif // __MYLIST_HPP__