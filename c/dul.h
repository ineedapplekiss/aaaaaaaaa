#ifndef DUL_H
#define DUL_H

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
typedef int ElemType;
typedef int Status;


//================================
// 头节点结构
//================================

//================================
// 数据节点 
//================================
typedef struct Node
{
    ElemType data;
    struct Node *next;
} Node;

typedef struct Node *LinkList;

Status InitList(LinkList *L);
Status ListInsert(LinkList *L, int i, ElemType e);
Status ListDelete(LinkList *L, int i);

#endif
