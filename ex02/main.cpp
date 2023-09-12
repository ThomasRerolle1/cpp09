#include "PmergeMe.hpp"

int	main(int argc, char **argv)
{
	if (argc < 2)
	{
		std::cout << "Too few arguments" << std::endl;
		return (0);
	}
try
	{
		PmergeMe	sort(argv + 1, argc - 1);
		sort.compareSmallAndMain();

	}
	catch (std::exception &e)
	{
		std::cout << e.what() <<std::endl;
	}
}
