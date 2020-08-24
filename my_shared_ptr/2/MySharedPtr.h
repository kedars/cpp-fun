#ifndef MY_SHARED_PTR_H_
#define MY_SHARED_PTR_H_

#include <stdio.h>

/* Changes: Adds a dereference operator */
template <typename T>
class MySharedPtr
{
private:
    T *mPtr;
    MySharedPtr(const MySharedPtr &oldVal) {}
public:
    MySharedPtr(T *newPtr) : mPtr(newPtr)
    {
        printf("MySharedPtr: constructed\n");
    }

    ~MySharedPtr()
    {
        printf("MySharedPtr: destructed\n");
        if (mPtr) {
            delete mPtr;
        }
    }

    T * operator->() {return mPtr;}
};

#endif /* ! MY_SHARED_PTR_H_ */
