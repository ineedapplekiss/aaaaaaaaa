#include<stdio.h>
unsigned long int count=0;
int overflow=0;
int main()
{
    int sta,end,from_num;
    sta = 1;
    end = 90000;
    while(sta<end)
    {
        from_num = sta;
        sta++;
        w(from_num,sta,end);
    }
    printf("finish:%d * 2000000000 +  %d \n" , overflow , count);
    return 1;
}

int w(int from_num , int sta , int end)
{
    while(sta <= end)
    {
        //printf("%d -- %d \n",from_num,sta);
        sta++;
        count++;
        if(count > 2000000000)
        {
            overflow++;
            count=0;
        }

    }
    return 1;
}
