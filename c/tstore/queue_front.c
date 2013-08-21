#include "queue_front.h"
#include "cui_types.h"
#include "tstore.h"

void CUI_Create()
{
	// 初始化交互数据存放空间
	size_t chunk_size = sizeof(char) * ELEM_LENGTH;
	// 初始化TQueue对象
	pTStore store = TStore_init();
	do
	{
		// 4096字节等于4k,用来存放用户录入的value
		// 10字节为queue系统的指令存储空间
		// 50字节用来存放用户输入的keyname
		char *user_input = malloc(chunk_size);
		CUI_Create_Prompt("输入help获取更多指令");
		// 接受输入直到回车
		scanf("%[^\n]", user_input);
		// 多余的一个回车接收
		getchar();
		pcui_command command = cui_command_init(user_input);
		if (command == NULL)
		{
			continue;
		}		
		if(strncmp(command->cmd, "quit", strlen(command->cmd)) == 0)
		{
			CUI_Output("bye!", true);
			break;
		}
		else if (strncmp(command->cmd, "help", strlen(command->cmd)) == 0)
		{
			CUI_Menu_Show();
		}
		
		else if (strncmp(command->cmd, "set", strlen(command->cmd)) == 0)
		{
			TStore_set(store, command->keyname, command->value);
		}
		
		else if (strncmp(command->cmd, "get", strlen(command->cmd)) == 0)
		{
			TStore_get(store, command->keyname);
		}
		
		// cui_command_display(command);
		// !!使用完记得释放内存
		// free(command);
		cui_command_free(command);
		memset(user_input, 0, chunk_size);
		free(user_input);
	} while (1);
}

void CUI_Create_Prompt(const char *prompt_string)
{
	if (strlen(prompt_string) > 0)
	{
		CUI_Output(prompt_string, true);
	}
	CUI_Output(">", false);
}


void CUI_Output(const char* string, _Bool need_br)
{
	
	if (need_br)
	{
		printf("%s\n", string);
	}
	else
	{
		printf("%s", string);
	}
}

void CUI_Menu_Show()
{
	CUI_Output("T-Queue Version:", false);
	CUI_Output(TQUEUE_VERSION, false);
	CUI_Output(" Author:", false);
	CUI_Output(TQUEUE_AUTHOR, true);
	CUI_Output(": help 帮助", true);
	CUI_Output(": set <keyname> 'data' 存放数据操作", true);
	//CUI_Output(": keysize 查看Queue key数量", true);
	//CUI_Output(": realsize 查看Queue 内存占用总量", true);
	CUI_Output(": get <keyname> 读取数据操作", true);
	CUI_Output(": quit 退出T-Queue", true);
	CUI_Output(" ", true);
}

void CUI_Error(const char* string)
{
	fprintf(stderr, "%s\n", string);
}