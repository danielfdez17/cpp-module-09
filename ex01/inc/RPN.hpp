#pragma once
#ifndef __RPN_HPP__
#define __RPN_HPP__

#include "utils.hpp"
#include <iostream>
#include <stack>

class RPN
{
private:

	std::stack<float>	stack;

	bool				isValidRPN(std::string) const;
	float				processOp(float, char, float);
	bool				processRPN(std::string);
	void				displayResult() const;

	RPN();
	RPN(RPN const& copy);
	RPN & operator=(RPN const& copy);
	
public:
	RPN(std::string);
	~RPN();

};

#endif // __RPN_HPP__