#include "PmergeMe.hpp"

PmergeMe::PmergeMe() {
    // Constructor implementation
}

PmergeMe::PmergeMe(PmergeMe const &cpy){
	*this = cpy;
}

PmergeMe::PmergeMe(char **argv, int argc)
{
	for (int i = 0; i < argc; i++)
	{
		int	j = 0;
		while (argv[i][j])
		{
			if (!isdigit(argv[i][j]))
				throw PmergeMe::BadInputException();
			j++;
		}
		if (argc % 2 && i == (argc - 1))
		{
			oddNumber = atoi(argv[i]);
			break ;
		}
		if (i >= argc / 2)
			mainV.push_back(atoi(argv[i]));
		else
			smallV.push_back(atoi(argv[i]));
	}

	displayVector(smallV);
	displayVector(mainV);
}

PmergeMe::~PmergeMe() {
    // Destructor implementation
}

PmergeMe const &	PmergeMe::operator=(PmergeMe const &rhs){
	if (this == &rhs)
		return (*this);
	//Operator implementation
	return (*this);
}

// Other member function implementations
//

void	PmergeMe::displayVector(std::vector<unsigned int> v)
{
	for (std::vector<unsigned>::const_iterator it = v.begin(); it != v.end(); ++it) 
	{
        	std::cout << *it << " ";
    	}
	std::cout << std::endl;
}

void	PmergeMe::compareSmallAndMain(void)
{
	unsigned int	tmp;
	for (size_t i  = 0; i < smallV.size(); i++)
	{
		if (smallV[i] > mainV[i])
		{
			tmp = smallV[i];
			smallV[i] = mainV[i];
			mainV[i] = tmp;
		}
	}

	mainV = mergeSortVector(mainV);
	std::cout << "after merge sort :\t";
	displayVector(mainV);
}

std::vector<unsigned int>	PmergeMe::splitVector(std::vector<unsigned int> v, int start, int end)
{
	std::vector<unsigned int>::iterator	first = v.begin() + start;
	std::vector<unsigned int>::iterator	last = v.begin() + end;
	
	std::vector<unsigned int>		subVector(first, last);
	return (subVector);
}

void PmergeMe::insertSortVector(std::vector<unsigned int>& vec) 
{
    int n = vec.size();
    
    for (int i = 1; i < n; ++i) 
    {
        unsigned int key = vec[i];
        int j = i - 1;

        while (j >= 0 && vec[j] > key) 
	{
            vec[j + 1] = vec[j];
            j--;
        }

        vec[j + 1] = key;
    }
}

std::vector<unsigned int>	PmergeMe::mergeVector(std::vector<unsigned int> a, std::vector<unsigned int> b)
{
	std::vector<unsigned int>	c;
	size_t				i, j;

	i = 0;
	j = 0;
	
	while (i < a.size() && j < b.size())
	{
		if (a[i] < b[j])
		{
			c.push_back(a[i]);
			i++;
		}
		else
		{
			c.push_back(b[j]);
			j++;
		}
	}
	while (i < a.size())
	{
		c.push_back(a[i]);
		i++;
	}
	while (j < b.size())
	{
		c.push_back(b[j]);
		j++;
	}
	return c;
}

std::vector<unsigned int>	PmergeMe::mergeSortVector(std::vector<unsigned int> v)
{
	if (v.size() <= 2)
	{
		insertSortVector(v);
		return v;
	}
	std::vector<unsigned int> arrayOne = splitVector(v, 0, v.size() / 2);
	std::vector<unsigned int> arrayTwo = splitVector(v, v.size() / 2, v.size());

	arrayOne = mergeSortVector(arrayOne);
	arrayTwo = mergeSortVector(arrayTwo);
	
	return mergeVector(arrayOne, arrayTwo);
}
