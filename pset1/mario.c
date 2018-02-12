#include <cs50.h>
#include <stdio.h>

int main(void)
{
    //height of pyramid
    int h=0;
    //brick character
    string brick = "#";
    //space character
    string space = " ";
    //number of attempts in stating height
    int tries=0;
    //makes a lock on program to keep negative or large numbers unusable
    do
    {
        //asks for the height
        printf("height: ");
        //stores the height in variable h
        h = GetInt();
        //increase the attempts by one
        tries++;
        //if they entered wrong number three times or more replace message with Retry:
        if(tries >= 3)
        {
           do
           {
               printf("Retry: ");
               h = GetInt();
           }while(h<0 || h>23);
        }
    }while(h<0 || h>23 ); 
   //creates the height of pyramid 
   for(int i = 0; i < h; i++) 
	{
	    //creates number of spaces based on height	
        for(int j = 0; j <h-i-1; j++)
        {
            printf("%s", space);
        }
        //creates number of hashes based on spaces
		for(int k = 0; k < i+2; k++)
		{
			printf("%s",brick);
		}
		//tells computer to go to next line in pyramid
		printf("\n");
	}	            
}
