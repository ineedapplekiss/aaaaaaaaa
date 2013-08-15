#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dul.h"

Node *InitList(void){
    Node *L = malloc(sizeof(Node));
    if(L == NULL) {
        printf("out of memory\n");
        exit(1);
    }
    L->next = NULL;
    L->pre = NULL;
    L->data = malloc(20);
    strcpy(L->data,"list leader\0");
    return L;
}

void freeNode(Node *p)
{
    free(p->data);
    free(p);
    p = NULL;
}
