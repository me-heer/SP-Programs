#include<stdio.h>
#include<conio.h>

int main()
{
    char ch,string[100];
    int stringIndex = 0;
    printf("Enter the text: ");
    while(1)
    {
		//read a single character
		ch=fgetc(stdin);

		if(ch=='\n')
		{
		    string[stringIndex++] = ch;
			ch = fgetc(stdin);
			if(ch == '\n')
			    break;
            else
                string[stringIndex++] = ch;
		}
		else
			string[stringIndex++] = ch;
		//read dummy character to clear
		//input buffer, which inserts after character input
	}
	for(int s = 0; s < stringIndex ;s++)
        printf("%c",string[s]);
	for(int s = 0; s < stringIndex ;s++)
    {
        if(string[s] >= 'A' && string[s] <= 'Z')
            printf("%c : uppercase.\n",string[s]);
        if(string[s] >= 'a' && string[s] <= 'z')
            printf("%c : lowercase.\n",string[s]);
        switch(string[s])
        {
            case '+': case '-': case '*': case '/': case '%':
            case '=':
            printf("%c : operator.\n",string[s]);
        }
        switch(string[s])
        {
            case '!': case '@': case '#': case '$': case '^':
            case '&': case '(': case ')': case '{': case '}':
            case '[': case ']': case ',': case '.': case '\\':
            case '<': case '>': case '?': case ';': case ':':
            case '\'': case '"': case '|': case '`': case '~':
            printf("%c : special character.\n",string[s]);
        }

    }
}
