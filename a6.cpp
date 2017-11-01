#include <iostream>

using namespace std;
/** Constructor and Destructor for objects in a loop block */

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
	cout << "main: Entering the block\n";
	for (int i = 0; i < 10; i++) {
		base b(2);
		cout << "     loop interation: " << i << "\n";
	}
	cout << "main: Exited the block\n";
	return 0;
}
