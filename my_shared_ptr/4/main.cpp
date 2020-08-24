#include <stdio.h>
#include "MySharedPtr.h"

class LargeObject
{
private:
    char a[1000];
    char val;
public:
    LargeObject(char newVal) : val(newVal) { printf("LargeObject: constructed (value %c)\n", val); }
    void Print(void) { printf("LargeObject: Value is %c\n", val); }
    ~LargeObject() { printf("LargeObject: destructed (value %c)\n", val); }
};

int main(void)
{
    MySharedPtr<LargeObject> ptr3(new LargeObject('z'));
    MySharedPtr<LargeObject> ptr4;
    ptr3->Print();
    printf("Before the block\n");
    {
        MySharedPtr<LargeObject> ptr(new LargeObject('b'));
        MySharedPtr<LargeObject> ptr2 = ptr;
        ptr->Print();
        ptr2->Print();
        /* The ptr3 reference to 'z' should be dropped here, and new one to 'b' created */
        ptr4 = ptr3 = ptr;
    }
    printf("After the block\n");
    ptr3->Print();
    return 0;
}

