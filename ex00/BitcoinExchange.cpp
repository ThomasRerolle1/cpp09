/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trerolle <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 19:50:34 by trerolle          #+#    #+#             */
/*   Updated: 2023/10/05 14:57:19 by trerolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <unistd.h>
#include <limits.h>
	//constructors
BitcoinExchange::BitcoinExchange()
{
	try
	{
		_data = fromTextToMap("data.csv");
	}
	catch (BitcoinExchange::FileNotFoundException &e)
	{
		std::cerr << e.what() << std::endl;
	}
}


		
BitcoinExchange::BitcoinExchange(BitcoinExchange const &rhs)
{
	*this = rhs;
}
		

		//Destructor
		
BitcoinExchange::~BitcoinExchange()
{
}

		//overload operators
		
BitcoinExchange const &	BitcoinExchange::operator=(BitcoinExchange const &rhs)
{
	if (this == &rhs)
		return (*this);
	_data = rhs.getData();
	return (*this);
}


		//functions

void	BitcoinExchange::displayBTC(std::string file) const
{
	std::ifstream	ifs;
	std::string	line;

	if (_data.empty())
		return ;
	ifs.open(file.c_str(), std::ifstream::in);
	if (!ifs.is_open())
		throw BitcoinExchange::FileNotFoundException();
	std::getline(ifs, line);
	while (std::getline(ifs, line))
	{
		try
		{
			if (line.length() < 11)
				throw BitcoinExchange::BadDateException();
			bitcoinConvertor(line.substr(0, 10), strtod(line.substr(12, line.length()).c_str(), 0));
		}
		catch (BitcoinExchange::BadDateException &e)
		{
			std::cerr << e.what() << " => " << line.substr(0, 10) << std::endl;
		}
		catch (std::exception &e)
		{
			std::cerr << e.what() << std::endl;
		}
	}
	ifs.close();
}

void	BitcoinExchange::bitcoinConvertor(std::string date, double value) const
{
	std::map<std::string, double>::const_iterator	it;

	if (_data.empty())
		return ;	
	it = _data.find(date);
	if (it == _data.end())
	{
		it = _data.lower_bound(date);
		if (it != _data.begin())
			--it;
	}
	if (it == _data.end())
		throw BitcoinExchange::BadDateException();
	if (value < 0)
		throw BitcoinExchange::NegativevalueException();
	if (value > static_cast<double>(INT_MAX))
		throw BitcoinExchange::TooLargeNumberException();
	std::cout << date << " => " << value << " = " << value * it->second << std::endl;
}

		
std::map<std::string, double>	BitcoinExchange::fromTextToMap(std::string fileName)
{
	std::ifstream					ifs;
	std::map<std::string, double>	dataMap;
	std::string						line;
	char							*end;

	ifs.open(fileName.c_str(), std::ifstream::in);	
	if (!ifs.is_open())
		throw (BitcoinExchange::FileNotFoundException());
	std::getline(ifs, line);
	while (std::getline(ifs, line))
	{
		try
		{
			dataMap[line.substr(0, 10)] = strtod(line.substr(11, line.length()).c_str(), &end);
		}
		catch (std::exception &e)
		{
			std::cerr << e.what() << std::endl;
		}
	}
	ifs.close();
	return (dataMap);
}

//getters


std::map<std::string, double> const &	BitcoinExchange::getData() const
{
	return (_data);
}




