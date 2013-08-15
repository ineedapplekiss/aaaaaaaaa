#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int number;
    char *msg;
} unit;

int main(void)
{
    unit node;
    node.number = 12;
    node.msg = "aaaaa";
    printf("%d --- %s \n",node.number,node.msg);
    return 0;
}
