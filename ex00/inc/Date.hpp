#pragma once
#ifndef __DATE_HPP
#define __DATE_HPP

#include <iostream>
#include <string>

class Date
{
	private:
		long	year;
		long	month;
		long	day;
	public:
		Date();
		Date(std::string);
		Date(int, int, int);
		Date(Date const&);
		Date & operator=(Date const&);
		bool	operator<(Date const&) const;
		bool	operator>(Date const&) const;
		bool	operator<=(Date const&) const;
		bool	operator>=(Date const&) const;
		bool	operator==(Date const&) const;
		bool	operator!=(Date const&) const;
		Date	&operator--();
		~Date();
		long	getYear() const;
		long	getMonth() const;
		long	getDay() const;
		void	print() const;
};

std::ostream& operator<<(std::ostream& os, const Date& date);

#endif // __DATE_HPP
