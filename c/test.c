#include <stdio.h>
#include <stdlib.h>

int main(int argc,char *argv[])
{
    char *a;
    if(argc < 2)
    {
        printf("Usage:file <url>;\n");
        exit(1);
    }
    a = argv[2];
    printf("c:%s \n",a);
    return 0;
}

