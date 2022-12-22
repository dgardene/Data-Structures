#include <stdio.h>
/*
 AUTHOR: De'Andre Gardener
 FILENAME: problem_2.c
 SPECIFICATION: The problem in this assignment is that there is a text file with x and y coordinate points that needs to be 
 stored into data structures in order to be used to solve for both slope and intercept.
 FOR: CS 2413 Data Structures Section 002
*/
int main()
{
    FILE *infile;//pointer for file reading
    double x[4], y[4];//arrays to store x and y components from file
    
    double xk = 0, yk = 0, x2k = 0, xkyk = 0, m, b;//variables for the calculation solving
    
    infile = fopen("zone.txt", "r");//opens the text file in read mode
    for(int i = 0; i<4; i++)
    {
        fscanf(infile, "%lf %lf", &x[i], &y[i]);//scans the text saving the values into the x and y arrays
    }
    
    for(int i = 0; i<4; i++)
    {
        xk += x[i];//sums up all x values in the array
        yk += y[i];//sums up all y values in the array
        x2k += (x[i] * x[i]);//squares and sums up each value of x
        xkyk += (x[i] * y[i]);//takes the sum of each x*y point
    }

    m = ((yk * xk) - 4 * xkyk)/((xk * xk) - (4 * x2k));//computes the ozone-mix-ratio slope
    b = ((xk * xkyk) - (x2k * yk))/((xk * xk) - (4 * x2k));//calculates the intersection point

    printf("Range of altitudes in km: %.0lf to %.0lf \n", x[0], x[3]);//prints the range this test was
    printf("Linear Model: ozone-mix-ratio = %.2lf * altitude + %.1lf", m, b);//prints out the slope and point
    fclose(infile);
}
