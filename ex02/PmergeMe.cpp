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
	int	first, second;
	std::vector<int>::iterator	itNext = container.begin() + 1;

	for (std::vector<int>::iterator it = container.begin(); it != container.end(); ++it)
	{
		//std::cout << "for loop" << *it << std::endl;
		//
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
	std::vector<int>::iterator			itMain = _mainVec.begin() + 1, itPrev = _mainVec.begin(), insertSmall;
	std::vector<int>				tmp = _mainVec;
	std::vector<std::pair<int, int> >::iterator	itPair;

	_mainVec.insert(_mainVec.begin(), findPairBySecondElement(_pairVec, _mainVec[0])->first);

	for (size_t i = 1; i < _jacobsthalSequence.size() && _mainVec.size() != 2; i++)
	{
		if (_jacobsthalSequence[i] > tmp.size())
			_jacobsthalSequence[i] = tmp.size() - 1;
		itMain = std::find(_mainVec.begin(), _mainVec.end(), tmp[_jacobsthalSequence[i]]);
		itPrev = std::find(_mainVec.begin(), _mainVec.end(), tmp[_jacobsthalSequence[i - 1]]);
		//std::cout << "prev tmp: " << tmp[_jacobsthalSequence[i - 1]] << std::endl;
		if (itPrev == _mainVec.end())
		{
			std::cout << tmp[_jacobsthalSequence[i - 1]] << std::endl;
			return ;
		}
		for (size_t nbElem = 0; _jacobsthalSequence[i] - nbElem != _jacobsthalSequence[i - 1]; nbElem++)
		{
			itPair = findPairBySecondElement(_pairVec, *itMain);
			insertSmall = std::lower_bound(_mainVec.begin(), itMain + 1, itPair->first);
			_mainVec.insert(insertSmall, itPair->first);
			displayT(_mainVec);
		}
	}
	itPair = findPairBySecondElement(_pairVec, -1);
	if (itPair != _pairVec.end())
		_mainVec.insert(std::lower_bound(_mainVec.begin(), _mainVec.end(), itPair->first), itPair->first);
}

void	PmergeMe::insertPairDeque(void)
{
	std::deque<int>::iterator			itMain = _mainDeque.begin() + 1, itPrev = _mainDeque.begin(), insertSmall;
	std::deque<int>					tmp = _mainDeque;
	std::deque<std::pair<int, int> >::iterator	itPair;

	_mainDeque.insert(_mainDeque.begin(), findPairBySecondElement(_pairDeque, _mainDeque[0])->first);

	for (size_t i = 1; i < _jacobsthalSequence.size() && _mainDeque.size() != 2; i++)
	{
		if (_jacobsthalSequence[i] > tmp.size())
			_jacobsthalSequence[i] = tmp.size() - 1;
		itMain = std::find(_mainDeque.begin(), _mainDeque.end(), tmp[_jacobsthalSequence[i]]);
		itPrev = std::find(_mainDeque.begin(), _mainDeque.end(), tmp[_jacobsthalSequence[i - 1]]);
		//std::cout << "prev tmp: " << tmp[_jacobsthalSequence[i - 1]] << std::endl;
		if (itPrev == _mainDeque.end())
		{
			std::cout << tmp[_jacobsthalSequence[i - 1]] << std::endl;
			return ;
		}
		for (size_t nbElem = 0; _jacobsthalSequence[i] - nbElem != _jacobsthalSequence[i - 1]; nbElem++)
		{
			itPair = findPairBySecondElement(_pairDeque, *itMain);
			insertSmall = std::lower_bound(_mainDeque.begin(), itMain + 1, itPair->first);
			_mainDeque.insert(insertSmall, itPair->first);
			displayT(_mainDeque);
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
		//std::cout << "for loop" << *it << std::endl;
		//
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
	time_t	start, end;
	int	i = 0;
	std::vector<int>	container;
	(void)argv;

	time(&start);
	while (argv[i])
	{
		if (std::find(container.begin(), container.end(), atoi(argv[i])) != container.end())
			throw PmergeMe::BadArguments();
		container.push_back(atoi(argv[i++]));
	}
	createPairVector(container);
	mergeInsertion(_mainVec);
	insertPairVec();
	time(&end);
	double	timePast = (end - start);
	std::cout << "Time taken by program is : " <<
		std::fixed << timePast << std::setprecision(5) << " sec " << std::endl;
}

void	PmergeMe::sortDeque(char **argv)
{
	int	i = 0;
	std::deque<int>	container;
	while (argv[i])
	{
		if (std::find(container.begin(), container.end(), atoi(argv[i])) != container.end())
			throw PmergeMe::BadArguments();
		container.push_back(atoi(argv[i++]));
	}
	displayT(container);
	createPairDeque(container);
	displayT(_mainDeque);
	mergeInsertion(_mainDeque);
	insertPairDeque();
	displayT(_mainDeque);

	
}

PmergeMe::PmergeMe(int argc, char **argv): _elemCount(argc){
	(void)argv;
	checkArgs(argv);
	if (argc == 1)
	{
		_mainVec.push_back(atoi(argv[0]));
		displayT(_mainVec);
		return ;
	}
	makeJacobSequence();
	//sortVector(argv);
	sortDeque(argv);
	//sortList(argv);
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

/*
void	PmergeMe::createPairList(std::list<int> container)
{
	int	first, second;
	std::list<int>::iterator	itNext = container.begin();

	itNext++;

	for (std::list<int>::iterator it = container.begin(); it != container.end(); ++it)
	{
		//std::cout << "for loop" << *it << std::endl;
		//
		if (itNext != container.end())
		{
			first = *it;
			second = *itNext;
			if (first > second)
				swap(first, second);
			_pairLst.push_back(std::make_pair(first, second));
			_mainLst.push_back(second);
			++it;
			itNext++;
			itNext++;
		}
		else
			_pairLst.push_back(std::make_pair(*it, -1));
	}	
}

void insertLst(std::list<int>& myList) {
    for (std::list<int>::iterator i = myList.begin(); i != myList.end(); ++i) {
        std::list<int>::iterator current = i;
        int key = *i;
        
        while (current != myList.begin() && *(--current) > key) {
            std::list<int>::iterator next = current;
            ++next;
            *next = *current;
        }
        
        std::list<int>::iterator next = current;
        ++next;
        *next = key;
    }
}

void	mergeLst(std::list<int> &container, std::list<int> &left, std::list<int> &right)
{
	std::list<int>::iterator	itL = left.begin(), itR = right.begin();

	container.clear();
	while (itL != left.end() && itR != right.end())
	{
		if (*itL <= *itR)
		{
			container.push_back(*itL);
			++itL;
		}
		else
		{
			container.push_back(*itR);
			++itR;
		}
	}
	while (itL != left.end())
	{
		container.push_back(*itL);
		++itL;
	}
	while (itR != right.end())
	{
		container.push_back(*itR);
		++itR;
	}
}

std::list<int>	splitList(std::list<int> container, size_t start, size_t end)
{
	std::list<int>			lst;
	std::list<int>::iterator	it;
	size_t				i = 0;
	
	while (it != container.end() && i != start)
	{
		++it;
		i++;
	}
	while (it != container.end() && i < end)
	{
		lst.push_back(*it);
		++it;
		i++;
	}
	return (lst);
}


void	mergeInsertionLst(std::list<int> &container)
{
	if (container.size() <= threshold)
	{
		insertLst(container);
		return ;
	}
	std::list<int>	left, right;
	left = splitList(container, 0, container.size() / 2);
	right = splitList(container, container.size() / 2, container.size());

	mergeInsertionLst(left);
	mergeInsertionLst(right);
	mergeLst(container, left, right);
}





void	PmergeMe::sortList(char **argv)
{
	time_t	start, end;
	int	i = 0;
	std::list<int>	container;

	time(&start);
	while (argv[i])
	{
		if (std::find(container.begin(), container.end(), atoi(argv[i])) != container.end())
			throw PmergeMe::BadArguments();
		container.push_back(atoi(argv[i++]));
	}
	displayT(container);

	std::cout << "coucou\n";
	createPairList(container);
	displayT(_mainLst);
	mergeInsertionLst(_mainLst);
	displayT(_mainLst);
	time(&end);
	double	timePast = (end - start);
	std::cout << "Time taken by program is : " <<
		std::fixed << timePast << std::setprecision(5) << " sec " << std::endl;
}
*/























