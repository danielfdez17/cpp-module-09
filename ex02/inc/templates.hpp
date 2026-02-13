#pragma once
#ifndef __TEMPLATES_HPP__
#define __TEMPLATES_HPP__

template <typename Container>
void	recursiveMergeSort(Container &c, long begin, long mid, long end);

template <typename Container>
void	mergeSort(Container &c, long begin, long mid, long end);

template <typename Container>
void	print(Container const&c);

#include "templates.tpp"

#endif // __TEMPLATES_HPP__