	
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
void printFloatArray(float arr[], int n) 
{ 
    int i; 
    for (i = 0; i < n; i++) 
        printf("%f ", arr[i]); 
    printf("\n"); 
} 
void printIntArray(int arr[], int n) 
{ 
    int i; 
    for (i = 0; i < n; i++) 
        printf("%d ", arr[i]); 
    printf("\n"); 
} 

void fillBestArray(int arr[], int n)
{
	int i;
	for(i = 0; i < n; ++i)
		arr[i] = i+1;
}

void fillWorstArray(int arr[], int n)
{
	int i;
	for(i = 0; i < n; ++i)
		arr[i] = n - i;
}

/* Driver program to test insertion sort */
// int main() 
// { 
//     int arr[] = {1,2,3,4,5,6,7,8,9,12,23,44,55};  // best case
//     int length = sizeof(arr) / sizeof(arr[0]); 
//   	clock_t start=clock();
//     insertation_sort(arr, length); 
//   	clock_t end=clock();
// 	printArray(arr, length); 
// 	printf("time passed[s] %lf \n", (double)(end-start)/CLOCKS_PER_SEC );  

//     return 0; 
// } 

// int main()
// {	//number of total arrays in best or worst case
// 	int num = 10;
// 	//these are the sizes for different arrays
// 	int sizes[num] = {20, 40, 60, 80, 100, 200, 400, 800, 1600, 3200};
// 	int arr1[num];
// 	int arr2[num];
// 	int arr3[num];
// 	int arr4[num];
// 	int arr5[num];
// 	int arr6[num];
// 	int arr7[num];
// 	int arr8[num];
// 	int arr9[num];
// 	int arr10[num];
// 	int* arrays[num] = {arr1, arr2, arr3, arr4, arr5, arr6, arr7, arr8, arr9, arr10};
// 	float bestTimes[num];
// 	float worstTimes[num];
// 	int i;
// 	float time;
// 	for(i = 0; i < num; ++i)
// 		fillWorstArray(arrays[i], sizes[i]);

// 	for(i = 0; i < num; ++i)
// 	{
// 	  	clock_t start=clock();
// 	    insertation_sort(arrays[i], sizes[i]); 
// 	  	clock_t end=clock();
// 	  	time = (double)(end-start)/CLOCKS_PER_SEC ;
// 	  	worstTimes[i] = time;
// 	}

// 	for(i = 0; i < num; ++i)
// 		fillBestArray(arrays[i], sizes[i]);

// 	for(i = 0; i < num; ++i)
// 	{
// 	  	clock_t start=clock();
// 	    insertation_sort(arrays[i], sizes[i]); 
// 	  	clock_t end=clock();
// 	  	time = (double)(end-start)/CLOCKS_PER_SEC ;
// 	  	bestTimes[i] = time;
// 	}

// 	printf("Worst Case Times:\n");
// 	printArray(worstTimes, num);
// 	printf("Best Case Times:\n");
// 	printArray(bestTimes, num);

// 	return 0;

// }


int main()
{
	int numElem = 10;
	int i;	
	int sizes[10] = {20, 40, 80, 160, 320, 640, 1280, 2560, 5120, 10240}; // the size of array .
	float worstTimes[numElem];
	float bestTimes[numElem];
	for(i = 0; i < numElem; ++i)
	{
		int arr[sizes[i]];
		fillWorstArray(arr, sizes[i]);
	  	clock_t start=clock();
	    insertation_sort(arr, sizes[i]); 
	  	clock_t end=clock();
	  	double time = (double)(end-start)/CLOCKS_PER_SEC ;
	  	worstTimes[i] = time;
	}

	printf("Worst Times[Reverse Order]:\n");
	printFloatArray(worstTimes, numElem);

	for(i = 0; i < numElem; ++i)
	{
		int arr[sizes[i]];
		fillBestArray(arr, sizes[i]);
	  	clock_t start=clock();
	    insertation_sort(arr, sizes[i]); 
	  	clock_t end=clock();
	  	double time = (double)(end-start)/CLOCKS_PER_SEC ;
	  	bestTimes[i] = time;
	}

	printf("Best Times[Ordered]:\n");
	printFloatArray(bestTimes, numElem);

}

//BEST CASE 

//Insertion sort performs two operations: 
//it scans through the list, comparing each pair of elements, 
//and it swaps elements if they are out of order. Each operation
//contributes to the running time of the algorithm. If the input
// array is already in sorted order, complexity: O(n)

/*WORST CASE 
The worst case for insertion sort will occur when the input list 
is in decreasing order. To insert the last element, we need at most
n−1n-1n−1 comparisons and at most n−1n-1n−1 swaps. complexity O(n2)*/
