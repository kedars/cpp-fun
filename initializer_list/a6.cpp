#include <iostream>

using namespace std;
/** Initialization with initializer list
 */

/*************** Class Definitions Start ***************/
class base {
public:
	base(int num)
	{
		m_num = num;
		cout << "  base: [" << m_num << "] constructor\n";
	}

	base() { cout << "  base: default constructor\n"; }

	~base() { cout << "  base: [" << m_num << "] destructor\n"; }
private:
	int m_num;
};

/********* New Container Class ********/
class container {
public:
	container(int num);
	~container() { cout << "     container: [" << m_container_num << "] destructor\n"; }
private:
	int m_container_num;
	base m_base;
};

/* Simple Constructor */
container::container(int num):
	m_container_num{num},
	m_base{num}
{
	/* This constructor body is executed after the object has been
	 * initialized with contents from the initializer list */
	cout << "     container: [" << m_container_num << "] constructor body\n";
}

/*************** Class Definitions End ***************/
	
int main()
{
	/* Create a temporary scope to show objects going out of scope */
	{
		cout << "main: Entered the block\n";
		container d(1);
		/* Objects dynamically allocated with new, are freed
		 * with delete, thus invoking the destructor */
		cout << "main: Exiting the block\n";
	}
	cout << "main: Exited the block\n";
	return 0;
}
