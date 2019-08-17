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
    int i;
    char infix[100];
    printf("Enter infix: ");
    scanf("%s",infix);
    int length = strlen(infix);
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
                        printf("%c",temp);
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
                    printf("%c",temp);
                }
                push(infix[i]);
            }
            break;
            default: printf("%c",infix[i]); break;
        }
    }
    //pop the remaining stack
    while(top >= 0)
    {
        char temp = pop();
        printf("%c",temp);
    }
}

