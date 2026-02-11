#pragma once
#ifndef __BITCOINEXCHANGE_HPP__
#define __BITCOINEXCHANGE_HPP__

#include "utils.hpp"
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
			bool	operator<(Date const&) const;
			Date	operator--();
			~Date();
			long	getYear() const;
			long	getMonth() const;
			long	getDay() const;
			void	print() const;
	};


	std::map<Date, float>	dates;

	bool					isValidDate(std::string);
	float					findValueOfDateOrClosestDate(std::string);

	
	BitcoinExchange(BitcoinExchange const& copy);
	BitcoinExchange & operator=(BitcoinExchange const& copy);

	bool					validateInput(std::string);
	void					addDateValue(std::string, float);
	void					displayFactor(std::string);
	std::string				stringConcat(std::string, std::string);

public:
	BitcoinExchange();
	~BitcoinExchange();

	void					readDatabase();
	void					readInputFile(std::string);

};

#endif // __BITCOINEXCHANGE_HPP__