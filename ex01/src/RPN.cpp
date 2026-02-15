#include "RPN.hpp"
#include <string>
#include <iomanip>

bool RPN::isValidRPN(std::string input) const
{
	size_t size = input.size();
	if (size == 0)
		return false;

	for (size_t i = 0; i < size; i++)
	{
		if (!isValidChar(input[i]))
			return false;
		if (isdigit(input[i]) && i + 1 < size && isdigit(input[i + 1]))
			return false;
	}
	return true;
}

float RPN::processOp(float a, char op, float b)
{
	switch (op)
	{
	case '+':
		return a + b;
	case '-':
		return a - b;
	case '*':
		return a * b;
	case '/':
		if (b == 0.0f)
			throw std::runtime_error(DIVISION_BY_0);
		return a / b;
	}
	return 0.0;
}

void	RPN::displayResult() const
{
	try
	{
		if (!DEBUG)
		{
			if (this->stack.empty())
				throw std::runtime_error(EMPTY_STACK);
			if (this->stack.size() != 1)
				throw std::runtime_error(BAD_INPUT);
		}
		if (DEBUG)
			std::cout << GREEN;
		else
			std::cout << OK;
		float result = this->stack.top();
		long longResult = static_cast<long>(result);
		if (result == longResult)
			std::cout << longResult << "\n\n" << RESET;
		else
			std::cout << std::fixed << this->stack.top() << "\n\n" << RESET;
	}
	catch(const std::exception& e)
	{
		std::cerr << ERROR << e.what() << "\n\n" RESET;
	}
}

bool RPN::processRPN(std::string input)
{
	size_t size = input.size();
	int a, b;
	try
	{
		for (size_t i = 0; i < size; i++)
		{
			if (input[i] == ' ')
				continue;
			if (isdigit(input[i]))
				this->stack.push(input[i] - '0');
			else if (isOp(input[i]))
			{
				if (this->stack.empty())
					throw std::runtime_error(EMPTY_STACK);
				a = this->stack.top();
				this->stack.pop();
				if (this->stack.empty())
					throw std::runtime_error(EMPTY_STACK);
				b = this->stack.top();
				this->stack.pop();
				this->stack.push(processOp(b, input[i], a));
				if (DEBUG)
				{
					std::cout << YELLOW "Processed: " << b << " " << input[i] << " " << a << "\n";
					std::cout << GREEN "Stack size: " << this->stack.size() << "; Top: ";
					this->displayResult();
					std::cout << RESET;
				}
			}
		}
	}
	catch (const std::exception &e)
	{
		std::cerr << ERROR << e.what() << "\n\n" RESET;
		return false;
	}
	return true;
}

RPN::RPN() {}

RPN::RPN(std::string input)
{
	std::cout << INFO "Processing '" << input << "'\n" RESET;
	if (!this->isValidRPN(input))
	{
		std::cout << ERROR "Bad input: '" << input << "'\n\n" RESET;
		return;
	}
	if (this->processRPN(input) && !DEBUG)
		this->displayResult();
}

RPN::RPN(RPN const &copy) { (void)copy; }

RPN &RPN::operator=(RPN const &copy)
{
	(void)copy;
	return *this;
}

RPN::~RPN() {}
