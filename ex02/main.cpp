#include "PmergeMe.hpp"

int	main(int argc, char **argv)
{
	if (argc < 2)
	{
		std::cout << "Too few arguments\n";
		return (0);
	}
	try
	{
		PmergeMe	test(argc - 1, argv + 1);
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}

	return (0);
}
