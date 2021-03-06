#include <stdio.h>
#include "MySharedPtr.h"

class LargeObject
{
private:
    char a[1000];
    char val;
public:
    LargeObject(char newVal) : val(newVal) { printf("LargeObject: constructed\n"); }
    void Print(void) { printf("LargeObject: Value is %c\n", val); }
    ~LargeObject() { printf("LargeObject: destructed\n"); }
};

int main(void)
{
    printf("Before the block\n");
    {
        MySharedPtr<LargeObject> ptr(new LargeObject('b'));
        // Because the copy-constructor is private, this operation is invalid
        //        MySharedPtr<LargeObject> ptr2 = ptr;
        ptr->Print();
    }
    printf("After the block\n");
    return 0;
}

