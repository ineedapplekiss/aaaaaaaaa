#include <stdio.h>

int main(void)
{
    int a=1,b=1;
    while(a<10)
    {
        if(b>9)
        {
            a++;
            b=a;
            printf("\n");
        }
        printf("%d*%d=%d ",a,b,a*b);
        b++;
    }
    return 0;
}

