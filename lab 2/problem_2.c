
#include <stdio.h>
#define top 100 //the max length for the string array
int search_sub(char string[top], char substring[top]);

/*
 AUTHOR: De'Andre Gardener
 FILENAME: problem_2.c
 SPECIFICATION: In this program it takes in a string and substring value and searchs through the string to see if it can find the substring inside
 FOR: CS 2413 Data Structures Section 002
*/
int main()
{
    char main[top], sub[top];//the main string and substring variable initialization
    int results;//results initialization for the function
    
    printf("Enter a String of any kind ");
    gets(main);
    
    printf("Give a search substring ");
    gets(sub);
    
    
    results = search_sub(main, sub);//call to the function which results gets stored in variable
    
    if (results == -1)//check the value of the result from the function
    {
        printf("Not present");
    }
    else
    {
        printf("Search for '%s' in '%s' - location %d", sub, main, results);
    }
    return 0;
}
/* NAME: search_sub
 PARAMETERS: string, substring
 PURPOSE: The function computes the position at which the substring is within the string
 PRECONDITION: Both of the parameters should be string array values that were inputted by the user at the start of the program
 POSTCONDITION: when the function returns it will return the position at which the substring matched the string or 
                return a -1 to say that the substring was not found in the string
*/
int search_sub(char string[top], char substring[top])
{
    int s1 = 0, s2 = 0;//variables for the length of each string
    
    while(string[s1] != '\0')//gets the length of the string
    {
        s1++;
    }
    while(substring[s2] != '\0')//gets the length of the substring
    {
        s2++;
    }
    
    int i, j, m = s1 - s2;//subtracts the 2 strings from eachother

    for (i = 0; i <= m; i++) 
    {
 
        for (j = 0; j < s2; j++)
        {
            if (string[i + j] != substring[j])//traverses through the string to see if it matches substring
            {
                break;
            }
        }
        if (j == s2)//elements match equals the subarray it will return the index its found
        { 
            return i;
        }
    }
 
    return -1;//if there was no match returns -1

}
//Search for 'caccoc' in 'cacco cacco caccoc cacco' - location 12
//In worst case this would be O(n^4) due to it having to make more than one loop around as it covers 2 loops
//as well as it having 2 extra loops for counting the string lengths
//The best case would be O(n) because it will only have to travel through the phrase once if it were perfectly optimized
    
    




