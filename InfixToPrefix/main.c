#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char stack[100];
int top = -1;

void push(char temp)
{
    top++;
    stack[top] = temp;
}

char pop()
{
    return stack[top--];
}

int getPriority(char operator)
{
    switch(operator){
        case '+': case '-': return 1; break;
        case '*': case '/': return 2; break;
        case '^': return 3; break;
    }
}

int main()
{
    int i,j,p=0;
    char infix[100],reverse[100],prefix[100];
    printf("Enter infix: ");
    scanf("%s",reverse);
    int length = strlen(reverse);
    j = length-1;
    for(i = 0; i < length; i++)
    {
        infix[i] = reverse[j];
        j--;
    }
    for(i = 0; i < length; i++)
    {
        if(infix[i] == '(')
            infix[i] = ')';
        else if(infix[i] == ')')
            infix[i] = '(';
    }

    for(i = 0; infix[i] != '\0'; i++ )
    {
        switch(infix[i])
        {
            case '(':
                    push(infix[i]);
                    break;
            case ')':
                    while( stack[top] != '(')
                    {
                        char temp = pop();
                        prefix[p] = temp;
                        p++;
                    }
                    pop();
                    break;
            case '+': case '-': case '*': case '/': case '^':
            //check priority
            //push if stackPriority is > infix priority
            //printf("P1 : %d ",getPriority(stack[top]));
            //printf("P2 : %d\n",getPriority(infix[i]));
            if(top == -1 || stack[top] == '(')
                push(infix[i]);
            else if( getPriority(stack[top]) < getPriority(infix[i]) )
                push(infix[i]);
            else
            {
                //pop the whole stack until lower priority
                while( getPriority(stack[top]) >= getPriority(infix[i])  && stack[top] != '(')
                {
                    char temp = pop();
                    prefix[p] = temp;
                    p++;
                    //printf("%c",temp);
                }
                push(infix[i]);
            }
            break;
            default:
            prefix[p] = infix[i];
            p++;
            //printf("%c",infix[i]);
            break;
        }
    }
    //pop the remaining stack
    while(top >= 0)
    {
        char temp = pop();
        prefix[p] = temp;
        p++;
        //printf("%c",temp);
    }
    char final[100];
    int lengthPrefix = strlen(prefix);
    j = lengthPrefix - 1;
    for(i = 0; i < lengthPrefix; i++)
    {
        final[i] = prefix[j];
        j--;
    }

    for(i = 0; i < lengthPrefix; i++)
    {
        if(final[i] == '(')
            final[i] = ')';
        else if(final[i] == ')')
            final[i] = '(';
    }

    for(i = 0; i < lengthPrefix; i++)
        printf("%c",final[i]);
    printf("\n");
}
