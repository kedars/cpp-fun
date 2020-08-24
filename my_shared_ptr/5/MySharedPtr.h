#ifndef MY_SHARED_PTR_H_
#define MY_SHARED_PTR_H_

#include <stdio.h>

/* Changes: 
 *   2 - Adds a dereference operator
 *   3 - Adds a reference count and supports copy-construction (newPtr a = b)
 *   4 - Adds assignment support (newPtr a; a = b)
 *   5 - Create a separate SharedPtrTable object
 */

/* This being a template will add to the .text section */
template <typename T>
class SharedPtrTable
{
 private:
    T *mPtr;
    int mRefCnt;
    /* Disable Copy Constructor */
    SharedPtrTable(SharedPtrTable &val) {}
 public:
    explicit SharedPtrTable(T *ptr) : mPtr(ptr), mRefCnt(1)
    {
        printf("   %p refcnt:1\n", this);
    }

    SharedPtrTable *Take()
    {
        mRefCnt++;
        printf("   %p refcnt:%d\n", this, mRefCnt);
        return this;
    }

    T *getPtr()
    {
        return mPtr;
    }

    /* Return 'true' if self needs to be deleted */
    bool Put()
    {
        mRefCnt--;
        printf("   %p refcnt:%d\n", this, mRefCnt);
        if (mRefCnt == 0) {
            delete mPtr;
            return true;
        }
        return false;
    }
};

template <typename T>
class MySharedPtr
{
private:
    SharedPtrTable<T> *mSharedTable;

    void releaseSharedPtrTable()
    {
        if (mSharedTable) {
            if (mSharedTable->Put() == true) {
                delete mSharedTable;
            }
        }
    }
public:
    /* Initialise with a pre-allocated pointer */
    explicit MySharedPtr(T *newPtr)
    {
        mSharedTable = new SharedPtrTable<T>(newPtr);
        if (!mSharedTable) {
            /* No exception environment */
            printf("Error!\n");
        }
    }

    /* Simple definition, no init */
    explicit MySharedPtr() : mSharedTable{nullptr} {}

    /* Copy constructor */
    MySharedPtr(const MySharedPtr &oldVal)
    {
        mSharedTable = oldVal.mSharedTable->Take();
    }

    /* Assignment after construction */
    MySharedPtr &operator=(const MySharedPtr &rhs)
    {
        releaseSharedPtrTable();
        mSharedTable = rhs.mSharedTable->Take();
        return *this;
    }

    ~MySharedPtr()
    {
        releaseSharedPtrTable();
    }

    T *operator->()
    {
        return mSharedTable->getPtr();
    }

};

#endif /* ! MY_SHARED_PTR_H_ */
