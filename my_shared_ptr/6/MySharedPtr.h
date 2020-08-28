#ifndef MY_SHARED_PTR_H_
#define MY_SHARED_PTR_H_

#include <stdio.h>
/* Changes: 
 *   2 - Adds a dereference operator
 *   3 - Adds a reference count and supports copy-construction (newPtr a = b)
 *   4 - Adds assignment support (newPtr a; a = b)
 *   5 - Create a separate SharedPtrTable object
 *   6 - Locking
 */

#define MYSHAREDPTR_LOCKING 

#ifdef MYSHAREDPTR_LOCKING

#include <mutex>
using std_mutex = std::mutex;
using lock_guard = std::lock_guard<std::mutex>;

#else /* MYSHAREDPTR_LOCKING */

struct std_mutex {};
struct lock_guard {
    lock_guard(std_mutex a) {}
};

#endif /* MYSHAREDPTR_LOCKING */

/* This being a template will add to the .text section */
template <typename T>
class SharedPtrTable
{
 private:
    T *mPtr;
    int mRefCnt;
    std_mutex mLock;

    /* Disable Copy Constructor */
    SharedPtrTable(SharedPtrTable &val) {}
 public:
    explicit SharedPtrTable(T *ptr) : mPtr(ptr), mRefCnt(1)
    {
        printf("   %p refcnt:1\n", this);
    }

    SharedPtrTable *Take()
    {
        const lock_guard lock(mLock);
        mRefCnt++;
        printf("   %p refcnt:%d\n", this, mRefCnt);
        return this;
    }

    T *getPtr()
    {
        const lock_guard lock(mLock);
        return mPtr;
    }

    int getCnt()
    {
        const lock_guard lock(mLock);
        return mRefCnt;
    }

    /* Return 'true' if self needs to be deleted */
    bool Put()
    {
        const lock_guard lock(mLock);
        printf("   %p refcnt:%d\n", this, mRefCnt);
        mRefCnt--;
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
    std_mutex mLock;
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
        const lock_guard lock(mLock);
        mSharedTable = oldVal.mSharedTable->Take();
    }

    /* Assignment after construction */
    MySharedPtr &operator=(const MySharedPtr &rhs)
    {
        const lock_guard lock(mLock);
        releaseSharedPtrTable();
        mSharedTable = rhs.mSharedTable->Take();
        return *this;
    }

    ~MySharedPtr()
    {
        const lock_guard lock(mLock);
        releaseSharedPtrTable();
    }

    T *operator->()
    {
        const lock_guard lock(mLock);
        if (mSharedTable) {
            return mSharedTable->getPtr();
        }
        return nullptr;
    }

    T &operator*()
    {
        const lock_guard lock(mLock);
        if (mSharedTable) {
            return *(mSharedTable->getPtr());
        }
        return nullptr;
    }

    uint16_t getCnt()
    {
        const lock_guard lock(mLock);
        if (mSharedTable) {
            return mSharedTable->getCnt();
        }
        return 0;
    }
};

#endif /* ! MY_SHARED_PTR_H_ */
