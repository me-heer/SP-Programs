#include <stdio.h>
#include <stdlib.h>

int main()
{
    char path[100];
    printf("Enter file path to be opened.\n");
    scanf("%s",&path);
    FILE *read, *write;
    read = fopen(path,"r");
    write = fopen("writeFile.txt","w");
    while(!feof(read))
    {
        char c = fgetc(read);
    }
    int curpos = ftell(read);
    printf("CURPOS: %d\n",curpos);
    fseek(read,0,0);
    while(curpos>0)
    {
        char c = fgetc(read);
        fputc(c,write);
        curpos--;
    }
}
