/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trerolle <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 19:43:49 by trerolle          #+#    #+#             */
/*   Updated: 2023/07/19 18:54:25 by trerolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include "BitcoinExchange.hpp" 


int	main(int argc, char **argv)
{
	BitcoinExchange	btc;


	if (argc != 2)
	{
		std::cout << "Btc must take 2 arguments" << std::endl;
		return (0);
	}
	btc.displayBTC(argv[1]);
/*	BitcoinExchange::t_date	d1 = {1, 2, 3};
	BitcoinExchange::t_date	d2 = {2, 2, 3};

	if (d1 == d2)
		std::cout << "working\n";
	try
	{
		d1 = "2023-05-02";
		for (int i  = 0; i < 365; i++)
		{
			d1++;
			std::cout << d1.year << " " << d1.month << " " << d1.day << std::endl;
		}
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}*/

	/*
	std::string					line;
	std::ifstream				input;
	std::map<std::string, double>	inputMap;
	char						*end;
	

	try
	{
		input.open("input.txt", std::ifstream::in);
		if (!input.is_open())
		{
			std::cout <<"1\n";
			throw std::exception();
		}
	}
	catch (std::exception &e)
	{
		std::cout << "Error: cannot open file" << std::endl;
		std::cout << e.what() << std::endl;
	}
	std::getline(input, line);
	while (std::getline(input, line))
	{
		try
		{
			inputMap[line.substr(0, 10)]  = strtod(line.substr(11, line.length()).c_str(), &end);
			if (inputMap.empty())
				throw std::exception();
		}
		catch (std::exception &e)
		{
			std::cout << "coucou"<<std::endl;
			std::cerr << e.what() << std::endl;
		}
		std::cout << inputMap.begin()->first << std::endl;
	}
	return (0);*/
}

