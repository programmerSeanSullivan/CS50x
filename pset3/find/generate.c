/***************************************************************************
 * generate.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Generates pseudorandom numbers in [0,LIMIT), one per line.
 *
 * Usage: generate n [s]
 *
 * where n is number of pseudorandom numbers to print
 * and s is an optional seed
 ***************************************************************************/
 
// standard libraries
#define _XOPEN_SOURCE
#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// constant
#define LIMIT 65536

int main(int argc, string argv[])
{
    //if two user input commands are not entered after ./generate return 1 and prompt user proper input.
    if (argc != 2 && argc != 3)
    {
        printf("Usage: generate n [s]\n");
        return 1;
    }

    //take the number thats represented as a string and translates it into an int through atoi() function
    int n = atoi(argv[1]);

    //if there is second user input number generate a random 48 bit integers
    if (argc == 3)
    {
        srand48((long int) atoi(argv[2]));
    }
    else
    {
        srand48((long int) time(NULL));
    }

    //generates random numbers based on user input first it generates a number from .0 to 1 and multiplies it by the limit
    for (int i = 0; i < n; i++)
    {    
        printf("%i\n", (int) (drand48() * LIMIT));
    }

    // success
    return 0;
}
