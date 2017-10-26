#include <iostream>

using namespace std;
/** Constructor and Destructor class that inherits from multiple
 * bases. The class that was declared first in the class definition is
 * initialised first */

/*************** Class Definitions Start ***************/
class base {
public:
	base() { std::cout << "  base: constructor\n"; }
	~base() { std::cout << "  base: destructor\n"; }
};

class base_more {
public:
	base_more() { std::cout << "  base_more: constructor\n"; }
	~base_more() { std::cout << "  base_more: destructor\n"; }
};
/********* New Derive Class ********/
class derived: public base_more, public base {
public:
	derived() { std::cout << "     derived: constructor\n"; }
	~derived() { std::cout << "     derived: destructor\n"; }
};

/*************** Class Definitions End ***************/
	
int main()
{
	/* Create a temporary scope to show objects going out of scope */
	{
		std::cout << "main: Entered the block\n";
		derived d;
		/* Objects dynamically allocated with new, are freed
		 * with delete, thus invoking the destructor */
		std::cout << "main: Exiting the block\n";
	}
	std::cout << "main: Exited the block\n";
	return 0;
}
