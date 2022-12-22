#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max 100

/*
AUTHOR: Deandre Gardener and Blanca Gallego
FILENAME: lab3.c
SPECIFICATION: In this program it is supposed to read in phrases from a text file. From the text file it should store the parts into the nodes of linked list.
                From the list it should sort the nodes into alphabetical order and print into a concordance.txt, from there it should then remove the stop words that are
                inside a file called stops.txt and then end by printing everything in the linked list into concordance_wo_stops.txt
FOR: CS 2413 Data Structures Section 002
*/

typedef struct node // this struct instantiates the linked list
{
  char data[max]; // sets it where the data able to be inputted are char values
  int freq;       //to find occurrance of a certain word in the linked list
  struct node *next;
} node_t;

void print_list(node_t *head);                                               //instantiate print function to print the node
node_t *create_node(char word[max], node_t *ptr);                            //this function creates each node of the linked list
void insert(node_t **head, char word[max]);                                  //instantiates the insert function to insert a value to the end of the linked list
int search_list(node_t *head, char word[max], node_t **prev, node_t **cur);  //instantiate the search_list function which searches the linked list for a certain value
void delete_node(node_t *head, char word[max], node_t **prev, node_t **cur); //this instantiates the delete_node function which will be able to delete the stop words

node_t *create_node(char word[], node_t *ptr)
{
  node_t *newp = (node_t *)malloc(sizeof(node_t));
  strncpy(newp->data, word, strlen(word));
  newp->next = ptr;
  // newp->freq = freq;
  return (newp);
}
/*  NAME: create_node
    PARAMETERS: char word[], node_t *ptr
    PURPOSE: THe purpose of this function is to take in a set of values from the main function and 
    PRECONDITION: That there are values with in the linked list
    POSTCONDITION: This function should print out the strings within the linked list if done properly
*/
void print_list(node_t *head)
{
  printf("\nThe List is:\n");
  node_t *cur = head;
  if (cur == NULL)
    printf("  Empty\n");
  else
  {
    while (cur != NULL)
    {
      printf("  %s\n", cur->data);
      cur = cur->next; // cur = (*cur).next;
    }
  }
}
/*  NAME: print_list
    PARAMETERS: node_t *head
    PURPOSE: The purpose of this function is to print the values within the linked list
    PRECONDITION: That there are values with in the linked list
    POSTCONDITION: This function should print out the strings within the linked list if done properly
*/

void insert(node_t **head, char word[max])
{
  node_t *newp = create_node(word, NULL);
  node_t *cur;
  if (*head == NULL)
  {
    *head = newp;
  }
  else
  {
    cur = *head;
    while (cur->next != NULL)
      cur = cur->next;
    cur->next = newp;
  }
}
/*  NAME: insert
    PARAMETERS: node_t **head, char word[max]
    PURPOSE: It inserts the word at the end of the node.
    PRECONDITION: There must be text to be inserted in. 
    POSTCONDITION: Successfully inserts the string at the end of the node. 
*/
int main(void)
{
  FILE *infile;
  char w[max];

  infile = fopen("text.txt", "r"); //opens file in read mode
  fscanf(infile, "%s", w);         //scans file
  fclose(infile);                  //closes file
  int i;
  char str;

  node_t *head = create_node(&str, NULL); //creates a node
  for (i = 0; i <= strlen(w); i++)        //this section reads a line into the node
  {
    str = w[i];
    insert(&head, &str);
  }
  print_list(head);
}

/*

Team Member names: Deandre Gardener and Blanca Gallego
Deandre: 1.printlist - modified from the original code that was provided to us by Dr.Mengel
         2.main driver - Hand crafted to take in file input and then call the functions required to print
         3.create node - modified from the original code that was provided to us by Dr.Mengel
Blanca:  1.search list - modified from the original code that was provided to us by Dr.Mengel was a joint issue due to many issues involved
         2.Insert - modified from the original code that was provided to us by Dr.Mengel
         3.create node - modified from the original code that was provided to us by Dr.Mengel was a joint issue due to many issues involved
TEST CASES AND STATUS:
For the test cases and status due to many errors in the code these will all fail to run
1.Failed
2.Failed
3.Failed
4.Failed
5.Failed
6.Failed

1. Example of a worst case for inserting n words into an ordered linked list would be if the linked list was fully out of order because it would require the maximum amount of passes needed in order to put the linked list in order
2. The worst case for inserting n words into an ordered linked list is O(n)^2.
3. The Big O of the storage requirements for a linked list of size n would be n because as size increases so will the storage required, thus being a direct relation

*/