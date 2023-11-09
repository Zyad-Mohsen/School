#include <stdio.h>
#include <stdlib.h>
#include "String.h"

void string_print(char*str)
{
    int i;
    for(i=0; str[i]; i++)
    {
        printf("%c",str[i]);
    }
    printf("\n");
}

int string_len(char*str)
{
    int i;
    for(i=0; str[i]; i++);
    return i;
}

int string_compareNotSensetive(char*str1,char*str2)
{
    int i,L1,L2;
    L1=string_len(str1);
    L2=string_len(str2);
    if(L1!=L2)
    {
        return 0;
    }
    for(i=0;str1[i];i++)
    {
        if((str1[i]==str2[i])||(str1[i]==(str2[i]-'A'+'a'))||(str2[i]==(str1[i]-'A'+'a')))
        {

        }
        else
        {
            return 0;
        }
    }
    return 1;
}
void string_scan(char*str,int maxSize)
{
    int i=0;
    fflush(stdin);
    scanf("%c",&str[i]);
    for(; str[i]!='\n';)
    {
        i++;
        scanf("%c",&str[i]);
        if(i==maxSize-1)
        {
            break;
        }
    }
    str[i]=0;
}
