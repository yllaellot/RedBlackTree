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

	try{

    while (std::cin >> request)
	{
		switch(request)
		{
			
			case KEY: 
				if (!(std::cin >> key)) throw "Error reading from input stream\n";

				rb_tree.insert(key);
				break;

			case QUERY:
				if (!(std::cin >> key1 >> key2)) throw "Error reading from input stream\n";

			    std::cout << rb_tree.range_queries_2(key1, key2) << "\n";
				break;

			default :
			    std::cerr << "Error input" << "\n";
                return EXIT_FAILURE;
		}

    }
	}
	catch (const char* error)
	{
		std::cerr<< error << "\n";
	}

    return EXIT_SUCCESS;
}
