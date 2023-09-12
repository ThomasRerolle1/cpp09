/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trerolle <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 20:29:55 by trerolle          #+#    #+#             */
/*   Updated: 2023/07/19 21:19:41 by trerolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

int main(int argc, char **argv)
{
	std::stack<int>	r;
	if (argc != 2)
	{
		std::cout << "Wrong number of arguments\n";
		return (0);
	}
	RPN	rpn;

	try
	{
		rpn.fillStack(argv[1]);
		r = rpn.getRPN();
		std::cout << r.top() << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
	
}

