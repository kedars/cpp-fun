#include <iostream>

using namespace std;
/** Constructor and Destructor for dynamically allocated object */

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
		base *b_ptr = new base(1);
		delete b_ptr;
		cout << "main: Exiting the block\n";
	}
	/* Objects dynamically allocated with new, don't get
	 * out-of-scope. They are explicitly freed with delete
	 */
	cout << "main: Exited the block\n";
	return 0;
}
