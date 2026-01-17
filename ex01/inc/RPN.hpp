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
	void				processRPN(std::string);
	void				displayResult() const;
	
public:
	RPN();
	RPN(std::string);
	RPN(RPN const& copy);
	RPN & operator=(RPN const& copy);
	~RPN();

};

#endif // __RPN_HPP__