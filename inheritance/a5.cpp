#include <iostream>

using namespace std;

/** Constructor and Destructor for derived classes. The base class is
 * first constructed followed by the derived class
 * (bottom-up). Destruction is in the reverse order */

/*************** Class Definitions Start ***************/
class base {
public:
	base() { cout << "  base: constructor\n"; }
	~base() { cout << "  base: destructor\n"; }
};

/********* New Derive Class ********/
class derived: public base {
public:
	derived() { cout << "     derived: constructor\n"; }
	~derived() { cout << "     derived: destructor\n"; }
};

/*************** Class Definitions End ***************/
	
int main()
{
	/* Create a temporary scope to show objects going out of scope */
	{
		cout << "main: Entered the block\n";
		derived d;
		/* Objects dynamically allocated with new, are freed
		 * with delete, thus invoking the destructor */
		cout << "main: Exiting the block\n";
	}
	cout << "main: Exited the block\n";
	return 0;
}
