#include <stdio.h>

void myprint(char *msg)
{
    printf("echo %s; \n",msg);
}

int main(int argc,char *argv[])
{
    char *s;
    s = argv[1];
    void (*f)(char *msg) = myprint;
    f(s);
    return 0;
}
