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
        LargeObject *obj = new LargeObject('a');
        MySharedPtr<LargeObject> ptr(obj);
        obj->Print();
    }
    printf("After the block\n");
    return 0;
}

