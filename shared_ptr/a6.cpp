#include <iostream>

using namespace std;

/** Interesting concepts about shared_ptr
 */

/*************** Class Definitions Start ***************/
class base {
public:
	base(int a)
	{
		m_num = a;
		cout << "  base: [" << m_num << "] constructor\n";
	}

	~base() { cout << "  base: [" << m_num << "] destructor\n"; }
	int get_num() { return m_num; }
private:
	int m_num;
};

/*************** Class Definitions End ***************/
void print_ptr_member(std::shared_ptr<base>bptr)
{
	if (bptr) {
		/* The check for null-pointer checks whether a pointer
		 * is assigned to it or not */
		cout << "main: get_num " << bptr->get_num() << "\n";

		/* Operations on the shared_ptr (like the dereference
		 * -> operator above), act on the target pointed to by
		 * the shared pointer. So the shared_ptr can be used
		 * on all operations as if it is the actual pointer to
		 * that object */
	}
}

int main()
{
	std::shared_ptr<base> main_sptr;

	/* By default, a shared_ptr target is initialized to nullptr,
	 * so this will print nothing */
	print_ptr_member(main_sptr);

	main_sptr = std::make_shared<base>(4);

	print_ptr_member(main_sptr);

	main_sptr = std::make_shared<base>(9);
	/* Overwriting the contents will destroy the object that was pointed earlier (4). */

	/* Notice the order, where first the new object (9) is
	 * created, and then as the object is getting assigned, the
	 * previous object (4) gets destroyed */

	print_ptr_member(main_sptr);

	return 0;
}
