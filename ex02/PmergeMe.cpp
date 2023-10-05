#include "PmergeMe.hpp"

PmergeMe::PmergeMe() {
    // Constructor implementation
}

PmergeMe::PmergeMe(PmergeMe const &cpy){
	*this = cpy;
}
	
void	PmergeMe::checkArgs(char **argv)
{
	int	i = 0;

	while (argv[i])
	{
		int j = 0;
		while (argv[i][j])
		{
			if (!std::isdigit(argv[i][j]))
				throw PmergeMe::BadArguments();
			j++;
		}
		if (atol(argv[i]) > INT_MAX)
			throw PmergeMe::BadArguments();
		i++;
	}
	i = 0;
}

void	PmergeMe::makeJacobSequence(void){

	_jacobsthalSequence.push_back(0);
	_jacobsthalSequence.push_back(1);
	_jacobsthalSequence.push_back(3);
	for (int i = 1; _jacobsthalSequence[i + 1] < _elemCount / 2 + 1; i++)
		_jacobsthalSequence.push_back(2 * _jacobsthalSequence[i] + _jacobsthalSequence[i + 1]);
}

void	PmergeMe::createPairVector(std::vector<int> container)
{
	int							first, second;
	std::vector<int>::iterator	itNext = container.begin() + 1;

	for (std::vector<int>::iterator it = container.begin(); it != container.end(); ++it)
	{
		if (itNext != container.end())
		{
			first = *it;
			second = *itNext;
			if (first > second)
				swap(first, second);
			_pairVec.push_back(std::make_pair(first, second));
			_mainVec.push_back(second);
			++it;
			itNext += 2;
		}
		else
			_pairVec.push_back(std::make_pair(*it, -1));
	}	
}


void	PmergeMe::insertPairVec(void)
{
	std::vector<int>::iterator					itMain = _mainVec.begin() + 1, itPrev = _mainVec.begin(), insertSmall;
	std::vector<int>							tmp = _mainVec;
	std::vector<std::pair<int, int> >::iterator	itPair;

	_mainVec.insert(_mainVec.begin(), findPairBySecondElement(_pairVec, _mainVec[0])->first);

	for (size_t i = 1; i < _jacobsthalSequence.size() && _mainVec.size() != 2; i++)
	{
		if (_jacobsthalSequence[i] > tmp.size())
			_jacobsthalSequence[i] = tmp.size() - 1;
		itMain = std::find(_mainVec.begin(), _mainVec.end(), tmp[_jacobsthalSequence[i]]);
		itPrev = std::find(_mainVec.begin(), _mainVec.end(), tmp[_jacobsthalSequence[i - 1]]);
		if (itPrev == _mainVec.end())
			return ;
		for (size_t nbElem = 0; _jacobsthalSequence[i] - nbElem != _jacobsthalSequence[i - 1]; nbElem++)
		{
			itMain = std::find(_mainVec.begin(), _mainVec.end(), tmp[_jacobsthalSequence[i] - nbElem]);
			itPair = findPairBySecondElement(_pairVec, *itMain);
			insertSmall = std::lower_bound(_mainVec.begin(), itMain + 1, itPair->first);
			_mainVec.insert(insertSmall, itPair->first);
		}
	}
	itPair = findPairBySecondElement(_pairVec, -1);
	if (itPair != _pairVec.end())
		_mainVec.insert(std::lower_bound(_mainVec.begin(), _mainVec.end(), itPair->first), itPair->first);
}

void	PmergeMe::insertPairDeque(void)
{
	std::deque<int>::iterator					itMain = _mainDeque.begin() + 1, itPrev = _mainDeque.begin(), insertSmall;
	std::deque<int>								tmp = _mainDeque;
	std::deque<std::pair<int, int> >::iterator	itPair;

	_mainDeque.insert(_mainDeque.begin(), findPairBySecondElement(_pairDeque, _mainDeque[0])->first);
	for (size_t i = 1; i < _jacobsthalSequence.size() && _mainDeque.size() != 2; i++)
	{
		if (_jacobsthalSequence[i] > tmp.size())
			_jacobsthalSequence[i] = tmp.size() - 1;
		itMain = std::find(_mainDeque.begin(), _mainDeque.end(), tmp[_jacobsthalSequence[i]]);
		itPrev = std::find(_mainDeque.begin(), _mainDeque.end(), tmp[_jacobsthalSequence[i - 1]]);
		if (itPrev == _mainDeque.end())
			return ;
		for (size_t nbElem = 0; _jacobsthalSequence[i] - nbElem != _jacobsthalSequence[i - 1]; nbElem++)
		{
			itMain = std::find(_mainDeque.begin(), _mainDeque.end(), tmp[_jacobsthalSequence[i] - nbElem]);
			itPair = findPairBySecondElement(_pairDeque, *itMain);
			insertSmall = std::lower_bound(_mainDeque.begin(), itMain + 1, itPair->first);
			_mainDeque.insert(insertSmall, itPair->first);
		}
	}
	itPair = findPairBySecondElement(_pairDeque, -1);
	if (itPair != _pairDeque.end())
		_mainDeque.insert(std::lower_bound(_mainDeque.begin(), _mainDeque.end(), itPair->first), itPair->first);
}

void	PmergeMe::createPairDeque(std::deque<int> container)
{
	int	first, second;
	std::deque<int>::iterator	itNext = container.begin() + 1;

	for (std::deque<int>::iterator it = container.begin(); it != container.end(); ++it)
	{
		if (itNext != container.end())
		{
			first = *it;
			second = *itNext;
			if (first > second)
				swap(first, second);
			_pairDeque.push_back(std::make_pair(first, second));
			_mainDeque.push_back(second);
			++it;
			itNext += 2;
		}
		else
			_pairDeque.push_back(std::make_pair(*it, -1));
	}	
}



void	PmergeMe::sortVector(char **argv)
{
	std::clock_t	timePast;
	int	i = 0;
	std::vector<int>	container;

	timePast = clock();
	while (argv[i])
	{
		if (std::find(container.begin(), container.end(), atoi(argv[i])) != container.end())
			throw PmergeMe::BadArguments();
		container.push_back(atoi(argv[i++]));
	}
	if (_elemCount > 1)
	{
		createPairVector(container);
		mergeInsertion(_mainVec);
		insertPairVec();
	}
	else
		_mainVec = container;
	std::cout << "Vector:\t";
	displayT(_mainVec);
	timePast = clock() - timePast;
	std::cout << "Time to process a range of " << _elemCount << " elements with std::vector: " << (timePast / (CLOCKS_PER_SEC / 1000000)) << " usec " << std::endl;
}

void	PmergeMe::sortDeque(char **argv)
{
	std::clock_t	timePast;
	int	i = 0;
	std::deque<int>	container;
	
	timePast = clock();
	while (argv[i])
	{
		if (std::find(container.begin(), container.end(), atoi(argv[i])) != container.end())
			throw PmergeMe::BadArguments();
		container.push_back(atoi(argv[i++]));
	}
	std::cout << "\nBefore:\t";
	displayT(container);
	if (_elemCount > 1)
	{
		createPairDeque(container);
		mergeInsertion(_mainDeque);
		insertPairDeque();
	}
	else
		_mainDeque = container;
	std::cout << "\nDeque:\t";
	displayT(_mainDeque);
	timePast = clock() - timePast;
	std::cout << "Time to process a range of " << _elemCount << " elements with std::deque: " << (timePast / (CLOCKS_PER_SEC / 1000000)) << " usec " << std::endl;

	
}

PmergeMe::PmergeMe(int argc, char **argv): _elemCount(argc){
	checkArgs(argv);
	makeJacobSequence();
	sortDeque(argv);
	if (std::is_sorted(_mainDeque.begin(), _mainDeque.end()))
			std::cout << "DEQUE IS SORTED" << std::endl;
	std::cout << std::endl;
	sortVector(argv);
	if (std::is_sorted(_mainVec.begin(), _mainVec.end()))
			std::cout << "VECTOR IS SORTED" << std::endl;
	std::cout << std::endl;
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
