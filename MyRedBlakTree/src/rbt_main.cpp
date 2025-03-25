#include "../include/RedBlackTree.h"

enum Requests
{
	KEY = 'k',
	QUERY = 'q'
};

int main() 
{
	RedBlackTree<int> rb_tree;

    char request;

    int key;
    int key1, key2;

    while (std::cin >> request)
	{
		switch(request)
		{
			case KEY   : 
					     if (!(std::cin >> key))
					     {
					          std::cerr << "Error input" << std::endl;
						      return EXIT_FAILURE;
					     }

						 rb_tree.insert(key);

			case QUERY :
					     if (!(std::cin >> key1 >> key2))
					     {
					         std::cerr << "Error input" << std::endl;
						     return EXIT_FAILURE;
					     }

						 std::cout << rb_tree.range_queries(key1, key2) << std::endl;

			default :
			          std::cerr << "Error input" << std::endl;
                      return EXIT_FAILURE;
		}

    }

    return EXIT_SUCCESS;
}
