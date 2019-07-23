#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <dir.h>

int main()
{
    int flag = 1;
    char dirName[10];
    while(flag!=0)
    {
        printf("Enter a directory name:\n");
        printf("E.g.: D:\\Movies\\\n");
        scanf("%s",&dirName);
        flag = mkdir(dirName);
        if(flag!=0)
            printf("Couldn't create the directory. Try another name.\n");
        else
            printf("Directory successfully created.\n");
    }
    return 0;
}
