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

//#define MYSHAREDPTR_LOCKING 
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

//#define MYSHAREDPTR_REFCNT_DEBUG
#ifdef MYSHAREDPTR_REFCNT_DEBUG
#define refcnt_debug printf
#else
#define refcnt_debug(fmt, args...)
#endif

class SharedPtrTable
{
 private:
    int mRefCnt;
    std_mutex mLock;

    /* Disable Copy Constructor */
    SharedPtrTable(SharedPtrTable &val) {}
 public:
    explicit SharedPtrTable() : mRefCnt(1)
    {
        refcnt_debug("   %p refcnt:1\n", this);
    }

    SharedPtrTable *Take()
    {
        const lock_guard lock(mLock);
        mRefCnt++;
        refcnt_debug("   %p refcnt:%d\n", this, mRefCnt);
        return this;
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
        refcnt_debug("   %p refcnt:%d\n", this, mRefCnt);
        mRefCnt--;
        if (mRefCnt == 0) {
            return true;
        }
        return false;
    }
};

/* Note that while accesses to the SharedPtrTable are multi-thread
 * safe, access to the MySharedPtr is not supposed to be multi-thread
 * safe.
 */
template <typename T>
class MySharedPtr
{
private:
    T *mPtr;
    SharedPtrTable *mSharedTable;

    void releaseSharedPtrTable()
    {
        if (mSharedTable) {
            if (mSharedTable->Put() == true) {
                delete mPtr;
                delete mSharedTable;
            }
        }
    }
public:
    /* Initialise with a pre-allocated pointer */
    explicit MySharedPtr(T *newPtr) :
        mPtr(newPtr)
    {
        mSharedTable = new SharedPtrTable();
        if (!mSharedTable) {
            /* No exception environment */
            printf("Error!\n");
        }
    }

    /* Simple definition, no init */
    explicit MySharedPtr() :
        mSharedTable{nullptr},
        mPtr{nullptr}
    {}

    /* Copy constructor */
    MySharedPtr(const MySharedPtr &oldVal)
    {
        mPtr = oldVal.mPtr;
        mSharedTable = oldVal.mSharedTable->Take();
    }

    /* Assignment after construction */
    MySharedPtr &operator=(const MySharedPtr &rhs)
    {
        releaseSharedPtrTable();
        mPtr = rhs.mPtr;
        mSharedTable = rhs.mSharedTable->Take();
        return *this;
    }

    ~MySharedPtr()
    {
        releaseSharedPtrTable();
    }

    T *operator->()
    {
        return mPtr;
    }

    T &operator*()
    {
        return mPtr;
    }

    int getCnt()
    {
        if (mSharedTable) {
            return mSharedTable->getCnt();
        }
        return 0;
    }
};

#endif /* ! MY_SHARED_PTR_H_ */
