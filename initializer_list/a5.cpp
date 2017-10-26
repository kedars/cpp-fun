#include <iostream>

using namespace std;
/** Initialization without initializer list
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
	m_container_num{num}
{
	m_base = base{num};
	/* What happens when this is moved out of the initializer list
	 * is that, the class is first constructed. The member m_base
	 * is constructed with the default constructor. Then, a
	 * temporary object is created because of 'base{name}' call,
	 * and then the already constructed m_base member is
	 * overwritten with this temporary object. Finally, the
	 * temporary object is destroyed, and then the execution
	 * proceeds further.*/
	cout << "     container: [" << m_container_num << "] constructor\n";
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
