#include<stdio.h>
#include<malloc.h>
int main()
{
    int i;
    char *p[3];
    for(i=0;i<3;i++)
    {
        p[i] = (char*)malloc(100);
        scanf("%s",p[i]);
    }

    for(i=0;i<3;i++)
    {
        printf("%s\n",p[i]);
        free(p[i]);
        p[i] = NULL;
    }
    return 0;
}
