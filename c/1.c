#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
    int i=0;
    while(i<10)
    {
        printf("%d \r",i);
        fflush(stdout);
        i++;
        sleep(1);
    }
    printf("\n");
    return 0;
}
