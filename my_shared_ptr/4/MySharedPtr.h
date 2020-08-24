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
 *   4 - Adds assignment support (newPtr a; a = b)
 */
template <typename T>
class MySharedPtr
{
private:
    T *mPtr;
    RefCnt *mRefCnt;

    void DestroyObject()
    {
        if (mPtr) {
            printf("MySharedPtr: destructed: pre refcnt: %d\n", mRefCnt->ReadValue());
            if (mRefCnt->Put() == 0) {
                delete mRefCnt;
                delete mPtr;
            }
        }
    }

    void CopyObject(const MySharedPtr &oldVal)
    {
        mPtr    = oldVal.mPtr;
        mRefCnt = oldVal.mRefCnt;
        if (mPtr) {
            mRefCnt->Take();
            printf("MySharedPtr: copied: post refcnt:%d\n", mRefCnt->ReadValue());
        }
    }

public:
    MySharedPtr(T *newPtr) :
        mPtr(newPtr),
        mRefCnt(new RefCnt)
    {
        printf("MySharedPtr: constructed: post refcnt:1\n");
    }

    MySharedPtr() : mPtr{nullptr}, mRefCnt{nullptr} {}

    MySharedPtr(const MySharedPtr &oldVal)
    {
        CopyObject(oldVal);
    }

    MySharedPtr &operator=(const MySharedPtr &rhs)
    {
        DestroyObject();
        CopyObject(rhs);
        return *this;
    }

    ~MySharedPtr()
    {
        DestroyObject();
    }

    T *operator->() {return mPtr;}

};

#endif /* ! MY_SHARED_PTR_H_ */
