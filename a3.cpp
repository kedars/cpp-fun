#include <iostream>

using namespace std;
/** Constructor and Destructor sequence for multiple objects within the scope */

/*************** Class Definitions Start ***************/
class base {
public:
	base(int num)
	{
		m_num = num;
		cout << "  base: [" << m_num << "] constructor\n";
	}

	~base() { cout << "  base: [" << m_num << "] destructor\n"; }
private:
	int m_num;
};

/*************** Class Definitions End ***************/
	
int main()
{
	/* Create a temporary scope to show objects going out of scope */
	{
		cout << "main: Entered the block\n";
		base b{1};
		base c{2};
		/* Destruction always happens exactly in the reverse
		 * order of construction */
		cout << "main: Exiting the block\n";
	}
	cout << "main: Exited the block\n";
	return 0;
}
