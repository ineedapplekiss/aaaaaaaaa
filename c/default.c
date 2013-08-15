#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dul.h"

char *cmds[] = {"list","push","pop","get","exit",NULL};

int getcmd(char *cmd)
{
    int n=0;
    while(cmds[n] != NULL)
    {
        if(strncasecmp(cmd,cmds[n],strlen(cmds[n]))==0)
        {
            return n;
        }
        n++;
    }
    return -1;
}
int main(void)
{
 
    char buf[1024];
    int ok;
    Node *L = InitList();

    printf("welcome! it's my service \n");

    fflush(stdout);

    ok=0;
    do
    {
        while(fgets(buf,1023,stdin)==NULL);
        
        switch(getcmd(buf))
        {
            case -1: printf("unknow command \n");break;
            case 0: 
                printf("%s\n",L->data); 
                break;
            case 4: printf("go ahead! \n");ok=1;break;
        }
        fflush(stdout); 
    }while(!ok);

    return 1;
}
