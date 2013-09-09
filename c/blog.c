#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>

void mainInput(void);

int main(int argc,char *argv[])
{
    CURL *curl;
    CURLcode res;
    
    curl = curl_easy_init();
    if(curl!=NULL)
    {
        curl_easy_setopt(curl,CURLOPT_URL,argv[1]);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }
    return 1;
}

void mainInput(void)
{
    char command[1024];
    do{
        gets(command);
        printf("input %s \n",command);
        break;
    }while(1);
}

