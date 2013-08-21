#include "queue_tools.h"

void strcut(const char* haystack, char* needle, char** result)
{
	if (!haystack || strlen(haystack) <= 0)
	{
		fprintf(stderr, "参数haystack不能为空\n");
		exit(-1);
	}
	if (!needle || strlen(needle) <= 0)
	{
		fprintf(stderr,"参数needle不能为空\n");
		exit(-1);
	}
	
	printf("%s\n", haystack);
}

// void strprintf(const char* format)
// {
// 	va_list argv;
// 	
// }