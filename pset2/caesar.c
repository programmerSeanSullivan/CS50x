#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    string key = argv[1];
    int k=0;
    string message = GetString();
    int c=0;
    if(argc == 2)
    {   
       
        for(int i = 0, n = strlen(message); i < n; i++)
        {
             k = atoi(key);
             if(isalpha(message[i]))
             {            
                if(isupper(message[i]))
                {
                    c = (((int)message[i]- 65) + k) % 26;
                    c = c + 65;
                }else if(islower(message[i]))
                {
                    c = (((int)message[i]- 97) + k) % 26;
                    c = c + 97;
                }
                printf("%c", c);
             }
             else
             {
                printf("%c", message[i]);
             }
        }
    }
    else if(argc<2)
    {
        
        return 2;
    }        
    printf("\n");    
    
         
}
