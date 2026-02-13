#pragma once
#ifndef __TEMPLATES_HPP__
#define __TEMPLATES_HPP__

template <typename Container>
void	recursiveMergeSort(Container &c, long begin, long mid, long end);

template <typename Container>
void	mergeSort(Container &c, long begin, long mid, long end);

template <typename Container>
void	print(Container const&c);

template <typename Container>
double	sortingTime(Container &c);

// template <typename Container>
// Container fordJohnson(Container &c);
std::vector<int> fordJohnsonV(const std::vector<int>&v);

#include "templates.tpp"

#endif // __TEMPLATES_HPP__