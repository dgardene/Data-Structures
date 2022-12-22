
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define KEYS 2                   /* max number of keys in a 2-3 tree node */
#define DEBUG 0                  /* print debug statements if 1, 0 otherwise */

/*
AUTHOR: De'Andre Gardener and Blanca Gallego
FILENAME: lab06.c
SPECIFICATION: In this program, it is supposed to read in words from a textfile that then is inserted into a 2-3 tree that will then read out certain statistics and find a search word
FOR: CS 2413 Data Structures Section 002
*/

typedef struct data_node {       
  char key[40];
  int count;
} data_t;

typedef struct node {              /* 2-3 tree node */
  int num_keys;                    /* number of keys in the data array */
  int count;
  data_t data[KEYS+1];             /* data array */
  struct node *tree_p[KEYS+1+1];   /* pointer array */
} tree_t;

void print_23tree (tree_t *);         /* recursive helper function to print a 2-3 tree */
void recur_print_23tree (tree_t *);   /* recursive function to print a 2-3 tree */
tree_t * search_23tree (tree_t *, char word[]);  /* recursive search function to find an element in a 2-3 tree */
tree_t * create_node ();                 /* creates and initializes an empty 2-3 tree node */
void insert (tree_t **root, data_t val);   /* recursive helper function for recur_insert function */
void recur_insert (tree_t **root, data_t val, int *split, data_t *mid, tree_t **newp); /* recursively insert a key into a 2-3 tree */
void print_tree (tree_t *tree);               /* helper to recursive bst print */
void recur_print (tree_t *tree, int level);   /* print the bst recursively and addresses */
tree_t *  concordance(tree_t *root, int length);
void print_stats (tree_t *tree, int size);
int height (tree_t *tree, int level);
int node_count(tree_t *tree, int level, int vals);


int main(void) {
  printf("\n2-3 Tree Insertion...\n");           /* insert into an empty 2-3 tree */
  tree_t *root = NULL;
  data_t aa = {"NULL"};

    int i = 0;
    char str[100];
    FILE* fp;
    fp = fopen("test.txt", "r");

    while(fgets(str, 100, fp) != NULL)
    {
        ++i;
        printf("%s",str);
        strcpy(aa.key, str);
        insert(&root, aa);
    }
    
    fclose(fp); 
    concordance(root, i);
    
   print_tree(root);
   print_stats(root, i);
  
  return 0;
}

/*  NAME: insert
    PARAMETERS: tree_t **root, data_t val
    PURPOSE: create a new tree node and insert val and also checks to see if word exists
    PRECONDITION: That there is a string being sent in
    POSTCONDITION: populates a node with in the tree
*/

void insert (tree_t **root, data_t val) {
  data_t mid;
  int split;
  tree_t *newp;
  tree_t *ptr;
  int i;
  if (*root == NULL) {
    if (DEBUG) printf("\ninsert - empty tree - val = %s\n",val.key);
    newp = create_node();
    newp->data[0] = val;
    newp->num_keys = 1;
    *root = newp;
  }
  else {
    if (search_23tree(*root, val.key) == NULL) {
      split = 0;
      if (DEBUG) printf("\ninsert - non-empty tree before recur call - val = %s\n",val.key);
      recur_insert (root,val,&split,&mid,&ptr);
      if (DEBUG) printf("insert - non-empty tree after recur call - val = %s  split = %d\n",val.key,split);
      if (split) {
        newp = create_node();
        newp->data[0] = mid;
        newp->tree_p[0] = *root;
        newp->tree_p[1] = ptr;
        newp->num_keys = 1;
        *root = newp;
      }
    }    
  }
}

 
/*  NAME: recur_insert
    PARAMETERS: tree_t **root, data_t val, int *split, data_t *mid, tree_t **newp
    PURPOSE: traverses the tree to a leaf node to insert val and propagates the mid key and new node back up the tree
    PRECONDITION: That there is a string being sent in
    POSTCONDITION: populates a node with in the tree
*/
void recur_insert (tree_t **root, data_t val, int *split, data_t *mid, tree_t **newp) {
  int i,j;
  tree_t *np;
  if ((*root)->tree_p[0] == NULL) {    // insert val in leaf node
    if (DEBUG) printf("recur_insert - insert in leaf - val = %s  (*root)->data[0].key = %s\n",val.key,(*root)->data[0].key);
    for (i = (*root)->num_keys; i > 0 && strcmp(val.key, (*root)->data[i-1].key) < 0; i--) {
      (*root)->data[i] = (*root)->data[i-1];
      (*root)->tree_p[i+1] = (*root)->tree_p[i];
    }
    (*root)->data[i] = val;
    (*root)->tree_p[i+1] = NULL;
    (*root)->num_keys++;
    if (DEBUG) {
      printf("recur_insert - after leaf insert\n");
      for (j=0; j < (*root)->num_keys; j++) {
        printf("  %s\n",(*root)->data[j].key);
        printf("  %p\n",(*root)->tree_p[j]);
      }
      printf ("  %p\n",(*root)->tree_p[j]);
    }
    if ((*root)->num_keys == KEYS+1) {     // split leaf node
      if (DEBUG) printf("recur_insert - split leaf node\n");
      *split = 1;
      *newp = create_node ();
      (*newp)->data[0] = (*root)->data[KEYS];
      (*newp)->num_keys = 1;
      *mid = (*root)->data[1];
      (*root)->num_keys = 1;
    }
  }
  else {               
    if (DEBUG) printf("recur_insert - internal - before recur - val = %s  (*root)->data[0].key = %s\n",val.key,(*root)->data[0].key);
    for (i = 0; i < (*root)->num_keys && strcmp(val.key, (*root)->data[i].key) > 0; i++);
    
    recur_insert (&((*root)->tree_p[i]), val, split, mid, newp);
    if (DEBUG) printf("recur_insert - internal - after recur - val = %s  (*root)->data[0].key = %s  split = %d\n",val.key,(*root)->data[0].key,*split);
    if (*split) {   
      if (DEBUG) printf("recur_insert - splitting - mid = %s  (*root)->num_keys = %d\n",(*mid).key,(*root)->num_keys);
      *split = 0;
      
      for (i = (*root)->num_keys; i > 0 && strcmp(mid->key, (*root)->data[i-1].key) < 0; i--) {
        
      (*root)->data[i] = (*root)->data[i-1];
      (*root)->tree_p[i+1] = (*root)->tree_p[i];
      }
      (*root)->data[i] = *mid;
      (*root)->tree_p[i+1] = *newp;
      (*root)->num_keys++;
      if (DEBUG) {
        printf("recur_insert - after internal insert\n");
        for (j=0; j < (*root)->num_keys; j++) {
          printf("  %s\n",(*root)->data[j].key);
          printf("  %p\n",(*root)->tree_p[j]);
        }
        printf ("  %p\n",(*root)->tree_p[j]);
      }
      if ((*root)->num_keys == KEYS+1) {
        *split = 1;
        *newp = create_node ();
        (*newp)->data[0] = (*root)->data[KEYS];
        (*newp)->tree_p[0] = (*root)->tree_p[2];
        (*newp)->tree_p[1] = (*root)->tree_p[3];
        (*newp)->num_keys = 1;
        *mid = (*root)->data[1];
        (*root)->num_keys = 1;
      }
    }
  }
}


/*  NAME: create_node
    PARAMETERS: none
    PURPOSE: The purpose of this function is to create a node 
    PRECONDITION: That there is a string being sent in
    POSTCONDITION: This function should create a node size for the word
*/
tree_t * create_node () {
  tree_t *newp = (tree_t *) malloc (sizeof(tree_t));
  int i;
  for (i = 0; i < KEYS; i++) {
    strcpy((char *) &newp->data[i],"");
    newp->tree_p[i] = NULL;
  }
  newp->tree_p[i] = NULL;
  newp->num_keys = 0;
  return(newp);
}

 
/*  NAME: search_23tree
    PARAMETERS: tree_t *root, char word[]
    PURPOSE: The purpose of this function is to search through the 2-3 tree
    PRECONDITION: there is data within the tree and you have a search word
    POSTCONDITION: The function will return if the word was found or not
*/
tree_t * search_23tree (tree_t *root, char word[]) {
  tree_t *p = NULL;
  if (root != NULL) {
    int i;
    for (i = 0; i < root->num_keys && strcmp(word, root->data[i].key) > 0; i++);  
    
    if (i < root->num_keys && strcmp(word, root->data[i].key) == 0) {      
      p = root;
      p->data[0].count += 1;
    }
    else
      p = search_23tree (root->tree_p[i], word);                
  }
  return (p);
}

/*  NAME: print_tree
    PARAMETERS: tree_t *tree
    PURPOSE: The purpose of this function is to call recur_print
    PRECONDITION: there is data within the tree
    POSTCONDITION: call recur_tree to print tree
*/
void print_tree (tree_t *tree) {
  printf("\nThe 2-3 tree is:\n");
  recur_print(tree,0);
}

/*  NAME: recur_print
    PARAMETERS: tree_t *tree, int level
    PURPOSE: The purpose of this function is to print the 2-3 tree
    PRECONDITION: there is data within the tree
    POSTCONDITION: print the tree
*/

void recur_print (tree_t *tree, int level) {
  int i;
  if (tree != NULL) {
    for (i = 0; i < level; i++) putchar(' ');
    printf("Tree Node %p:\n",tree);
    for (i = 0; i < level; i++) putchar(' ');
    printf("  Number of Keys: %d\n",tree->num_keys);
    for (i = 0; i < level; i++) putchar(' ');
    printf("  Keys: ");
    for (i = 0; i < tree->num_keys; i++) printf("%s ",tree->data[i].key);
    putchar('\n');
    for (i = 0; i < level; i++) putchar(' ');
    printf("  Ptrs: ");
    for (i = 0; i <= tree->num_keys; i++) printf("%p ",tree->tree_p[i]);
    putchar('\n');
    for (i = 0; i <= tree->num_keys; i++)
    {
      recur_print (tree->tree_p[i],level+1);
    }
  }
}

/*  NAME: concordance
    PARAMETERS: tree_t *root, int length
    PURPOSE: The purpose of this function is to get the frequency of each word and store in file
    PRECONDITION: there is data within the tree
    POSTCONDITION: print to file
*/
tree_t *  concordance(tree_t *root, int length)
{

    char str[100], comp[100];
    int count = 1;
    FILE *fp = fopen("concordance.txt", "a+");
    FILE *fr = fopen("test.txt", "r");

    while(fgets(str, 100, fr) != NULL)
    {
        fprintf(fp, "%s %d\n", str, root->count);
    }

    fclose(fp);    
}

/*  NAME: print_stats
    PARAMETERS: tree_t *tree, int size
    PURPOSE: The purpose of this function is to print out the stastics of the 2-3 Tree
    PRECONDITION: there is a 2-3 tree
    POSTCONDITION: The function will print out the statistics of the tree
*/

void print_stats (tree_t *tree, int size)
{
    char words[20] = "test";
    tree_t* temp = search_23tree(tree, words);
    int tree_height = height(tree, 0);
    int nodes = node_count(tree, 0, 0);
    printf("\n%p\n", temp);
    printf("Tree Check:\n");
    printf("\tTree Height: %d\n", tree_height);
    printf("\tTree Size : %d nodes\n", nodes);
    if(temp == NULL)
    {
        printf("\t%s is not found\n", words);
    }
    else
    {
        printf("\t%s is found\n", words); 
    }
}

/*  NAME: height
    PARAMETERS: tree_t *tree, int level
    PURPOSE: The purpose of this function is to get the height of the tree 
    PRECONDITION: there is a 2-3 tree 
    POSTCONDITION: returns the height of the tree
*/

int height (tree_t *tree, int level)
{
    
    if(tree == NULL)
    {
        return level;
    }
    return height(tree->tree_p[0],level+1);
}

/*  NAME: node_count
    PARAMETERS: tree_t *tree, int level, int vals
    PURPOSE: The purpose of this function is to get the node count of the function
    PRECONDITION: there is a 2-3 tree 
    POSTCONDITION: returns the amount of nodes of the tree
*/

int node_count(tree_t *tree, int level, int vals)
{
    if(tree == NULL)
    {
        return vals + 1;
    }
    for (int i = 0; i < level+1; i++)
    {
        vals++;
    }
    return node_count(tree->tree_p[0],level+1, vals);
}
/*

Team Member names: Deandre Gardener and Blanca Gallego
De'Andre: 1. insert - modified insert function to aid in inserting strings
          2. main driver - Built tor intake from word file
          3. search_23tree - modified to be able to search for certain words
          4. concordance - built to print words into file with the frequency
          5. recur_print - modified to print the tree
          6. recur_print_23tree - modified to print strings
         
Blanca:  1. height - created in order to find the height of the tree
         2. print_stats - a single function to make all the function calls and print the statistics
         3. Create_node - modified to create node for strings
         4. node_count - created to count the amount of nodes
         5. print_tree - modified to print tree
         6. recur_insert - modified to insert strings into the tree
         


TEST CASES AND STATUS:
For all the test cases, it is able to find a keyword if it exists, but concordance files are unable to be made
1. test.txt – passed
2. test1.txt with one word – passed
3. empty.txt – passed
4. textFile.txt with > 500 total words – passed

1. The worst case for inserting n words into a 2-3 tree would be O(n)
2. Big O of the best case for inserting n words into a 2-3 search tree would be O(logn)
3. Big O of the storage requirements for 2-3 search tree with n keys is O(n)
4. For the example text.txt file, the tree height is 3. What is the minimum possible height?
   The minimum possible height would be a height of 1

*/