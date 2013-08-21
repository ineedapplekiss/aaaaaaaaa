// cui_types.h
// 用户命令识别组件 头文件
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
	

// 结构定义部分
typedef struct {
	char cmd[10];
	char keyname[50];
	char value[4096];
} cui_command, *pcui_command;

// 创建一个命令识别组件
pcui_command cui_command_init(char* user_input);
// 释放一个命令识别组件
void cui_command_free(pcui_command cui_commmand);
// 打印command数据
void cui_command_display(pcui_command command);

