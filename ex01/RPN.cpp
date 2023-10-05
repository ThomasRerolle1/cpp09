/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trerolle <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:31:59 by trerolle          #+#    #+#             */
/*   Updated: 2023/10/05 15:09:19 by trerolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"
#include <cstring>
	
RPN::RPN()
{
}

RPN::RPN(RPN const &cpy)
{
	*this = cpy;
}
		
RPN::RPN(std::string rpn): _expression(rpn)
{
}

		
//destructors
		
RPN::~RPN()
{
}

		
//overload
		
const RPN &	RPN::operator=(RPN const &rhs)
{
	if (this == &rhs)
		return (*this);
	return (*this);
}

//getters

std::stack<int> &	RPN::getRPN() 
{
	return (this->_rpn);
}

		
//functions

int	RPN::calculate(int n1, int n2, char ope)
{
	if (ope == '+')
		return (n1 + n2);
	else if (ope == '*')
		return (n1 * n2);
	else if (ope == '-')
		return (n1 - n2);
	else 
	{
		if (n2 == 0)
			throw RPN::DivideByZero();
		return (n1 / n2);
	}
}

void	RPN::fillStack(char *str)
{
	int			n, nb_operand, nb_operators;
	std::string	ope = "+*/-";
	
	nb_operand = nb_operators = 0;
	for (size_t i  = 0; i < strlen(str); i++)
	{
		if (isdigit(str[i]))
		{
			nb_operand++;
			_rpn.push(str[i] - '0');
		}
		else if (ope.find(str[i], 0) != std::string::npos)
		{
			nb_operators++;
			if (_rpn.size() < 2)
				throw RPN::BadInput();
			n = _rpn.top();
			_rpn.pop();
			_rpn.top() = calculate(_rpn.top(), n, str[i]);
		}
		else if (str[i] == ' ')
			continue ;
		else
			throw RPN::BadInput();
	}
	if (nb_operators + 1 != nb_operand)
		throw RPN::BadInput();
}
