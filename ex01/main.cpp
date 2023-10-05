/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trerolle <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 20:29:55 by trerolle          #+#    #+#             */
/*   Updated: 2023/10/05 15:06:07 by trerolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

int main(int argc, char **argv)
{
	std::stack<int>	r;
	if (argc != 2)
	{
		std::cout << "Error: RPN take 1 argument (e.g. \"8 9 * 9 - 9 - 9 - 4 - 1 +\")\n";
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
