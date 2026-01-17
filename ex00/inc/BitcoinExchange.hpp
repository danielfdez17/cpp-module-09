#pragma once
#ifndef __BITCOINEXCHANGE_HPP__
#define __BITCOINEXCHANGE_HPP__

#include "utils.hpp"
#include <iostream>
#include <map>

class BitcoinExchange
{
private:
	class Date
	{
		private:
			int	year;
			int	month;
			int	day;
		public:
			Date();
			Date(std::string);
			Date(int, int, int);
			Date(Date const&);
			Date & operator=(Date const&);
			~Date();
			int	getYear() const;
			int	getMonth() const;
			int	getDay() const;
	};

	std::map<Date, float>			dates;

	bool							isValidDate(std::string);
	float							findValueOfDateOrClosestDate(std::string);

	
public:
	BitcoinExchange();
	BitcoinExchange(std::string, float);
	BitcoinExchange(BitcoinExchange const& copy);
	BitcoinExchange & operator=(BitcoinExchange const& copy);
	~BitcoinExchange();

};

#endif // __BITCOINEXCHANGE_HPP__