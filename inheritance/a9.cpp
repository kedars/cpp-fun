#include <iostream>

using namespace std;

/** Derive from 2 base classes with same function */

/*************** Class Definitions Start ***************/
class base {
public:
        int a;
	base() { cout << "  base: constructor\n"; }
	~base() { cout << "  base: destructor\n"; }
        virtual void test(int value) { cout << "base:  value is " << value << "and a is " << a << "\n"; }
};

class baseNew {
public:
        int a;
	baseNew() { cout << "  baseNew: constructor\n"; }
	~baseNew() { cout << "  baseNew: destructor\n"; }
        virtual void test(int value) { cout << "baseNew:  value is " << value << "and a is " << a << "\n"; }
};


/********* New Derive Class ********/
class derived: public base,
public baseNew
{
public:
	derived() { cout << "     derived: constructor\n"; }
	~derived() { cout << "     derived: destructor\n"; }
        void test(int value)
        {
                cout << "derived: value is" << value << "and a is " << ::base::a << "\n";
                if (value < 10) { base::test(value); }
                else { baseNew::test(value); }
        }
};

/*************** Class Definitions End ***************/
	
int main()
{
        derived d;
        d.test(1);
        d.test(10);
	return 0;
}
