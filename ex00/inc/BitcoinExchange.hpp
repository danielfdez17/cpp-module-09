#pragma once
#ifndef __BITCOINEXCHANGE_HPP__
#define __BITCOINEXCHANGE_HPP__

#include "utils.hpp"
#include "Date.hpp"
#include <map>

class BitcoinExchange
{
private:

	std::map<Date, float>	dates;
	bool					firstDate;
	Date					minimumDate;

	bool					isValidDate(std::string);
	float					findClosestValueForDate(std::string);
	void					printFloatValue(float value);

	
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