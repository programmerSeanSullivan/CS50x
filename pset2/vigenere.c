#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    if(argc == 2)
    {
        string key = argv[1];
        for(int x = 0, n = strlen(key); x < n; x++)
        {
            if(key[x]>48 && key[x]<57)
            {
                printf("please enter letter characters only for the key");
            }
        }
        if(argc > 2 || argc < 2)
        {
            printf("Please enter in one word for the key");
        }
   
        for(int i = 0, n = strlen(key); i < n; i++)
        {
            if((int)key[i] > 48 && (int)key[i] < 57)
            {
                return 1;
            }
        }
        string message = GetString();
        int c, k, length = strlen(key); 
        for(int i = 0, count = 0, n = strlen(message); i < n; i++)
        {
            if(count == length)
            {
                count = 0;
            }  
            char kk = key[count];       
            if(isupper(message[i]))
            {
                k = (int)kk-65;
            }
            else if(islower(message[i]))
            {
                k = (int)kk-97;
            }             
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
                count++;  
            }
            else
            {
               printf("%c", message[i]);
            }            
        }
        printf("\n");
        if(key < 0)
        {
            return 1;
        }
   }
   else
   {
        printf("Please enter a key word");
        return 1;
   }
}
