#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
/*
AUTHOR: De'Andre Gardener and Blanca Gallego
FILENAME: lab04.c
SPECIFICATION: In this program, it is supposed to read in equations from the text file and then check each equation
               set to see if it has a variable before the equal sign, has an equal sign, and there is a matching
               set of brackets, parenthesis, and braces.
FOR: CS 2413 Data Structures Section 002
*/

typedef struct node  // this struct instantiates the linked list
{ 
    char data; // sets it where the data able to be inputted are char values
    struct node* next; 
} node_t;
void error_id(node_t* stack, char array[50],int lens);
void push(char data, node_t** stack);
void pop(node_t** stack);
/*  NAME: push
    PARAMETERS: char data, node_t** stack
    PURPOSE: The purpose of this function is to take in a set of values from the main function and add
             it to the stack
    PRECONDITION: That there is a value inside the pointer to be added to the stack
    POSTCONDITION: a value will be successfully added to the stack
*/
void push(char data, node_t** stack)
{
    node_t* Node = (node_t*)malloc(sizeof(node_t)); 
    Node -> data = data; 
    Node -> next = *stack;  
    (*stack) = Node;  
}

/*  NAME: pop
    PARAMETERS: node_t** stack
    PURPOSE: The purpose of this function is to remove and free the top of the stack
    PRECONDITION: That there is a value inside the stack
    POSTCONDITION: the top value will have been removed from the stack
*/
void pop(node_t** stack)
{
    if(*stack != NULL)
    {
        node_t* tempPtr = *stack;
        *stack = (*stack) -> next;
        free(tempPtr);
    }
    else
    {
        printf("The stack is empty.\n");
    }
}

/*  NAME: error_id
    PARAMETERS: node_t* stack, char array[50],int lens
    PURPOSE: The purpose of this function is to check if there are any errors within the equations
             that was in the text file
    PRECONDITION: that there is an equation stored in the array and stack
    POSTCONDITION: the error code will successfully be printed
*/
void error_id(node_t* stack, char array[50],int lens)
{
  int error = 0, i = 0;

  if(!(isalpha(array[0]) || array[1] == '='))
  {
    error = 1;
  }
  else if((isalpha(array[0]) && array[1] == '='))
  {
    error = 0;
  }
  else
  {
    while(i < lens-1)
    {
      if(array[i] == '=')
      {
        error = 0;
        break;
      }
      else
      {
        error = 2;
        i++;
      }
    }
  }
  if(stack -> data != NULL)
  {
    error = 3;
  }
  

  printf("Error ID %d on ", error);
  for(i = 0; i< lens; i++)
  {
      printf("%c", array[i]);
  }
  
}

int main() {
  node_t* root = (node_t*)malloc(sizeof(node_t)); // a different way of creating the node
  FILE *fp ;//sets filepointer
  fp = fopen ( "equations.txt", "r" ); //opens file
  char ch; //to set characters in file
  int lens = 0; // to count length of the line in the file
  char equ[50] = {}; //store each equation
  while ((ch = fgetc(fp)) != EOF) // loop that will read each character within the file
  {
    if(ch == '\n')//this will run the error code check when end of line hits
      {
          error_id(root, equ, lens);
          lens = 0;
          printf("\n");
      }
    else if(isspace(ch)) //removes spaces within the equation
    {
      
    }
    else
    {
      //helps to denote when to push and pop into the stack
    if(ch == '(' || ch == '{' || ch == '[')
    {
        push(ch, &root);    
    }

    if(ch == ')' || ch == '}' || ch == ']')
    {
       pop(&root); 
    }
      equ[lens] = ch;
      lens++; 
    }
  }
  }
/*

Team Member names: Deandre Gardener and Blanca Gallego
Deandre: 1. push- modified linked list insert code to insert at the head or in this case top of the stack
         2. main driver - Handcrafted to take in file input and notice when the end of the line hits so that
                         the error_id driver can be called and checked for error
Blanca:  1. pop - modified delete node code to delete the top of the stack
         2.error_id - handcrafted to be called from the main function to be able to check the criteria
                      for being each error case. and will output the error at the end of the call

TEST CASES AND STATUS:
For the test cases, it consistently is able to output errors 0,1 and 2 but has issues with error 3
1. Failed h=5+9*3) is showing no error when should be an error 3
2. Passed
3. Passed
4. Passed

1. Example of a worst-case type of equation that would require many items to be placed
   on the stack would be O(n^2)
2. Big O for determining that n equations of max length m are valid would be O(n*m)
3. Big O of the storage requirements for a stack linked list of size n would be O(n)

*/
  


