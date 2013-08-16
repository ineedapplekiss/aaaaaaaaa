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
    L->data = "i'm first";
    return L;
}

void freeNode(Node *p)
{
    //free(p->data);
    //p->data = NULL;
    free(p);
    p = NULL;
}

Status dList(Node *p)
{
    int i=0;
    Node *cur = p;
    while(cur)
    {
        printf("listnum:%d val:%s \n",i,cur->data);
        i++;
        cur = cur->next;
    }

    return OK;
}

Status dPush(Node *p,ElemType val)
{
    Node *new_node = malloc(sizeof(Node));
    if(new_node == NULL) {
        printf("out of memory\n");
        exit(1);
    }
    new_node->next = p->next;
    p->next = new_node;
    new_node->data = malloc(sizeof(val));
    strncpy(new_node->data,val,5);
    return OK;
}

ElemType dPop(Node *p)
{
    Node *cur=p->next;
    ElemType res;
    if(cur == NULL) {
        return NULL;
    }
    p->next = cur->next;
    res = cur->data;
    freeNode(cur);
    return res;
}
