/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    int start = 0;
    int end = n - 1; // important (start counting from 0)
    int mid = (start + end) / 2;

    while (start <= end)
    {
        if (values[mid] == value)
            return true;
        else if (value < values[mid])
        {
            end = mid - 1;
            mid = (start + end) / 2;
        }
        else if (value > values[mid])
        {
            start = mid + 1;
            mid = (start + end) / 2;
        }
        else 
            break;
  }
  return false;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    int v = n;
    // TODO: implement an O(n^2) sorting algorithm
   for(int i = 1; i < v-1; i++)
   {
        int min = i;
        for(int j = i + 1; j < v; j++)
        {
            if(values[j] < values[min])
            {
                min = j;
            }
            if(min != i)
            {
                int temp = values[min];
                    values[min] = values[i];
                    values[i] = temp;
            }
        }
   }  
    return ;
}
