#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void fillArray(int arr[], int size)
{
  int i;
  for(i = 0; i < size; ++i)
    arr[i] = i+1;
}

/* swap a[i] and a[j] */
void swap(int arr[], int i, int j)
{ 
  int temp;
  temp = arr[i];
  arr[i] = arr[j];
  arr[j] = temp;
}

void print(const int arr[], int size)
{
  for(int i=0;i < size; i++)
    printf("%3d\n", arr[i]);

  printf("\n");
}

/* sort arr[left]...arr[right] into increasing order */
void quicksort(int arr[], int left_index, int right_index)
{
  int left, right, pivot;
  if(left_index >= right_index) return;

  left = left_index;
  right = right_index;

        // pivot selection
  pivot = arr[(left_index + right_index) /2];

        // partition
  while(left <= right) {
    while(arr[left] < pivot) left++;
    while(arr[right] > pivot) right--;
    if(left <= right) {
      swap(arr,left,right);
      left++; right--;
    }
  }
    
        // recursion
  quicksort(arr,left_index,right);
  quicksort(arr,left,right_index);
}

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

int main()
{
  int numElem = 10;
  int i;  
  int sizes[10] = {20, 40, 80, 160, 320, 640, 1280, 2560, 5120, 10240};
  float bestTimes[numElem];

  for(i = 0; i < numElem; ++i)
  {
    int arr[sizes[i]];
    fillArray(arr, sizes[i]);
    clock_t start=clock();
    quicksort(arr, 0, sizes[i]-1);
    clock_t end=clock();
    double time = (double)(end-start)/CLOCKS_PER_SEC ;
    bestTimes[i] = time;
    if(i == 0)
    {
      printf("Ordered List for first case of size %d:\n", sizes[i]);
      printIntArray(arr, sizes[i]);
    }
  }

  printf("Quick Sort Times (Best Case):\n");
  printFloatArray(bestTimes, numElem);
}


//DETAIL:

/*1 12  5 26  7 14  3  7  2
1 12 5 26 7 14 3 7 2
  pivot element = 7
  swap(12,2)
  1  2  5 26  7 14  3  7 12
  swap(26,7)
  1  2  5  7  7 14  3 26 12
  swap(7,3)
  1  2  5  7  3 14  7 26 12
  1  2  5  7  3 14  7 26 12
1 2 5 7 3.......*/

//poor choices of pivots can result in drastically slower (O(n^2)) performance, 
//but if at each step we choose the median as the pivot then it works in O(n log n).


