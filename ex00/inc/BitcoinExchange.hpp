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
			long	year;
			long	month;
			long	day;
		public:
			Date();
			Date(std::string);
			Date(int, int, int);
			Date(Date const&);
			Date & operator=(Date const&);
			~Date();
			long	getYear() const;
			long	getMonth() const;
			long	getDay() const;
	};

	std::map<Date, float>			dates;

	bool							isValidDate(std::string);
	float							findValueOfDateOrClosestDate(std::string);

	
public:
	BitcoinExchange();
	BitcoinExchange(BitcoinExchange const& copy);
	BitcoinExchange & operator=(BitcoinExchange const& copy);
	~BitcoinExchange();

	void							addDateValue(std::string, float);
	void							displayFactor(std::string, float);


};

#endif // __BITCOINEXCHANGE_HPP__