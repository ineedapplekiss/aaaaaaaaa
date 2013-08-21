#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
	
	
#define ELEM_LENGTH 4156

typedef struct _Elem
{
	struct _Elem *head;
	struct _Elem *tail;
	struct _Elem *next;
	
	char data[4096];
	char keyname[50];
	
	unsigned int dataLength;
	unsigned short keynameLength;
} Elem, *pElem;

typedef struct 
{	
	pElem root;
	unsigned long int memorySize;
} TStore, *pTStore;

pTStore TStore_init();

void TStore_set(pTStore store, char* keyname, char* value);

void TStore_get(pTStore store, const char* keyname);

void TStore_display(pTStore store);

void TStore_display_e(pElem elem);

pElem TStore_search(pTStore store, const char* keyname);