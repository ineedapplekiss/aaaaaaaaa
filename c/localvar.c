#include <stdio.h>

void test(void)
{
    int i;
    printf("variable i : %d \n",i);
    i = 500;
}

int main(void)
{
    test();
    printf("hello\n");
    test();
    return 0;
}
