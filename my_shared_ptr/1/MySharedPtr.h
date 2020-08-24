#ifndef MY_SHARED_PTR_H_
#define MY_SHARED_PTR_H_

#include <stdio.h>

template <typename T>
class MySharedPtr
{
private:
    T *mPtr;

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
};

#endif /* ! MY_SHARED_PTR_H_ */
