#include <iostream>

using namespace std;
/** Constructor and Destructor for dynamically objects, simple pointers and smart pointers.
 * - An object referenced through raw pointer is leaked
 * - An object referenced through a smart pointer (shared_ptr) is automatically destroyed only after all the smart pointers are destroyed.
 */

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
	std::shared_ptr<base> main_sptr;
	/* Create a temporary scope to show objects going out of scope */
	{
		cout << "main: Entered the block\n";
		base *b_ptr = new base(1);
		std::shared_ptr<base> b_sptr = std::make_shared<base>(2);
		main_sptr = b_sptr;
		cout << "main: Exiting the block\n";
	}
	/* Objects dynamically allocated with new, don't get
	 * out-of-scope. That b_ptr, does though, causing a memory
	 * leak in this case */
	/* Objects accessed through shared pointers, are automatically
	 * reference counted and deleted, when all the pointers to
	 * them are destroyed. */
	cout << "main: Exited the block\n";
	return 0;
}
