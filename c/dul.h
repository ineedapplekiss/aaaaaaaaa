#ifndef DUL_H
#define DUL_H 1

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
typedef char *ElemType;
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
    struct Node *pre;
} Node;

extern Node *InitList(void);
extern void freeNode(Node *);

//Status dPush(LinkList, ElemType);
//Status dPop(LinkList);
//Status dShow(LinkList);


#endif
