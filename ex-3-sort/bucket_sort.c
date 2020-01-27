// Bucket Sort in C programming
#include <stdio.h>
#include<time.h>
int getMax(int array[], int size)
{
  int max = array[0];
  for (int i = 1; i < size; i++)
    if (array[i] > max)
      max = array[i];
  return max;
}

  //This code divides a predefined input array among 3 buckets by range:
  //[-infinity][-1] -> first bucket
  //[0;10] -> second bucket
  //[11;infinity] -> third bucket

void bucketSort(int array[], int size)
{
  // The size of bucket must be at least the (max+1) but
  // we cannot assign declare it as int bucket(max+1) in C as
  // it does not support dynamic memory allocation.
  // So, its size is provided statically.
  int bucket[10];
  const int max = getMax(array, size);
  for (int i = 0; i <= max; i++)
  {
    bucket[i] = 0; // initializing the auxiliary array elements to 0
  }
  for (int i = 0; i < size; i++)  //
  {
    // there is an iteration through the given array
    // of numbers such that each element equalling the
    // index of an element in the auxiliary array has 
    //its value incremented by 1 everytime the element occurs. 

    bucket[array[i]]++;   // filling the auxiliary array with elements of unsorted array
  }
  for (int i = 0, j = 0; i <= max; i++) // emptying the auxiliary array
    // lastly, all the incremented elements
    // in the auxiliary array are assigned 
    //back to the original array in order
  {
    while (bucket[i] > 0)
    {
      array[j++] = i;
      bucket[i]--;
    }
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
  int data[] = {4, 3, 4, 5, 6, 0, 9, 5};
  int size = sizeof(data) / sizeof(data[0]);
  clock_t start=clock();
  bucketSort(data, size);
  clock_t end=clock();

  printf("Sorted array in ascending order: \n");

  printArray(data, size);
  printf("time passed[s] %lf \n", (double)(end-start)/CLOCKS_PER_SEC );  

}