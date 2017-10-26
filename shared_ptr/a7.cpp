#include <iostream>
#include <memory>

using namespace std;

/** Constructor to only allow use through smart-pointers. Uses named constructor idiom.
 */

/*************** Class Definitions Start ***************/
class base {
public:
	static std::unique_ptr<base> create(int num);

	~base() { cout << "  base: [" << m_num << "] destructor\n"; }

	int get_num() { return m_num; }

private:
	base(int a)
	{
		m_num = a;
		cout << "  base: [" << m_num << "] constructor\n";
	}

	int m_num;
};

std::unique_ptr<base> base::create(int num)
{
	/* So turns out make_unique is part of C++14, instead of
	 * C++11. Although, make_shared is part of C++11, so...
	 */
	//	return std::make_unique<base>(num);
	return std::unique_ptr<base>(new base(num));
}

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
	std::shared_ptr<base> main_sptr = base::create(9);

	print_ptr_member(main_sptr);

	/* Defining a static function to create the objects, and
	 * defining the constructor privately, ensures that the object
	 * cannot be allocated on the stack. Uncommenting the
	 * following will cause a compiler error.
	 */
	//	base(4);

	main_sptr = base::create(4);

	return 0;
}
