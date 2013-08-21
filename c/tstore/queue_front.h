#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
	
#define TQUEUE_VERSION "0.0.1"
#define TQUEUE_AUTHOR "qunqiang<qunqiang@leju.com>"


void CUI_Create(void);

void CUI_Create_Prompt(const char* prompt_string);

void CUI_Output(const char* string, _Bool needBR);

void CUI_Menu_Show();

void CUI_Error(const char* string);