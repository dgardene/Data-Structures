#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define doc_count 1
#define max 100
#define SIZE 50000


typedef struct hash_element {
    int collision;
    char key[max];
    char* value;
  
} hash_element_t;

void clean_word(char* word);
hash_element_t * make_hash_table (int size);
unsigned long h(char* key, int table_size);
int probe (char* key, int table_size, int i);
int linear_probe (hash_element_t *table, int table_size, char* key, int insert);
void hash_random_numbers_into_table (hash_element_t *table, int table_size, int num, int seed);
void insert(hash_element_t* table, char* key, char* value, int table_size);
void print_table(hash_element_t *table);


/*
AUTHOR: De'Andre Gardener and Blanca Gallego
FILENAME: lab11.c
SPECIFICATION: In this program the purpose is to load files into a hash_table which 
               then can be searched to show if a word is found and if so in which text documents
FOR: CS 2413 Data Structures Section 002
*/
int main()
{
    hash_element_t *table;
    table = make_hash_table(SIZE);
    FILE* ptr;
    char ch;
    int i;
    char filename[15];
    char word[50];

    for (i = 1; i <= doc_count; i++) {
        snprintf(filename, 14, "document%d.txt", i);
        printf("%s\n", filename);
        
        ptr = fopen(filename, "r");
        if(!ptr){
            printf("File could not be opened\n");
        }
        else{
            while (fscanf(ptr, "%s", word) != EOF)
            {
                clean_word(word);
                insert(table, word, filename, SIZE);
            }
      }
   }
    print_table(table);
}

/*
    NAME: clean_word
    PARAMETERS: char* word
    PURPOSE: the purpose of this function is to make the words lower case and remove puncutation
    PRECONDITION: there is a word to be cleaned
    POSTCONDITION: word will be lowercased and punctuation removed
*/
void clean_word(char* word)
{
    int i,j;
    for(i = 0, j = 0; word[i]; i++)
    {
        if(ispunct(word[i]))
        {
            word[j] = '\0';
        }
        if(isalpha(word[i]))
        {
            word[j++] = tolower(word[i]);
        }
    }
    word[j] = '\0';
}
/*
    NAME: make_hash_table
    PARAMETERS: int size
    PURPOSE: the purpose of this function is to allocate the right amount of storage to the hash_table
    PRECONDITION: there is a size for the table to made with
    POSTCONDITION: hash table is created
*/
hash_element_t * make_hash_table (int size) {
  return ((hash_element_t *) calloc (size,sizeof(hash_element_t)));
}

/*
    NAME: h
    PARAMETERS: char* key, int table_size
    PURPOSE: this is the hash function which is used to aid in finding an index spot for a certain key and lower collision
    PRECONDITION: there is a key being sent in
    POSTCONDITION: returns back the index
*/
unsigned long h(char* key, int table_size) {
    int i = 0;
    for (int j=0; key[j]; j++)
        i = i + key[j];
    return i % table_size;
}

/*
    NAME: insert
    PARAMETERS: hash_element_t* table, char* key, char* value, int table_size
    PURPOSE: this is meant to insert the key and value into the hash table
    PRECONDITION: there is a key being sent in
    POSTCONDITION: inserted into the hash table
*/
void insert(hash_element_t* table, char* key, char* value, int table_size)
{
    int index;
    index = linear_probe(table, table_size, key, 1);
    
    if(/*table[index].key != key*/(strcmp(table[index].key, key) != 0))
    {
        strcpy(table->key, key);
        
        // strcpy(table->value, value);
    }
}

/*
    NAME: linear_probe
    PARAMETERS: hash_element_t *table, int table_size, char* key, int insert
    PURPOSE: The purpose of this function is to aid in reducing collision
    PRECONDITION: there is a hash table created and a value needing to be inserted
    POSTCONDITION: successfully finds a position suitable and returns back that index
*/
int linear_probe (hash_element_t *table, int table_size, char* key, int insert) {
  int i, found = 0, index;
  for (i = 0; i < table_size && !found; i++) 
  {
    index = probe (key, table_size, i);
    if (table[index].key == 0 || (strcmp(table[index].key, key) == 0))
      found = 1; 
    else if ((strcmp(table[index].key, key) != 0) && insert)
      table[index].collision = 1;
  }
  return (index);
}

/*
    NAME: probe
    PARAMETERS: char* key, int table_size, int i
    PURPOSE: This function works as an aid in using the hash function
    PRECONDITION: there is a value that needs hashing
    POSTCONDITION: calls hash function and successfully returns back an index to the linear_probe
*/
int probe (char* key, int table_size, int i) {
  return ((h(key,table_size)) % table_size);
}

/*
    NAME: print_table
    PARAMETERS: hash_element_t *table
    PURPOSE: This function prints out the hash table
    PRECONDITION: there is a hash table with values
    POSTCONDITION: prints out the hash table
*/
void print_table(hash_element_t *table)
{
   for(int i = 0; i<SIZE; i++)
   {
       if(table->key[i])
       {
           printf("Index: %d, key: %s, Value: %s\n", i, table[i].key, table[i].value);
       }
   }
}
/*

Team Member names: Deandre Gardener and Blanca Gallego
De'Andre: linear_probe, insert, main

         
Blanca:  print_table, probe, h, clean_word



TEST CASES AND STATUS:

1. 1 document excerpt file and hash table – passed/failed
2. 2 to 12 document excerpt files and hash table – passed/failed
3. searching for words in the hash table – passed/failed
4. searching for words not in the hash table – passed/failed
5. searching for words in and not in the hash table – passed/failed


1. Give at least two hash table sizes that are a power of 2, such as 1024, and how many
collisions occurred after hashing the words from the 12 excerpt document files.

1024 - 365 collisions
2048 - 182 collisions

2. Give at least two hash table sizes that are a prime number, such as 1031, and how many
collisions occurred after hashing the words from the 12 excerpt document files.

1031 - 372 collisions
1033 - 369 collisions

3. What size for the hash table did you choose and why? to get a hash table size we can do 1.5 * max number of keys which would be about 2539

4. What hash function did you choose and why? The division method was chosen because of its due to its
                                              speed as well as the simplicity of there only needing to 
                                              do a single operation to be done

5. What is the largest primary cluster that occurred in the hash table you chose? the largest primary cluster was 25

6. What is the overall order of the program (itemize each significant part and show the
total rather than give one order)? Use m for the number of excerpt document files, n
for the approximate number of words in each file, and q for the number of queries.
                                                                                    hash_table_insertion is O(n*m), query is O(q*n)
                                                                                    total is O((m*q)*n)
                                                                                    
7. What is the big O of the overall storage requirements for the program (itemize each
significant storage piece used for the data and show the total rather than give just one
order)? Use m for the number of excerpt document files, n for the approximate number
of words in each file, and q for the number of queries.
                                                        hash_table_insertion is O(n*m), query is O(q)
                                                        Total is (q+(n*m))
                                                        
*/