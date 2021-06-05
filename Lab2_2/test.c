#include "main.h"
#include <assert.h>
#include <stdio.h>

void test()
{
assert(Num(50, 50, 50)==3);
assert(Num(50, 50, 110)==5);
assert(Num(50, 50, 75)==4);
}

#undef main

int main() 
{
    test();
}