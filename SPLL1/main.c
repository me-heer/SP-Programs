#include <stdio.h>
#include <stdlib.h>

void printFormatArray(int* formatArray)
{
    printf("FORMAT ARRAY: ");
    for(int i = 0; i < 6; i++)
        printf("%c ",formatArray[i]);
}

int getSymbolID(char c)
{
    switch(c)
    {
        case 'x': return 0; break;
        case '+': return 1; break;
        case '*': return 2; break;
        case '(': return 3; break;
        case ')': return 4; break;
        case '$': return 5; break;
    }
}

char getSymbol(int i)
{
    switch(i)
    {
        case 0: return 'x'; break;
        case 1: return '+'; break;
        case 2: return '*'; break;
        case 3: return '('; break;
        case 4: return ')'; break;
        case 5: return '$'; break;
    }

}

int hasSlash(char givenGrammar[5][11], int i)
{
    int j;
    for( j = 0; givenGrammar[i][j] != NULL; j++)
    {
        if(givenGrammar[i][j] == '/')
            return ++j;
    }
    return 0;
}

int isNonTerminal(char c)
{
    if(c >= 'A' && c <= 'Z' )
        return 1;
    else
        return 0;
}

int isNonTerminalAfterArrow(char givenGrammar[5][11], int i)
{
    int j = 0;
    while(givenGrammar[i][j] != '>')
        j++;
    j++;
    if(isNonTerminal(givenGrammar[i][j]))
        return 1;
    else
        return 0;
}

char findNonTerminalAfterArrow(char givenGrammar[5][11],int i)
{
    int j = 0;
    while(givenGrammar[i][j] != '>')
        j++;
    j++;
    return givenGrammar[i][j];
}

char findSpecifiedNonTerminalAfterArrow(char givenGrammar[5][11],int i,char specifiedSymbol)
{
    int j = 0;
    while(givenGrammar[i][j] != '>')
        j++;
    j++;
    while(givenGrammar[i][j] != NULL)
    {
        if(givenGrammar[i][j] == specifiedSymbol)
        {
            if(givenGrammar[i][j+1] == NULL)
                return '@';
            else
                return givenGrammar[i][j+1];
        }
        j++;
    }
    return '#';
}

char followStack[20];
int topFollow = -1;
void pushFollow(char c)
{
    topFollow++;
    followStack[topFollow] = c;
}

char popFollow()
{
    return followStack[topFollow--];
}
void displayFollow()
{
    for(int i = topFollow; i >= 0; i--)
        printf("%c",followStack[i]);
}

void findFollowWithStack(char givenGrammar[5][11],int currentProduction)
{
    if(currentProduction == 0)
            pushFollow('$');
    int i;
    char currentSymbol = givenGrammar[currentProduction][0];
    for(i = 0; i < 5; i++)
    {
        char c = findSpecifiedNonTerminalAfterArrow(givenGrammar,i,currentSymbol);
        //printf("RETURNED VALUE OF C: %c\n",c);
        if(c != '#')
        {
            if(c == '@')
            {
                findFollowWithStack(givenGrammar,i);
                break;
            }
            else if(!isNonTerminal(c) && c != '/')
            {
                pushFollow(c);
                break;
            }
            else if(isNonTerminal(c))
            {
                int j;
                for( j = 0; j < 5; j++)
                {
                    if(givenGrammar[j][0] == c)
                        break;
                }
                findFirstExceptNullForStack(givenGrammar,j);
                int hasNull = hasNullInFIRST(givenGrammar,j);
                if(hasNull)
                {
                    findFollowWithStack(givenGrammar,j);
                }
                break;
            }
        }
    }
}


void findFollow(char givenGrammar[5][11],int currentProduction)
{
    if(currentProduction == 0)
            printf("$, ");
    int i;
    char currentSymbol = givenGrammar[currentProduction][0];
    for(i = 0; i < 5; i++)
    {
        char c = findSpecifiedNonTerminalAfterArrow(givenGrammar,i,currentSymbol);
        //printf("RETURNED VALUE OF C: %c\n",c);
        if(c != '#')
        {
            if(c == '@')
            {
                findFollow(givenGrammar,i);
                break;
            }
            else if(!isNonTerminal(c) && c != '/')
            {
                printf("%c",c);
                break;
            }
            else if(isNonTerminal(c))
            {
                int j;
                for( j = 0; j < 5; j++)
                {
                    if(givenGrammar[j][0] == c)
                        break;
                }
                findFirstExceptNull(givenGrammar,j);
                int hasNull = hasNullInFIRST(givenGrammar,j);
                if(hasNull)
                {
                    findFollow(givenGrammar,j);
                }
                break;
            }
        }
    }
}

int hasNullInFIRST(char givenGrammar[5][11],int currentProduction)
{
    int nullFlag = 0;
    if(isNonTerminalAfterArrow(givenGrammar,currentProduction))
    {
        char Muratiyo = findNonTerminalAfterArrow(givenGrammar,currentProduction);
        int findNonTerminalIndex = 0;
        for(findNonTerminalIndex = 0; findNonTerminalIndex < 5; findNonTerminalIndex++)
        {
            if(givenGrammar[findNonTerminalIndex][0] == Muratiyo)
                break;
        }
        hasNullInFIRST(givenGrammar,findNonTerminalIndex);
    }
    else
    {
        char c = findNonTerminalAfterArrow(givenGrammar,currentProduction);
        if(c == 'e')
            nullFlag = 1;
        //check for forward slash
        int slashIndex = hasSlash(givenGrammar,currentProduction);
        if(slashIndex != 0)
        {
            char c =  givenGrammar[currentProduction][slashIndex];
            if(c == 'e')
                nullFlag = 1;
        }
    }
    return nullFlag;
}

void findFirstExceptNullForStack(char givenGrammar[5][11],int currentProduction)
{
    if(isNonTerminalAfterArrow(givenGrammar,currentProduction))
    {
        char Muratiyo = findNonTerminalAfterArrow(givenGrammar,currentProduction);
        int findNonTerminalIndex = 0;
        for(findNonTerminalIndex = 0; findNonTerminalIndex < 5; findNonTerminalIndex++)
        {
            if(givenGrammar[findNonTerminalIndex][0] == Muratiyo)
                break;
        }
        findFirstExceptNullForStack(givenGrammar,findNonTerminalIndex);
    }
    else
    {
        char c = findNonTerminalAfterArrow(givenGrammar,currentProduction);
        if(c != 'e')
            pushFollow(c);
        //check for forward slash
        int slashIndex = hasSlash(givenGrammar,currentProduction);
        if(slashIndex != 0)
        {
            char c =  givenGrammar[currentProduction][slashIndex];
            if(c != 'e')
                pushFollow(c);
        }
    }
}

int findFirstExceptNull(char givenGrammar[5][11],int currentProduction)
{
    int nullFlag = 0;
    if(isNonTerminalAfterArrow(givenGrammar,currentProduction))
    {
        char Muratiyo = findNonTerminalAfterArrow(givenGrammar,currentProduction);
        int findNonTerminalIndex = 0;
        for(findNonTerminalIndex = 0; findNonTerminalIndex < 5; findNonTerminalIndex++)
        {
            if(givenGrammar[findNonTerminalIndex][0] == Muratiyo)
                break;
        }
        findFirst(givenGrammar,findNonTerminalIndex);
    }
    else
    {
        char c = findNonTerminalAfterArrow(givenGrammar,currentProduction);
        if(c == 'e')
            nullFlag = 1;
        if(c != 'e')
            printf("%c, ",c);
        //check for forward slash
        int slashIndex = hasSlash(givenGrammar,currentProduction);
        if(slashIndex != 0)
        {
            char c =  givenGrammar[currentProduction][slashIndex];
            if(c == 'e')
                nullFlag = 1;
            if(c != 'e')
                printf("%c, ",c);
        }
    }
    return nullFlag;
}

int* findFirstExceptNullWithFormat(char givenGrammar[5][11],int currentProduction,int* formatArray)
{
    int nullFlag = 0;
    if(isNonTerminalAfterArrow(givenGrammar,currentProduction))
    {
        char Muratiyo = findNonTerminalAfterArrow(givenGrammar,currentProduction);
        int findNonTerminalIndex = 0;
        for(findNonTerminalIndex = 0; findNonTerminalIndex < 5; findNonTerminalIndex++)
        {
            if(givenGrammar[findNonTerminalIndex][0] == Muratiyo)
                break;
        }
        findFirstExceptNullWithFormat(givenGrammar,findNonTerminalIndex,formatArray);
    }
    else
    {
        char c = findNonTerminalAfterArrow(givenGrammar,currentProduction);
        if(c == 'e')
            nullFlag = 1;
        if(c != 'e')
        {
            int id = getSymbolID(c);
            formatArray[id] = 1;
        }

        //check for forward slash
        int slashIndex = hasSlash(givenGrammar,currentProduction);
        if(slashIndex != 0)
        {
            char c =  givenGrammar[currentProduction][slashIndex];
            if(c == 'e')
                nullFlag = 1;
            if(c != 'e')
            {
                int id = getSymbolID(c);
                formatArray[id] = 1;
            }
        }
    }
    return formatArray;
}

char firstStack[20];
int top = -1;
void push(char c)
{
    top++;
    firstStack[top] = c;
}

char pop()
{
    return firstStack[top--];
}
void display()
{
    for(int i = top; i >= 0; i--)
        printf("%c",firstStack[i]);
}

void findFirstWithStack(char givenGrammar[5][11],int currentProduction)
{
    if(isNonTerminalAfterArrow(givenGrammar,currentProduction))
    {
        char Muratiyo = findNonTerminalAfterArrow(givenGrammar,currentProduction);
        int findNonTerminalIndex = 0;
        for(findNonTerminalIndex = 0; findNonTerminalIndex < 5; findNonTerminalIndex++)
        {
            if(givenGrammar[findNonTerminalIndex][0] == Muratiyo)
                break;
        }
        findFirstWithStack(givenGrammar,findNonTerminalIndex);
    }
    else
    {
        if(findNonTerminalAfterArrow(givenGrammar,currentProduction) != 'e')
            push(findNonTerminalAfterArrow(givenGrammar,currentProduction));
        //check for forward slash
        int slashIndex = hasSlash(givenGrammar,currentProduction);
        if(slashIndex != 0)
        {
            if( givenGrammar[currentProduction][slashIndex] != 'e')
                push(givenGrammar[currentProduction][slashIndex]);
        }
    }
}

void findFirst(char givenGrammar[5][11],int currentProduction)
{
    if(isNonTerminalAfterArrow(givenGrammar,currentProduction))
    {
        char Muratiyo = findNonTerminalAfterArrow(givenGrammar,currentProduction);
        int findNonTerminalIndex = 0;
        for(findNonTerminalIndex = 0; findNonTerminalIndex < 5; findNonTerminalIndex++)
        {
            if(givenGrammar[findNonTerminalIndex][0] == Muratiyo)
                break;
        }
        findFirst(givenGrammar,findNonTerminalIndex);
    }
    else
    {
        printf("%c, ",findNonTerminalAfterArrow(givenGrammar,currentProduction));
        //check for forward slash
        int slashIndex = hasSlash(givenGrammar,currentProduction);
        if(slashIndex != 0)
        {
            printf("%c ", givenGrammar[currentProduction][slashIndex]);
        }
    }
}

int main()
{
    char givenGrammar[5][11] =
    {
        {'E','-','>','T','A',},
        {'A','-','>','+','T','A','/','e'},
        {'T','-','>','F','B'},
        {'B', '-', '>', '*', 'F', 'B', '/', 'e'},
        {'F', '-', '>', '(', 'E', ')', '/', 'x'}
     };
     for(int i = 0; i < 5; i++)
     {
        for(int j = 0; givenGrammar[i][j] != NULL;j++)
            printf("%c", givenGrammar[i][j]);
        printf("\n");
     }
     printf("\n");

    //finding FIRST(E)
    for(int i = 0; i < 5; i++)
    {
        printf("FIRST(%c): { ",givenGrammar[i][0]);
        findFirst(givenGrammar, i);
        printf("}\n");
    }
    printf("\n");
    for(int i = 0; i < 5; i++)
    {
        printf("FOLLOW(%c): { ",givenGrammar[i][0]);
        findFollow(givenGrammar,i);
        printf(" }\n");
    }


    printf("\n");

    /*
    for(int i = 0; i < 5; i++)
    {
        int formatArray[6] = {0};
        int* formatArrayPointer = findFirstExceptNullWithFormat(givenGrammar,i,formatArray);
        int hasNull = hasNullInFIRST(givenGrammar,i);
        if(hasNull)
        {
            formatArrayPointer = findFollowWithFormat(givenGrammar,i,formatArray);
        }
        for(int i = 0; i < 6; i++)
            printf(" %d ",formatArrayPointer[i]);
        //printf("%c: ",givenGrammar[i][0]);
        //int flag = findFirstExceptNull(givenGrammar,i);
        //if(flag == 1)
        //   findFollow(givenGrammar,i);
        printf("\n");
    }
    */
    int LL1[5][6] = {0};
    for(int index = 0; index < 5; index++)
    {
        findFirstWithStack(givenGrammar,index);
        while(top >= 0)
        {
            char c = pop();
            int i = getSymbolID(c);
            LL1[index][i]++;
        }
        if(hasNullInFIRST(givenGrammar,index))
        {
            findFollowWithStack(givenGrammar,index);
            while(topFollow >= 0)
            {
                int i;
                char c = popFollow();
                if(c != 'e')
                    i = getSymbolID(c);
                LL1[index][i]++;
            }
        }

    }

    int notLL1 = 0;
    printf("   ");
    for(int i = 0 ; i < 6; i++)
    {
        printf("%c ",getSymbol(i));
    }
    printf("\n");
    for(int i = 0; i < 5; i++)
    {
        printf("%c: ",givenGrammar[i][0]);
        for(int j = 0; j < 6; j++)
        {
            if(LL1[i][j] > 1)
                notLL1 = 1;
            printf("%d ",LL1[i][j]);
        }
        printf("\n");
    }
    if(notLL1)
        printf("Given Grammar is not LL(1).\n");
    else
        printf("Given Grammar is LL(1).\n");
}
