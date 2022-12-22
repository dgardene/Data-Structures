/*
 AUTHOR: De'Andre Gardener
 FILENAME: problem_1.c
 SPECIFICATION: In this program it takes in 3 user inputted numbers, and from those numbers it is then sorted from smallest to greatest value
 FOR: CS 2413 Data Structures Section 002
*/
#include <stdio.h>
void fun1(double smp, double lgp); // declares a function
int main (void) 
{
  double num1, num2, num3; //instantiating numbers for the user input
  printf("Enter 3 numbers separated by blanks> ");
  scanf("%lf%lf%lf",&num1,&num2,&num3);// gets input for 3 values
  fun1(num1,num2);//call to the sorting function
  fun1(num1,num3);//call to the sorting function
  fun1(num2,num3);//call to the sorting function
  printf("The numbers are: %.2f %.2f %.2f\n", num1, num2, num3);
  return (0);
}
/* NAME: fun1
 PARAMETERS: smp, lgp
 PURPOSE: The function compares two numbers to see which if they are in a certain order and if it is not it will then flip their places to put them in the right order
 PRECONDITION: both values being entered into the function should be pointer values and the values should also be double values.
 POSTCONDITION: once the function is done it will have changed the values of 2 variables to be least to greatest if the if statement was met inside the function
*/
void fun1 (double smp, double lgp) 
{
  double temp;//value to store a value temporarily
  if (smp > lgp) //compare condition to see if a value is smaller than the other
{
  temp=smp;//sets smp value to temp
  smp=lgp;//sets lgp to smp
  lgp=temp;//sets temp to lgp
}
}
//Once formatting of the code is done, when you run it, the program is supposed to take user input of 3 numbers and then it will put the numbers in ascending order.
//When both * and & signs are removed from the code, instead of the code returning the values in ascending order, they will just output what was originally inputted.