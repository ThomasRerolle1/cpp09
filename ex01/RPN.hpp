/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trerolle <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:18:56 by trerolle          #+#    #+#             */
/*   Updated: 2023/07/19 20:46:54 by trerolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <string>
#include <stdio.h>
#include <unistd.h>
#include <stack>


class	RPN
{
	public:
		//constructors
		RPN();
		RPN(RPN const &cpy);
		RPN(std::string rpn);

		//destructors
		~RPN();

		//overload
		const RPN &	operator=(RPN const &rhs);

		//functions
		
		std::stack<int> &	getRPN();
		std::string	&	getExpression();
		void			fillStack(char *str);
		int				calculate(int n1, int n2, char ope);

		//exceptions
		//
		class	BadInput: public std::exception
		{
			public:
				virtual const char * what() const throw()
				{
					return ("Error: Bad input");
				}
		};
		class	DivideByZero: public std::exception
		{
			public:
				virtual const char * what() const throw()
				{
					return ("Error: Trying to divide by 0");
				}
		};

	private:
		//constructor

		//attributes
		std::stack<int>	_rpn;
		std::string		_expression;
};

#endif

