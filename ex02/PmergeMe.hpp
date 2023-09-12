#ifndef PmergeMe_HPP
#define PmergeMe_HPP

#include <ctype.h>
#include <stdlib.h>
#include <iostream>
#include <vector>

class PmergeMe {
	public:
		//Constructors
		PmergeMe();
		PmergeMe(PmergeMe const &cpy);
		PmergeMe(char **argv, int argc);
		
		//Destructors
		~PmergeMe();


		//Operators Overloads
		PmergeMe const & operator=(PmergeMe const &rhs);
	
		//vector functions
		void	compareSmallAndMain();
		std::vector<unsigned int>	mergeSortVector(std::vector<unsigned int> v);
		std::vector<unsigned int>	mergeVector(std::vector<unsigned int> a, std::vector<unsigned int> b);
		void				insertSortVector(std::vector<unsigned int>& vec);
		std::vector<unsigned int>	splitVector(std::vector<unsigned int> v, int start, int end);
		/*void	insertSmallInMain();*/
		void	displayVector(std::vector<unsigned int> v);
		
		//exceptions
		class	BadInputException: public std::exception
		{
			public:
				virtual const char *what() const throw(){
					return ("Error: Bad input");
				}
		};
	private:
		std::vector<unsigned int>	smallV;
		std::vector<unsigned int>	mainV;
		unsigned int			oddNumber;
};

#endif // PmergeMe_HPP
