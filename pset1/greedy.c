#include <cs50.h>
#include <stdio.h>

int main(void)
{
    //declaration of coins and there respective worths left as whole numbers
    int penny         =  01;
    int nickel        =  05;
    int dime          =  10;
    int quarter       =  25;
    //declaration of the amount of change to be determined later
    float change      = 0.0;
    //declaration of the number of coins needed to make change
    int numberOfCoins = 0;
    //prints out O hai! How much change is owed?
    printf("O hai! How much change is owed? ");
    //stores the input as a float into variable change
    change = GetFloat();
    //making change into a whole number to prevent possible rounding mistakes
    change = change*100;
    //tells program to run this loop over and over again until change is zero
    do
    {   
        //while change is smaller or equal to a quarter subtract a quarter from change add a coin to count      
        while(change >= quarter)
        {
            change = change - quarter;
            numberOfCoins++;
        }
        //while change is smaller or equal to a dime subtract a dime from change add a coin to count    
        while(change >= dime)
        {
            change = change - dime;
            numberOfCoins++;                 
        }
        //while change is smaller or equal to a nickel subtract a nickel from change add a coin to count            
        while(change >= nickel)
        {
            change = change - nickel;
            numberOfCoins++;                   
        }
        //while change is smaller or equal to a penny subtract a penny from change add a coin to count                
        while(change >= penny)
        {
            change = change - penny;
            numberOfCoins++;
        }
    }while(change != 0);
    //tells  the program to print the number of coins necessary
    printf("%d\n",numberOfCoins);
}
