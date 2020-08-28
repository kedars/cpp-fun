#include <iostream>

using namespace std;

/** 
 * Overriding members with virtual keyword 'protected'
 */

/*************** Class Definitions Start ***************/
class base {
public:
	base() {  }
	~base() { }
protected:
        void test(void) { cout <<  "  base: test\n"; }
};

/********* New Derive Class ********/
class derived: public base {
public:
	derived() { }
	~derived() { }
        void test(void) { cout <<  "  derived: test\n"; }
};

class basevirtual {
public:
protected:
        virtual void test(void) { cout <<  "  base: test\n"; }
};

/********* New Derive Class ********/
class derivedvirtual: public basevirtual {
public:

        void test(void) { cout <<  "  derived: test\n"; }
};

/*************** Class Definitions End ***************/
	
int main()
{
        derived d;
        cout << "Calling derived.test() \n";
        d.test();

        derived e;
        base *b = &e;
        cout << "Calling base-ptr.test() \n";
        b->test();

        /* The basevirtual class defines the test() function as
         * 'virtual', hence when called with base-ptr c->test(), the derived
         * class's test() is called.
         *
         * as opposed to the behaviour above, where b->test() invokes
         * the base class' test().
         */
        derivedvirtual f;
        basevirtual *c = &f;
        cout << "Calling base-ptr-virtual.test()\n";
        c->test();
        return 0;
}
