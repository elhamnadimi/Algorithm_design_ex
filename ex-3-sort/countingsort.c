// Counting sort in C programming
#include<stdlib.h>
#include <stdio.h>
#include<time.h>

// we should define 3 array : 
//array[] is orginal array 
//count [] : for counting our val.
//out put[] : to place sorted numbers

void countingSort(int array[], int size)
{
  int output[20];
  int max = array[0];
  for (int i = 1; i < size; i++)
  {
    if (array[i] > max)
      max = array[i];
  }
  // The size of count must be at least the (max+1) but
  // we cannot assign declare it as int count(max+1) in C as
  // it does not support dynamic memory allocation.
  // So, its size is provided statically.
  
  //Initialize an array of length max+1 with all elements 0.
  //This array is used for storing the count of the elements in the array.
  int count[20];
  for (int i = 0; i <= max; ++i) 
  {
    count[i] = 0;
  } 
  //Store the count of each element at their respective index in count array
  for (int i = 0; i < size; i++)
  {
    count[array[i]]++;
  }
  //Store cumulative sum of the elements of the count array.
  // It helps in placing the elements into the correct index.
  for (int i = 1; i <= max; i++)
  {
    count[i] += count[i - 1];
  }
  //Find the index of each element of the original array
  //in count array. This gives the cumulative count.
  // Place the element at the index calculated.
  for (int i = size - 1; i >= 0; i--)
  {
    output[count[array[i]] - 1] = array[i];
    count[array[i]]--;
  }
  //After placing each element at its correct position, decrease the its count by one.
  for (int i = 0; i < size; i++)
  {
    array[i] = output[i];
  }
}
void printArray(int array[], int size)
{
  for (int i = 0; i < size; ++i)
  {
    printf("%d  ", array[i]);
  }
  printf("\n");
}
    int main()
    {
      int array[] = {4, 2, 19, 8, 5, 18, 13,0,3, 12, 15, 17};
      int n = sizeof(array) / sizeof(array[0]);
      clock_t start=clock();
      countingSort(array, n);
      clock_t end=clock();
      printArray(array, n);
      printf("time passed[s] %lf \n", (double)(end-start)/CLOCKS_PER_SEC );  

    }

