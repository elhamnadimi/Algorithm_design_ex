	
#include <stdlib.h>
#include<stdio.h>
#include<time.h>
void insertation_sort(int arr[], int n) //n=size array
{
	int i, j, pivot;
	for (i=1;i<n;i++)
	{
		pivot=arr[i]; //for the first FOR, PIVOT is second elem and j is first elem
		j=i-1; //because we want to sort all the elements before arr[i]

		/* Move elements of arr[0..i-1], that are 
          greater than pivot, to one position ahead 
          of their current position */
		while(j>=0&&arr[j]>pivot) 
		{
			arr[j+1]=arr[j];
			j=j-1;
		}
			arr[j+1]=pivot;

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
    int arr[] = { 12, 11, 13, 5, 6, 10, 20, 40, 32, 65, 87, 54, 12, 1, 0, 65, 98 }; 
    int n = sizeof(arr) / sizeof(arr[0]); 
  	clock_t start=clock();
    insertation_sort(arr, n); 
  	clock_t end=clock();

    printArray(arr, n); 
	printf("time passed[s] %lf \n", (double)(end-start)/CLOCKS_PER_SEC );  
    return 0; 
} 