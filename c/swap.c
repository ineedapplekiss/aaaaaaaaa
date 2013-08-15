#include <stdio.h>

int swap(int *x, int *y)
{
    int temp;
    temp = *x;
    *x = *y;
    *y = temp;
    return *x;
}

int main(void)
{
    int a=1,b=2,pa;
    int *pa = &a;
    int *pb = &b;
    printf("a:%d;b:%d;pa:%d;pb:%d \n",a,b,&a,&b);
    pa = swap(&pa,&pb);
    printf("a:%d;b:%d;pa:%d;pb:%d \n",a,b,&a,&b);
    //printf("pa:%d;pb:%d \n",*pa,*pb);
    return 0;
}

