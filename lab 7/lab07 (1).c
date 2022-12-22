#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define SIZE 7                       
#define DEBUG 0                       
#define DEBUG2 0                      
#define arr1 3
#define arr2 4



typedef struct binheap {             /* Binary Heap */
  int heap[SIZE];                    /* element 0 in heap is not used */
  int size;
} bin_t;

void insert_heap (bin_t *, int);
void printH(bin_t *h);
/*
AUTHOR: De'Andre Gardener and Blanca Gallego
FILENAME: lab07.c
SPECIFICATION: In this program, it is supposed to read in words from a textfile that then goes into the heap that will then output to a text file with it sorted
FOR: CS 2413 Data Structures Section 002
*/

int main (void) {

    FILE* txt1;
    FILE* txt2;
  int arr[SIZE];
  int tx1[arr1];
  int tx2[arr2];
  bin_t hp = {0};
  hp.size = SIZE;
  
  int i, j, temp;
    txt1 = fopen("text1.txt", "r");
    txt2 = fopen("text2.txt", "r");
  for(i = 0; i<arr1; i++)
    {
      fscanf(txt1,"%d",&tx1[i]);
    }
  for(i = 0; i<arr2; i++)
    {
      fscanf(txt2,"%d",&tx2[i]);
    }
  for(i = 0; i<arr1; i++)
    {
      arr[i] = tx1[i]; 
    }
    for(i = 3, j = 0; i<SIZE; i++, j++)
    {
      arr[i] = tx2[j]; 
    }
    for (i = 0; i < SIZE; i++) {
        for (j = i + 1; j < SIZE; j++) {
            if (arr[i] > arr[j]) {
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
  for(i=0; i< SIZE; i++)
    {
      printf("%d\n",arr[i]);
     
      insert_heap(&hp, arr[i]);
      hp.heap[i] = arr[i];
    }
  printH(&hp);




  return 0;
}

/*
    NAME: insert_heap
    PARAMETERS: bin_t *h, int data
    PURPOSE: this function inserts the data into heap
    PRECONDITION: sends in a number to the heap
    POSTCONDITION: stores the value into the heap
*/
void insert_heap (bin_t *h, int data) {
  int pos,par;
  if (DEBUG) {
    printf ("\ninsert_heap - begin, data = %d heap size is %d\n",
      data,h->size);
  }
  if (h->size < SIZE-1) {
    h->heap[h->size+1] = data;
    h->size += 1;
    pos = h->size;
    par = pos/2;
    int temp;
    while (pos > 1 && h->heap[pos] > h->heap[par]) {
      if (DEBUG) {
        printf("insert_heap - pos = %d par = %d\n",pos,par);
      }
      if (DEBUG2) {
        
        putchar('\n');
      }
      temp = h->heap[pos];
      h->heap[pos] = h->heap[par];
      h->heap[par] = temp;
      pos = par;
      par = pos/2;
    }
  }
  if (DEBUG) {
    printf("insert_heap - pos = %d par = %d\n",pos,par);
    printf ("insert_heap -   end, data = %d heap size is %d\n",
      data,h->size);
  }
}

/*
    NAME: printH
    PARAMETERS: bin_t *h
    PURPOSE: this function prints the heap into the text file
    PRECONDITION: there is a heap with data
    POSTCONDITION: stores the value into the text document
*/



void printH(bin_t *h) 
{
    int filenum;
    FILE * ofp = fopen("merge.txt", "w");
    
    while(h->size > 0) 
    {
        
      fprintf(ofp, "(%d in %d.txt)\n", h->heap[0], filenum);
        
      h->heap[0] = h->heap[h->size - 1];
      h->size--;

    }
    fclose(ofp);
}
/*

Team Member names: Deandre Gardener and Blanca Gallego
De'Andre: main driver, insert

         
Blanca:  printh, insert

insert - code that is slightly modified from original code giving by Dr.Mengel

TEST CASES AND STATUS:

1. example 1.txt, 2.txt, merged.txt built – passed/failed
2. 3<=n<=12 files of sorted integers, merged.txt built – passed/failed
3. one of the m.txt files of sorted integers is empty, merged.txt built – passed/failed
4. one of the m.txt files of sorted integers is missing, merged.txt built – passed/failed

1. Big O of inserting all m integers in files 1.txt to n.txt into a binary min heap of size n is O(mlogn)
2. Big O of the storage requirements for a binary min heap of size n is O(n)
3. How could this program be extended to perform an external file merge sort on one file
   of m unordered integers? You would first have to order the file(sort) and then once it is ordered, 
   the program will run as normal

*/

