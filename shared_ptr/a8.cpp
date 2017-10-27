#include <iostream>
#include <vector>

using namespace std;
/** shared_ptr destruction through destruction of contained object
 *
 * The allocated shared_ptr are tied into a container object. When the
 * container object is destroyed, its members are destroyed,
 * automatically destroying the shared_ptr references
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

class container {
public:
	container()
	{
		cout << "     container: constructor\n";
	}
	~container()
	{
		cout << "     container: destructor\n";
	}

	void add_to_list(std::shared_ptr<base> entry)
	{
		the_list.push_back(entry);
	}
private:
	std::vector<std::shared_ptr<base> > the_list;
};
/*************** Class Definitions End ***************/

#define ELEMENTS_NO 10	
int main()
{
	container c;
	/* Create a temporary scope to show objects going out of scope */
	{
		cout << "main: Entered the block\n";
		std::shared_ptr<base> array[ELEMENTS_NO];
		for (int i = 0; i < ELEMENTS_NO; i++) {
			array[i] = std::make_shared<base>(i);
		}
		cout << "main: Exiting the block\n";
	}
	cout << "main: Exited the block\n";
	cout << "---------";
	{
		cout << "main: Entered the block\n";
		std::shared_ptr<base> array[ELEMENTS_NO];
		for (int i = 0; i < ELEMENTS_NO; i++) {
			array[i] = std::make_shared<base>(i);
		}
		for (int i = 0; i < ELEMENTS_NO; i++) {
			c.add_to_list(array[i]);
		}
		cout << "main: Exiting the block\n";
	}
	/* Because the shared_ptr are also placed in the array, they
	   aren't destructed on exiting the block. But when the main()
	   function block is exited, the container C is destroyed,
	   hence it std::vector gets destroyed, and hence all the
	   shared ptrs within that vector decrement their reference
	   counts. And since those were the only references left, the
	   base poitners are destroyed.
	 */
	cout << "main: Exited the block\n";

	return 0;
}
