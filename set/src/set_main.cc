#include <iostream>
#include <set>

enum Requests
{
	KEY = 'k',
	QUERY = 'q'
};

template <typename C, typename T>
long range_query(const C &set, const T& first, const T& second) 
{
    if (first > second) 
        return 0;

    auto start = set.lower_bound(first);
    auto fin   = set.upper_bound(second);
    return std::distance(start, fin);
}

int main() 
{
	std::set<int> rb_tree;

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

						 std::cout << range_query(rb_tree, key1, key2) << std::endl;

			default :
			          std::cerr << "Error input" << std::endl;
                      return EXIT_FAILURE;
		}

    }

    return EXIT_SUCCESS;
}
