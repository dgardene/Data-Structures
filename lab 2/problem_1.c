/*
 AUTHOR: De'Andre Gardener
 FILENAME: problem_1.c
 SPECIFICATION: In this program it takes in a 2D array that then finds the peak values throughout the array which is determined by a center value being bigger than its N,E,S,W values around it
 FOR: CS 2413 Data Structures Section 002
*/
#include <stdio.h>
#define row 6
#define column 7
void peak(int arr[row][column]);
int main()
{
   int array[row][column] = 
                            {{5039, 5127, 5238, 5259, 5248, 5310, 5299},
                             {5150, 5392, 5410, 5401, 5320, 5820, 5321},
                             {5290, 5560, 5490, 5421, 5530, 5831, 5210},
                             {5110, 5429, 5430, 5411, 5459, 5630, 5319},
                             {4920, 5129, 4921, 5821, 4722, 4921, 5129},
                             {5023, 5129, 4822, 4872, 4794, 4862, 4245}};//Initialize 2D Array
                             
    peak(array);
    return 0;
}

/* NAME: peak
 PARAMETERS: arr[row][column]
 PURPOSE: The function computes and prints the number of peaks in the 2D as well as the locations
 PRECONDITION: There should be a 2D array that gets sent in to the parameters 
 POSTCONDITION: Once the function ends it should have printed the number of peaks as well as the location of each one
*/
void peak(int arr[row][column])
{
    int total = 0;
    //this first nested for loop goes through the array and counts up the total number of peaks
    for(int i = 0; i< row; i++)
    {
        for(int j = 0; j < column; j++)
        {
            if(arr[i-1][j] < arr[i][j] && arr[i+1][j] < arr[i][j] && arr[i][j-1] < arr[i][j] && arr[i][j+1] < arr[i][j])//checks each condition to see if it satisfies what a peak value is
            {
                total++;//counts the total number of peaks
            }
        }
    }

    printf("%d peaks found: \n",total);
 
 //This nested loop computes the location of the peaks   
    for(int i = 0; i< row; i++)
    {
        for(int j = 0; j < column; j++)
        {
            if(arr[i-1][j] < arr[i][j] && arr[i+1][j] < arr[i][j] && arr[i][j-1] < arr[i][j] && arr[i][j+1] < arr[i][j])//checks each condition to see if it matches what is needed to be cosidered a peak
            {
                printf("Location at row %d and column %d\n", i, j);
            }
        }
    }

}
/*Output
3 peaks found:
Location at row 2 and column 1
Location at row 2 and column 5
Location at row 4 and column 3

Big O storage complexity would be O(n) due to working with the single 2D array as well as 
if time complexity stays low then the space required for the time would also be low.

Big O time complexity would be O(n) due to it going and checking a certain value with the 
values next to it, but it is never actually going back to that value
*/




