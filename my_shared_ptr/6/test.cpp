#include <stdio.h>
#include <string.h>
#include "MySharedPtr.h"

#define MAX_REGISTERED_TESTS  10
static struct test_desc {
    const char *td_name;
    void (*td_func)(void);
} g_registered_tests[MAX_REGISTERED_TESTS];
static int g_total_tests;
static bool g_test_success;

/* Standard test framework, can be moved to a separate file */
#define etest_assert(string, condition) \
    do { \
       if (!(condition)) { \
           printf("[%s:%d] Error: %s\n", __FILE__, __LINE__, string);    \
           g_test_success = false; \
       } \
    } while(0)

#define etest_assert_str(string, expected, actual) \
    do { \
        if (strcmp(expected, actual) != 0) {    \
           printf("[%s:%d] Error: %s Expected:%s: Received:%s:\n", __FILE__, __LINE__, string, expected, actual); \
           g_test_success = false; \
       } \
    } while(0)

    
void etest_tests_register(const char *name, void (*func)(void))
{
    if (g_total_tests > MAX_REGISTERED_TESTS) {
        printf("Error: Failed to register tests: limit reached\n");
        return;
    }
    g_registered_tests[g_total_tests].td_name = name;
    g_registered_tests[g_total_tests].td_func = func;
    g_total_tests++;
}

void etest_tests_execute()
{
    for (int i = 0; i < g_total_tests; i++) {
        g_test_success = true;
        printf("%s: ", g_registered_tests[i].td_name);
        (*g_registered_tests[i].td_func)();
        if (g_test_success) {
            printf("Passed\n");
        } else {
            printf("Failed\n");
        }
    }
}

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
void test_basics(void)
{
    struct test_data basic_data(basic_str);
    {
        MySharedPtr<TestObject> ptr(new TestObject(&basic_data));
        /* Test that pointer deference points to the correct object */
        etest_assert_str("Pointer dereference", ptr->mPtr->mStr, basic_str);
        /* Test default reference count is 1 */
        etest_assert("Default ref 1", ptr.getCnt() == 1);
        etest_assert("Object Constructed", basic_data.mState == CONSTRUCTED);
    }
    /* Test that the 'ptr' was destructed */
    etest_assert("Object Destructed", basic_data.mState == DESTRUCTED);
}

void test_assignment(void)
{
    struct test_data basic_data(basic_str);
    {
        MySharedPtr<TestObject> ptr1(new TestObject(&basic_data));
        {
            MySharedPtr<TestObject> ptr2(ptr1);
            /* Test that pointer deference points to the correct object */
            etest_assert_str("Assigned pointer dereference", ptr2->mPtr->mStr, basic_str);
            /* Test reference count is 2 due to assignment */
            etest_assert("RefCount 2", ptr2.getCnt() == 2);
            etest_assert("Object Constructed", basic_data.mState == CONSTRUCTED);
        }
        /* Test reference count is 1 because one ptr is destroyed */
        etest_assert("RefCount 1", ptr1.getCnt() == 1);
        etest_assert("Object Constructed", basic_data.mState == CONSTRUCTED);
    }
    /* Test that the object was destructed as all reference are dropped */
    etest_assert("Object Destructed", basic_data.mState == DESTRUCTED);
}

void test_assignment_overwrite(void)
{
    struct test_data basic_data(basic_str);
    struct test_data overwritten_data(overwritten_str);
    {
        MySharedPtr<TestObject> ptr1(new TestObject(&basic_data));
        {
            MySharedPtr<TestObject> ptr2(new TestObject(&overwritten_data));
            ptr1 = ptr2;
            /* Test that basic-data is destroyed */
            etest_assert_str("Assigned pointer dereferences to new data", ptr1->mPtr->mStr, overwritten_str);
            /* Test reference count is 2 due to assignment */
            etest_assert("RefCount 2", ptr2.getCnt() == 2);
            etest_assert("Old Object Destructed", basic_data.mState == DESTRUCTED);
            etest_assert("New Object Constructed", overwritten_data.mState == CONSTRUCTED);
        }
    }
    /* Test that the object was destructed as all reference are dropped */
    etest_assert("Object Destructed", overwritten_data.mState == DESTRUCTED);
}


int main(void)
{
    etest_tests_register("[SharedPtr] Basic", &test_basics);
    etest_tests_register("[SharedPtr] Assignment", &test_assignment);
    etest_tests_register("[SharedPtr] Overwrite with Assignment", &test_assignment_overwrite);
    etest_tests_execute();
}
