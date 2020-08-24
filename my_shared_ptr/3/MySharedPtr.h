#ifndef MY_SHARED_PTR_H_
#define MY_SHARED_PTR_H_

#include <stdio.h>

class RefCnt
{
private:
    int mCnt;
public:
    RefCnt() : mCnt(1) {}
    void Take() { mCnt++;}
    int Put() { return --mCnt;}
    int ReadValue() { return mCnt;}
};

/* Changes: 
 *   2 - Adds a dereference operator
 *   3 - Adds a reference count and supports copy-construction (newPtr a = b)
 */
template <typename T>
class MySharedPtr
{
private:
    T *mPtr;
    RefCnt *mRefCnt;

public:
    MySharedPtr(T *newPtr) :
        mPtr(newPtr),
        mRefCnt(new RefCnt)
    {
        printf("MySharedPtr: constructed: post refcnt:1\n");
    }

    MySharedPtr(const MySharedPtr &oldVal)
    {
        mPtr = oldVal.mPtr;
        mRefCnt = oldVal.mRefCnt;
        mRefCnt->Take();
        printf("MySharedPtr: constructed: post refcnt:%d\n", mRefCnt->ReadValue());
    }

    ~MySharedPtr()
    {
        printf("MySharedPtr: destructed: pre refcnt: %d\n", mRefCnt->ReadValue());
        if (mPtr) {
            if (mRefCnt->Put() == 0) {
                delete mRefCnt;
                delete mPtr;
            }
        }
    }

    T *operator->() {return mPtr;}

    /*
    T &operator=()
    {
        
    }
    */
};

#endif /* ! MY_SHARED_PTR_H_ */
