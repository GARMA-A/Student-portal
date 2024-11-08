#include <stdio.h>

int getnum(int num);

int main()
{

    int x;
    scanf("%d",&x);
    printf("%d",getnum(x));



}


int getnum(int num)
{

 return num * 2;



}