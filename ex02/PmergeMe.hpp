#ifndef PmergeMe_HPP
#define PmergeMe_HPP
#define threshold 10

#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>
#include <list>
#include <deque>
#include <cmath>
#include <cctype>
#include <cctype>
#include <ctime>
#include <climits>

class PmergeMe {
	public:
		//Constructors
		PmergeMe();
		PmergeMe(int argc, char **argv);
		PmergeMe(PmergeMe const &cpy);
		
		//Destructors
		~PmergeMe();

		//Operators Overloads
		PmergeMe const & operator=(PmergeMe const &rhs);
		//other functions

		template <typename T>
		void	swap(T &a, T &b)
		{
			T	temp = a;
			a = b;
			b = temp;
		}

		template <typename T>
		typename T::iterator findPairBySecondElement(T& container, int target) 
		{
    			for (typename T::iterator it = container.begin(); it != container.end(); ++it) 
			{
        			if (it->second == target) 
            				return it; // Return iterator to the matching pair
    			}
			return container.end(); // Return end() iterator if not found
		}

		template <typename T>
		void	displayT(T &container)
		{
			int	i = 0;
			for (typename T::iterator it = container.begin(); it != container.end(); ++it)
			{
				if  (i == 4)
				{
					std::cout << " [...]";
					break ;
				}
				std::cout << " " << *it;
				i++;
			}
			std:: cout << "\n";
		}	

		template <typename T>
		T	split(T &container, size_t start, size_t end)
		{
			T	res;
			for (; start < end; start++)
				res.push_back(container[start]);
			return res;
		}

		template <typename T>
		void	insert(T &container)
		{
			for (size_t i = 0; i < container.size(); i++)
			{
				int	j = i - 1, key = container[i];
				while (j >= 0 && container[j] > key)
				{
					container[j + 1] = container[j];
					j--;
				}
				container[j + 1] = key;
			}
		}

		template <typename T>
		void	merge(T &container, T &left, T &right)
		{
			size_t	i = 0, j = 0;

			container.clear();
			while (i < left.size() && j < right.size())
			{
				if (left[i] <= right[j])
					container.push_back(left[i++]);
				else
					container.push_back(right[j++]);
			}
			while (i < left.size())
				container.push_back(left[i++]);
			while (j < right.size())
				container.push_back(right[j++]);
		}


		template <typename T>
		void	mergeInsertion(T &container)
		{
			if (container.size() <= threshold)
			{
				insert(container);
				return ;
			}
			T	left;
			T	right;
			left = split(container, 0, container.size() / 2);
			right = split(container, container.size() / 2, container.size());
			mergeInsertion(left);
			mergeInsertion(right);
			merge(container, left, right);
		}
		
				
		void	checkArgs(char **argv);
		void	makeJacobSequence(void);
		void	sortVector(char **argv);
		void	createPairVector(std::vector<int> container);
		void	createPairDeque(std::deque<int> container);
		void	insertPairVec(void);
		void	insertPairDeque(void);
		void	createPairList(std::list<int> container);
		void	sortDeque(char **argv);
		//exceptions

		class BadArguments: public std::exception
		{
			public:
				virtual const char *what() const throw(){
					return ("Bad input: must contain only positive integers and no duplicate values");
				}
		};
	private:
		size_t								_elemCount;
		std::vector<int>					_mainVec;
		std::vector<std::pair<int, int> >	_pairVec;
		std::deque<int>						_mainDeque;
		std::deque<std::pair<int, int> >	_pairDeque;
		std::vector<size_t>					_jacobsthalSequence;

};

#endif // PmergeMe_HPP
