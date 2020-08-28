#include <stdio.h>
#include "MySharedPtr.h"

#define my_assert(string, condition) \
    do { \
       if (!(condition)) { \
           printf("[%s:%d] Error: %s\n", __FILE__, __LINE__, string);    \
       } \
    } while(0)

#define my_assert_str(string, expected, actual) \
    do { \
        if (strcmp(expected, actual) != 0) {    \
           printf("[%s:%d] Error: %s Expected:%s: Received:%s:\n", __FILE__, __LINE__, string, expected, actual); \
       } \
    } while(0)

enum state {
    UNINIT = 0,
    CONSTRUCTED,
    DESTRUCTED,
};

struct test_data {
    enum state mState;
    const char *mStr;
    test_data(const char *str) : mStr(str) {}
};

class TestObject {
public:
    struct test_data *mPtr;
    TestObject(struct test_data *ptr) : mPtr(ptr)
    {
        mPtr->mState = CONSTRUCTED;
    }
    ~TestObject()
    {
        mPtr->mState = DESTRUCTED;
    }
};

static const char *basic_str = "Basic Str";
static const char *overwritten_str = "Overwritte Str";
void test_basics()
{
    struct test_data basic_data(basic_str);
    {
        MySharedPtr<TestObject> ptr(new TestObject(&basic_data));
        /* Test that pointer deference points to the correct object */
        my_assert_str("Pointer dereference", ptr->mPtr->mStr, basic_str);
        /* Test default reference count is 1 */
        my_assert("Default ref 1", ptr.getCnt() == 1);
        my_assert("Object Constructed", basic_data.mState == CONSTRUCTED);
    }
    /* Test that the 'ptr' was destructed */
    my_assert("Object Destructed", basic_data.mState == DESTRUCTED);
}

void test_assignment()
{
    struct test_data basic_data(basic_str);
    {
        MySharedPtr<TestObject> ptr1(new TestObject(&basic_data));
        {
            MySharedPtr<TestObject> ptr2(ptr1);
            /* Test that pointer deference points to the correct object */
            my_assert_str("Assigned pointer dereference", ptr2->mPtr->mStr, basic_str);
            /* Test reference count is 2 due to assignment */
            my_assert("RefCount 2", ptr2.getCnt() == 2);
            my_assert("Object Constructed", basic_data.mState == CONSTRUCTED);
        }
        /* Test reference count is 1 because one ptr is destroyed */
        my_assert("RefCount 1", ptr1.getCnt() == 1);
        my_assert("Object Constructed", basic_data.mState == CONSTRUCTED);
    }
    /* Test that the object was destructed as all reference are dropped */
    my_assert("Object Destructed", basic_data.mState == DESTRUCTED);
}

void test_assignment_overwrite()
{
    struct test_data basic_data(basic_str);
    struct test_data overwritten_data(overwritten_str);
    {
        MySharedPtr<TestObject> ptr1(new TestObject(&basic_data));
        {
            MySharedPtr<TestObject> ptr2(new TestObject(&overwritten_data));
            ptr1 = ptr2;
            /* Test that basic-data is destroyed */
            my_assert_str("Assigned pointer dereferences to new data", ptr1->mPtr->mStr, overwritten_str);
            /* Test reference count is 2 due to assignment */
            my_assert("RefCount 2", ptr2.getCnt() == 2);
            my_assert("Old Object Destructed", basic_data.mState == DESTRUCTED);
            my_assert("New Object Constructed", overwritten_data.mState == CONSTRUCTED);
        }
    }
    /* Test that the object was destructed as all reference are dropped */
    my_assert("Object Destructed", overwritten_data.mState == DESTRUCTED);
}

int main(void)
{
    test_basics();
    test_assignment();
    test_assignment_overwrite();
}
