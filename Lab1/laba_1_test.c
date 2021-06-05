#include "laba_1.h"
#include <stdio.h>
#include <assert.h>

int test() 
{
    structure x = BinGet(2, 4);
    assert(x.number == 3 && x.bin == 11);
    x = BinGet(100, 102);
    assert(x.number == 102 && x.bin == 1100110);
    x = BinGet(10, 15);
    assert(x.number == 15 && x.bin == 1111);
} 

#undef main

int main() 
{
    test();
}