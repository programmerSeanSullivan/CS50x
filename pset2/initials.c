#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int main(void)
{   
    string name = GetString();
    printf("%c",toupper(name[0]));
    for(int j=0, n = strlen(name); j < n; j++)
    {
        if(name[j] == ' ' && name[j + 1] != '\0')
        {
            printf("%c", toupper(name[j+1]));
        }
    }
    printf("\n");   
}


