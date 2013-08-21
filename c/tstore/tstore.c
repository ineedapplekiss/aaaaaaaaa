#include "tstore.h"

extern void CUI_Error(char* string);

extern void CUI_Output(const char* string, _Bool needBR);


pTStore TStore_init()
{
	pTStore store = malloc(sizeof(TStore));
	// 创建空队列
	store->root = NULL;
	return store;
}

void TStore_set(pTStore store, char* keyname, char* value)
{
	pElem elem = TStore_search(store, keyname);
	if (elem)
	{
		memset(elem->data, 0, elem->dataLength);
		strncpy(elem->data, value, strlen(value));
		elem->dataLength = strlen(value);
	}
	else
	{
		elem = malloc(sizeof(Elem));
		// 赋值
		if(strlen(keyname) <= 0)
		{
			CUI_Error("无效的Key名称");
		}
		strncpy(elem->keyname, keyname, strlen(keyname));
		elem->keynameLength = strlen(keyname);
	
		if (strlen(value) <= 0)
		{
			CUI_Error("无效的value数据");
		}
		strncpy(elem->data, value, strlen(value));
		elem->dataLength = strlen(value);
	
		elem->tail = elem;
		elem->next = NULL;
		if (store->root == NULL)
		{
			elem->head = elem;	
			store->root = elem;
		}
		else
		{
			pElem tail = (pElem)store->root->tail;
			store->root->tail = elem;
			tail->next = elem;
		}
		
	}
	
	TStore_display(store);
	
	// 计算内存占用量	
	store->memorySize += (long long) sizeof(Elem);
	
	printf(": ok!\n");
}

void TStore_display_e(pElem elem)
{
	printf("------------------\n");
	printf("\t%s",elem->keyname);
	printf("\t\t%s\n", elem->data);
	printf("------------------\n");
}

pElem TStore_search(pTStore store, const char* keyname)
{
	if (store->root)
	{
		pElem root = store->root;
		while(root)
		{
			if (strncmp(root->keyname, keyname, strlen(keyname)) == 0)
			{
				return root;
			}
			root = root->next;
		}
		
	}
	return NULL;
}

void TStore_get(pTStore store, const char* keyname)
{
	if (strlen(keyname) <= 0)
	{
		CUI_Error("Key名称不能为空");
	}
	
	pElem elem = TStore_search(store, keyname);
	
	if (elem)
	{
		TStore_display_e(elem);
	}
	else
	{
		CUI_Output("nil", true);
	}
}

void TStore_display(pTStore store)
{
	
	if (store->root)
	{
		pElem root = store->root;
		while(root)
		{
			printf("\t%s ",root->keyname);
			printf("\t\t%s\n", root->data);
			root = root->next;
		}
		
	}
	else
	{
		printf("empty store\n");
	}
	
}