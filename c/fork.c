#include <stdio.h>
#include <unistd.h>

int main(void)
{
    pid_t pid;
    printf("now only one process\n");
    printf("calling fork...\n");
    pid = fork();
    if(!pid)
    {
        printf("this is child process..\n");
    }
    else if(pid > 0)
    {
        printf("is parent,child has pid %d \n",pid);
    }
    else
    {
        printf("failed \n");
    }
    return 0;
}
