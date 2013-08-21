#include "cui_types.h"
#include "queue_tools.h"

pcui_command cui_command_init(char* user_input)
{
	pcui_command command = malloc(sizeof(cui_command));
	memset(command->cmd, 0, 10);
	memset(command->keyname, 0, 50);
	memset(command->value, 0, 4096);
	
	if (strlen(user_input) > 0)
	{
		char *tmp_user_input = malloc(sizeof(user_input));
		memset(tmp_user_input, 0, strlen(user_input));
		strncpy(tmp_user_input, user_input, strlen(user_input));
		// printf("cmd长度%ld keyname长度%ld value长度%ld\n", sizeof(command->cmd), sizeof(command->keyname), sizeof(command->value));
	 	char *tmp_cmd = strtok(user_input, " ");
		char *tmp_keyname = strtok(NULL, " ");
		char *tmp_value = strtok(NULL, " ");
		// printf("cmd=%s\nkeyname=%s\nvalue=%s\n", tmp_cmd, tmp_keyname, tmp_value);
		if (!tmp_cmd)
		{
			fprintf(stderr, "命令不能为空\n");
			return NULL;
		}
		strncpy(command->cmd, tmp_cmd, strlen(tmp_cmd));
		if (tmp_keyname)
		{
			strncpy(command->keyname, tmp_keyname, strlen(tmp_keyname));
		}
		
		if (tmp_value)
		{
			if (tmp_value[0] == '\'')
			{
				// printf("contains space:%s\n", tmp_user_input);
				strtok(tmp_user_input, "'");
				tmp_value = strtok(NULL, "'");
			}
			strncpy(command->value, tmp_value, strlen(tmp_value));
		}
		free(tmp_user_input);
	}
	else
	{
		fprintf(stderr, "无效的指令输入,请重新输入\n");
		return NULL;
	}
	return command;
}

void cui_command_free(pcui_command command)
{
	free(command);
}

void cui_command_display(pcui_command command)
{
	printf("\nCommand Details:\n");
	printf("command:\t%s\n", command->cmd);
	printf("keyname:\t%s\n", command->keyname);
	printf("k-value:\t");
	puts(command->value);
	printf("---------------------------------------\n\n");	
}