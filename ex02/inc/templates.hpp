#pragma once
#ifndef __TEMPLATES_HPP__
#define __TEMPLATES_HPP__

template <typename Container>
void	print(Container const&c);

template <typename Container>
Container	fordJohnsonTemplate(Container const& container);

template <typename Container>
bool	isSorted(Container const&c);

#include "templates.tpp"

#endif // __TEMPLATES_HPP__