#include <iostream>

using namespace std;
/** Constructor and Destructor sequence */

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
	{
		cout << "main: Entered the block\n";
		base b{1};
		cout << "main: Exiting the block\n";
	}
	cout << "main: Exited the block\n";
	return 0;
}
