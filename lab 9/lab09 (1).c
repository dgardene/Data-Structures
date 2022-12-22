#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define max 150
#define testfile "graph.txt"

struct AdjListNode
{
    char dest[max];
    int weight;
    struct AdjListNode* next;
};

struct AdjList
{
    struct AdjListNode *head;
};

struct Graph
{
    int vert;
    struct AdjList* array;
};

/*
    NAME: newAdjListNode
    PARAMETERS: char dest[], int weight
    PURPOSE: this function creates a new node for adjacency list
    PRECONDITION: there is a destination value and a weight
    POSTCONDITION: creates a new node for the adjacency list
*/
struct AdjListNode* newAdjListNode(char dest[], int weight)
{
    struct AdjListNode* newNode = (struct AdjListNode*) malloc(sizeof(struct AdjListNode));
    strcpy(newNode->dest, dest);
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}

/*
    NAME: createGraph
    PARAMETERS: int v
    PURPOSE: this function creates the graph
    PRECONDITION: there is a denoted number of vertices
    POSTCONDITION: creates a graph with the correct number of vertices
*/
struct Graph* createGraph(int v)
{
    struct Graph* graph = (struct Graph*) malloc(sizeof(struct Graph));
    graph->vert = v;

    graph->array = (struct AdjList*) malloc(v * sizeof(struct AdjList));

    int i;
    for (i = 0; i < v; ++i)
        graph -> array[i].head = NULL;

    return graph;
}

/*
    NAME: create_Edge
    PARAMETERS: struct Graph* graph, char *src, char *dest, int weight, int flag
    PURPOSE: This function creates an edge for the graph
    PRECONDITION: there is information to be inputed into the graph as well as if the graph should be undirected or directed
    POSTCONDITION: creates a new edge within the graph
*/
void create_Edge(struct Graph* graph, char *src, char *dest, int weight, int flag)
{
    
    struct AdjListNode* newNode = newAdjListNode(dest, weight);

    struct AdjListNode* temp = graph -> array[src[0]-'A'].head;

    if(temp == NULL)
      graph -> array[src[0]-'A'].head = newNode;
    else
    {
        while(temp -> next != NULL)
            temp = temp -> next;
        temp -> next = newNode;
    }

    newNode = newAdjListNode(src, weight);

    temp = graph -> array[dest[0]-'A'].head;
    if(flag == 0)
    {
        if(temp == NULL)
            graph -> array[dest[0]-'A'].head = newNode;
        else
        {
            while(temp -> next != NULL)
                temp = temp -> next;
        temp -> next = newNode;
        }
    }

}

/*
    NAME: printGraph
    PARAMETERS: struct Graph* graph
    PURPOSE: this function prints the information of the graph
    PRECONDITION: there is a graph with data stored in the file
    POSTCONDITION: the graph will be successfully printed
*/
void printGraph(struct Graph* graph)
{
    printf("Adjacency List:\n");
    printf("\tNumber of Vertices: %d\n", graph -> vert);
    for (int v = 0; v < graph -> vert; v++)
    {
        struct AdjListNode* ginfo = graph -> array[v].head;
        printf("\n\t%c: ", v + 'A');
        while (ginfo != NULL)
        {
            printf("(%s, %d) -> ", ginfo -> dest, ginfo -> weight);
            ginfo = ginfo -> next;
        }
        printf("%p", NULL);
        printf("\n");
    }
}

/*
    NAME: findDegree
    PARAMETERS: struct Graph *graph, int indegree[]
    PURPOSE: the purpose of this function is to find the indegree which is needed in order to complete the topological sort algorithm
    PRECONDITION: there is a graph with data stored in the file
    POSTCONDITION: the indegree for adjlistnodes will be found and stored
*/
void findDegree(struct Graph *graph, int indegree[])
{
	struct AdjListNode *temp = NULL;
	int length = 0;
	for (int i = 0; i < graph->vert; ++i)
	{
		temp = graph -> array[i].head;
		length = 0;
		while (temp != NULL)
		{
			indegree[temp->dest[i]]++;
			temp = temp->next;
			length++;
		}
	}
}


/*
AUTHOR: De'Andre Gardener and Blanca Gallego
FILENAME: lab09.c
SPECIFICATION: In this program the purpose is to take in a text file with graph cases as well as the vertices number in the graph
               from there it will build new adjacency list nodes and store the graph into the adjacency list and print it out
FOR: CS 2413 Data Structures Section 002
*/
int main()
{
    struct Graph* graph;

    char a[2], b[2];
    int nv, flag, weight;
    FILE* infile;
    

    if (infile = fopen(testfile, "r"))
    {
        fscanf(infile,"%d", &nv);
        graph = createGraph(nv);
        fscanf(infile, "%d", &flag);
        while (fscanf(infile, "%s %s %d", &a[0], &b[0], &weight) != EOF)
        {
            create_Edge(graph, a, b, weight, flag);
        }
    }

    printGraph(graph);

    return 0;
}
/*

Team Member names: Deandre Gardener and Blanca Gallego
De'Andre: main driver, newAdjListNode, create_Edge

         
Blanca:  printGraph, createGraph, AdjListNode



TEST CASES AND STATUS:

1. undirected graph file graph.txt – passed
2. directed graph file - failed


1. Big O of finding the indegree of each vertex O(v+e)
2. Big O of the determining the critical path O(v)
3. Big O of the topological sort that tracks the maximum path lengths and critical path O(v+e)
4. Big O of the overall storage requirements for the topological sort that tracks the
   maximum path lengths and critical path O(|V|+|E|)

*/