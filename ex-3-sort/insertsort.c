	
#include <stdlib.h>
#include<stdio.h>
#include<time.h>

// It just calls insert on the elements at indices 1,2,3,…,n−1.
//for the first FOR, PIVOT is second elem and j is first elem
//because we want to sort all the elements before arr[i]

void insertation_sort(int arr[], int n)  // O(n^2)
{
	int i, j, pivot;
	for (i=1;i<n;i++) //n times
	{
		pivot=arr[i]; // O(1)
		j=i-1; // O(1)

		/* Move elements of arr[0..i-1], that are 
          greater than pivot, to one position ahead 
          of their current position */

		while(j>=0&&arr[j]>pivot)  // at most j-1 times
		{
			arr[j+1]=arr[j]; // O(1)      //moving array if bigger than next element
			j=j-1;           // O(1)
		}
			arr[j+1]=pivot; // O(1)    // move pivot one elem forward

	}
}	

// A utility function to print an array of size n 
void printArray(int arr[], int n) 
{ 
    int i; 
    for (i = 0; i < n; i++) 
        printf("%d ", arr[i]); 
    printf("\n"); 
} 
  
/* Driver program to test insertion sort */
int main() 
{ 
    int arr[] = {1,2,3,4,5,6,7,8,9,12,23,44,55};  // best case
    int length = sizeof(arr) / sizeof(arr[0]); 
  	clock_t start=clock();
    insertation_sort(arr, length); 
  	clock_t end=clock();
	printArray(arr, length); 
	printf("time passed[s] %lf \n", (double)(end-start)/CLOCKS_PER_SEC );  

    return 0; 
} 



//BEST CASE 

//Insertion sort performs two operations: 
//it scans through the list, comparing each pair of elements, 
//and it swaps elements if they are out of order. Each operation
//contributes to the running time of the algorithm. If the input
// array is already in sorted order, insertion sort compares O(n)O(n)O(n)

/*WORST CASE 
The worst case for insertion sort will occur when the input list 
is in decreasing order. To insert the last element, we need at most
n−1n-1n−1 comparisons and at most n−1n-1n−1 swaps.*/