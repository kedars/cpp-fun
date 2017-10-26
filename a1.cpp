#include <iostream>

using namespace std;
/** Constructor and Destructor sequence */

/*************** Class Definitions Start ***************/
class base {
public:
	base() { cout << "  base: constructor\n"; }
	~base() { cout << "  base: destructor\n"; }
};

/*************** Class Definitions End ***************/
	
int main()
{
	{
		cout << "main: Entered the block\n";
		base b;
		cout << "main: Exiting the block\n";
	}
	cout << "main: Exited the block\n";
	return 0;
}
