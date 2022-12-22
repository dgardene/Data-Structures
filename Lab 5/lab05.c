#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
/*
AUTHOR: De'Andre Gardener and Blanca Gallego
FILENAME: lab05.c
SPECIFICATION: In this program, it is supposed to read in words from a textfile that then is inserted into a binary
               search tree that will then read out certain statistics and find a search word
FOR: CS 2413 Data Structures Section 002
*/

typedef struct node
{
    char* data;
    struct node* leftp;
    struct node* rightp;
} node_t;

node_t* create_node(char* data); //function to create node
node_t* insert_node(node_t* tree, char* data);   // function to insert a string into a node
node_t * search (node_t *tree, char* find);      // function to recursively search in the tree
int height(node_t *tree);   //gets the height of the binary tree
void print_stats (node_t *tree, int size, char words[30]);               // prints the information of the tree



int main (void)
{
    node_t *root = NULL;
    char word1[31] = {"land"};
    char word2[31] = {"test"};

    int i = 0;
    char str[100];
    FILE* fp;
    fp = fopen("test1.txt", "r");

    while(fgets(str, 100, fp) != NULL)
    {
        ++i;
        root = insert_node(root, str);
    }
    print_stats(root, i, word1);
    print_stats(root, i, word2);
  
}

/*  NAME: create_node
    PARAMETERS: char* data
    PURPOSE: The purpose of this function is to create a node 
    PRECONDITION: That there is a string being sent in
    POSTCONDITION: This function should create a node size for the word
*/
node_t* create_node(char* data) {
    // Creates a new node
    node_t* node = (node_t*) malloc (sizeof(node_t));
    node->data = strdup(data);
    node->leftp =NULL; 
    node->rightp = NULL;
    return node;
}

/*  NAME: insert_node
    PARAMETERS: node_t* tree, char* data
    PURPOSE: The purpose of this function is to store the string into a node 
    PRECONDITION: The node is defined, there is a word to be stored
    POSTCONDITION: The string should be stored into a node in the BST
*/
node_t* insert_node(node_t* tree, char* data) // inserting nodes!
{
    if(tree == NULL)//checks if tree is empty
    {
        return create_node(data);
    }
    else if(strcmp(data, tree->data) < 0)
    {
        tree->leftp = insert_node(tree->leftp, data);
    }
    else if(strcmp(data, tree->data) > 0)
    {
        tree->rightp = insert_node(tree->rightp, data);
    }

    return tree;

}

/*  NAME: Height
    PARAMETERS: node_t *tree
    PURPOSE: THe purpose of this function is to store the string into a node 
    PRECONDITION: there is data within the tree
    POSTCONDITION: The function will return the size of the tree
*/
int height(node_t *tree)
{
if(tree != NULL)//if the tree has values it will return a height
    {

        int left_side = height(tree -> leftp);
        int right_side = height(tree -> rightp);
        if(left_side > right_side)
        {
            return left_side + 1;
        }
        else
        {
            return right_side + 1;
        }
    }
}

/*  NAME: search
    PARAMETERS: node_t *tree, char* find
    PURPOSE: The purpose of this function is to store the string into a node 
    PRECONDITION: there is data within the tree and you have a search word
    POSTCONDITION: The function will return if the word was found or not
*/
node_t * search (node_t *tree, char* find)
{
  if (tree == NULL || strcmp(find, tree->data) == 0)
  {
      return tree;
  }
  else if (strcmp(find, tree->data) < 0)
  {
      return search(tree->leftp, find);
  }
  else
  {
      return search(tree->rightp,find);
  }
}


/*  NAME: print_stats
    PARAMETERS: node_t *tree, int size
    PURPOSE: The purpose of this function is to print out the stastics of the BST and search key
    PRECONDITION: there is a BST made and it has been loaded
    POSTCONDITION: The function will print out the statistics of the tree
*/
void print_stats (node_t *tree, int size, char words[30])
{
    
    node_t* temp = search(tree,words);
    printf("Tree Check:\n");
    printf("\tTree Height: %d\n", height(tree));
    printf("\tTree Size : %d nodes\n", size);
    if(temp == NULL)
    {
        printf("\t%s is not found\n", words);
    }
    else
    {
        printf("\t%s is found\n", words); 
    }
}

/*

Team Member names: Deandre Gardener and Blanca Gallego
De'Andre: 1. insert- modified linked list insert code to be able to compare the word and send it either to the left or right
                    side of a BST
         2. main driver - Built to take in file input and then call the insert function to put each word in the BST
         3. search - Built to take in a keyword then traverse through the tree to see if it exists
         
Blanca:  1. height - created in order to find the height of the tree
         2. print_stats - a single function to make all the function calls and print the statistics
         3. Create_node - modified code from linked list to work with the binary Tree

TEST CASES AND STATUS:
For all the test cases, it is able to find a keyword if it exists, but concordance files are unable to be made
1. test.txt – passed
2. test1.txt with one word – passed
3. empty.txt – passed
4. textFile.txt with > 500 total words – passed

1. Example of a best case for inserting n words into a binary search tree would be a perfectly balanced tree
2. Big O of the best case for inserting n words into a binary search tree is O(logn)
3. Big O of the storage requirements for a binary search tree of size n is O(n)

*/

