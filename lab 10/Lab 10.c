#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define max 1000
#define search_index_1 99

void selection_sort (void *a, int size, void (*swap) (void *,int,int), int (*compare) (void *,int,int));
void quickSort(int *a, int begin, int end);
int partition(int *a, int beg, int end);
void swap (void *, int, int);                                                   
int index_of_min (void *a, int low, int high, int (*compare) (void *,int,int)); 
int compare (void *a, int i, int j);
int linear_search(int *a, int lower_bound, int upper_bound,int val);
int binary_search(int *a, int lower_bound, int upper_bound,int val);
void stats(int *arr, int *arr2);
void print_sort(int *arr, int *arr2);
void print_search(int val);

/*
AUTHOR: De'Andre Gardener and Blanca Gallego
FILENAME: lab10.c
SPECIFICATION: In this program the purpose is to find the runtimes of both sort and search algorithms of different n sizes
FOR: CS 2413 Data Structures Section 002
*/
int main(void)
{
  
    int *arr = (int *)calloc(max,sizeof(int));
    int *arr2 = (int *)calloc(max,sizeof(int));
    for (int i = 0; i < max; i++)
    {
        arr[i] = rand() % 100000 + 1;
        arr2[i] = rand() % 100000 + 1;

    }
    stats(arr, arr2);
    
}


/*
    NAME: selection_sort
    PARAMETERS: void *a, int size, void (*swap) (void *,int,int), int (*compare) (void *,int,int)
    PURPOSE: the purpose of this function is to sort the array
    PRECONDITION: there is an array with data
    POSTCONDITION: it will call the necessary functions and sort the array in increasing order
*/

void selection_sort (void *a, int size, void (*swap) (void *,int,int), int (*compare) (void *,int,int)) 
{
    int lowind, i, j;
    for (i = 0; i < size-1; i++) 
    {   
        lowind = index_of_min (a,i,size-1,compare);
        if (i != lowind)
        {
            swap(a,i,lowind);
        }
    }
}

/*
    NAME: quickSort
    PARAMETERS: int *a, int begin, int end
    PURPOSE: the purpose of this function is to sort the array
    PRECONDITION: there is an array with data
    POSTCONDITION: it will call the necessary functions and sort the array in increasing order
*/
void quickSort(int *a, int begin, int end) 
{
    if (begin < end) 
    {
        int loc = partition(a, begin, end);
        quickSort(a, begin, loc - 1);
        quickSort(a, loc + 1, end);
    }
}

/*
    NAME: partition
    PARAMETERS: int *a, int beg, int end
    PURPOSE: the purpose of this function is to rearrange the array in a way where the values smaller than the pivot values
             will be placed before the pivot and values greater be placed after the pivot
    PRECONDITION: there is an array with data
    POSTCONDITION: it will reorganize the values within the array
*/
int partition(int *a, int beg, int end)
{
    int left = beg, right = end, loc = beg, flag = 0;
    while(flag == 0)
    {
        while(a[loc] <= a[right] && loc != right)
        {
            right = right - 1;
        }
        if(loc == right)
        {
            flag = 1;
        }
        else
        {
            swap(a, loc, right);
            loc = right;
        }
        if(flag == 0)
        {
            while(a[loc]>a[left] && loc != left)
            {
                left = left + 1;
            }
            if(loc == left)
            {
                flag = 1;
            }
            else
            {
                swap(a, loc, left);
                loc = left;
            }
        }
    }
}

/*
    NAME: index_of_min
    PARAMETERS: void *a, int low, int high, int (*compare) (void *,int,int)
    PURPOSE: the purpose of this function is to get the index of the minimum value
    PRECONDITION: there is an array with data that was passed into the function
    POSTCONDITION: it will return the smallest value within the given parameters
*/

int index_of_min (void *a, int low, int high, int (*compare) (void *,int,int))
{
    int lowind = low, i;
    for (i = low+1; i <= high; i++)
    {
        if (compare (a,i,lowind) < 0)
        {
            lowind = i;
        }
    }
    return lowind;
}

/*
    NAME: swap
    purpose:         swap exchanges the values in a[i] and a[j]               
    parameters:      void *a, int i, int j
    preconditions:   i and j must be valid array indices for array a
    postconditions:  the values in a[i] and a[j] are exchanged
 */
void swap (void *a, int i, int j) 
{
    int *b = (int *) a;
    int temp = b[i];
    b[i] = b[j];
    b[j] = temp;
}

/*
    NAME: compare
    PARAMETERS: void *a, int i, int j
    PURPOSE: the purpose of this function is to compare which value is smaller
    PRECONDITION: i and j must be valid array indices for array a
    POSTCONDITION: it will return the a value to indicate which value was smaller between i and j
*/
int compare (void *a, int i, int j)
{
    int *b = (int *) a;
    int res = 0;
    if(b[i] < b[j])
    {
        res = -1;
    }
    else if(b[i] > b[j])
    {
        res = 1;
    }
    return (res);
}

/*
    NAME: linear_search
    PARAMETERS: int *a, int lower_bound, int upper_bound,int val
    PURPOSE: the purpose of this function is to find a value within the array
    PRECONDITION: there is a sorted array to search through
    POSTCONDITION: it will return the value if it is found and return -1 if it isnt
*/
int linear_search(int *a, int lower_bound, int upper_bound,int val)
{
    int pos = -1;
    int i = lower_bound;
    while(i<= upper_bound)
    {
        if(a[i] == val)
        {
            pos = i;
            return(pos);
        }
        i = i+1;
    }
    return pos;
    
}

/*
    NAME: binary_search
    PARAMETERS: int *a, int lower_bound, int upper_bound,int val
    PURPOSE: the purpose of this function is to find a value within the array
    PRECONDITION: there is a sorted array to search through
    POSTCONDITION: it will return the value if it is found and return -1 if it isnt
*/
int binary_search(int *a, int lower_bound, int upper_bound,int val)
{
    int beg = lower_bound;
    int end = upper_bound;
    int pos = -1;
    int mid;
    while(beg <= end)
    {
        mid = (beg+end)/2;
        if(a[mid] == val)
        {
            pos = mid;
            return(pos);
        }
        else if(a[mid] > val)
        {
            end = mid - 1;
        }
        else
        {
            beg = mid + 1;
        }
    }
    return pos;
}

/*
    NAME: print_sort
    PARAMETERS: int *arr, int *arr2
    PURPOSE: the purpose of this function is to print the information for the sort algorithmms
    PRECONDITION: there is an array with data
    POSTCONDITION: runtimes for the sorts will be printed
*/
void print_sort(int *arr, int *arr2)
{
    clock_t start_time, end_time;

    printf("\nSelection Sort...");
    start_time = clock();
    selection_sort((void *) arr,max,swap,compare);     
    end_time = clock();
    printf ("\nmain - sort took %f seconds\n",(double)(end_time - start_time)/CLOCKS_PER_SEC);
    
    printf("\nQuick Sort...");
    start_time = clock();
    quickSort(arr2, 0, max-1);
    end_time = clock();
    printf ("\nmain - sort took %f seconds\n",(double)(end_time - start_time)/CLOCKS_PER_SEC);   
}

/*
    NAME: stats
    PARAMETERS: int *arr, int *arr2
    PURPOSE: the purpose of this function is to print the information for the search algorithms
    PRECONDITION: there is an array with data
    POSTCONDITION: runtimes for the search algorithms will be printed as well as if the value was found or not
*/
void stats(int *arr, int *arr2)
{
    clock_t start_time, end_time;
    int val;
    
    printf("Array of Random Numbers of size %d", max);
    srand(time(0));
    
    print_sort(arr, arr2);
    
    
    printf("\nLinear Search Sorted array: arr[%d] = %d",search_index_1, arr[search_index_1]);
    start_time = clock();
    val = linear_search(arr,0, max, arr[search_index_1]);   
    end_time = clock();
    printf ("\nmain - sort took %f seconds\n",(double)(end_time - start_time)/CLOCKS_PER_SEC);
    printf("index = %d\n ",val);
    
    printf("\nLinear Search Sorted array: arr[%d]+1 = %d",search_index_1, arr[search_index_1]+1);
    start_time = clock();
    val = linear_search(arr,0, max, arr[search_index_1]+1); 
    end_time = clock();
    printf ("\nmain - sort took %f seconds\n",(double)(end_time - start_time)/CLOCKS_PER_SEC);
    printf("index = %d\n",val);
    
    
    printf("\nBinary Search Sorted array: arr[%d] = %d",search_index_1, arr[search_index_1]);
    start_time = clock();
    val = binary_search(arr, 0, max - 1, arr[search_index_1]);   
    end_time = clock();
    printf ("\nmain - sort took %f seconds\n",(double)(end_time - start_time)/CLOCKS_PER_SEC);
    printf("index = %d\n",val);
    
    printf("\nBinary Search Sorted array: arr[%d]+1 = %d",search_index_1, arr[search_index_1]+1);
    start_time = clock();
    val = binary_search(arr, 0, max - 1, arr[search_index_1]+1);
    end_time = clock();
    printf ("\nmain - sort took %f seconds\n",(double)(end_time - start_time)/CLOCKS_PER_SEC);
    printf("index = %d\n",val); 
}
/*

Team Member names: Deandre Gardener and Blanca Gallego
De'Andre: quick sort functions, linear search, stats

         
Blanca:  selection sort functions, binary search, print_sort



TEST CASES AND STATUS:

1. sorting arrays with random values – passed
2. sorting arrays in increasing or decreasing order – passed
3. searching for values at the front, middle, and end of the sorted arrays – passed
4. searching for values that are not in the arrays – passed


1. Is there an array where the selection sort would take more steps or less steps? No
2. Is there an array where the quick sort would take more steps or less steps? yes
3. What improvement could the linear search have from the algorithm in the chapter 14
slides for a sorted array? Make it where the algorithm starts in the middle and does a comparison on whether it should go
                           left or right in order to reduce the time it takes to search the complete array
4. What is the big O of the overall storage requirements for each sort and search for n
items?
    selection sort - O(n)
    quick sort - O(nlog2n)
    linear search - O(n)
    Binary search - O(log2n)

*/
