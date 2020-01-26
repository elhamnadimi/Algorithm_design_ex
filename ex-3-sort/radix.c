#include<stdlib.h>
#include <stdio.h>
#include<time.h>
// Radix Sort in C Programming

/*In this array [121, 432, 564, 23, 1, 45, 788], we have the largest number 788. 
It has 3 digits. Therefore, the loop should go up to hundreds place (3 times).
Now, go through each significant place one by one.
using any stable sorting technique to sort the digits at each significant place.
 We have used counting sort for this.*/

int getMax(int array[], int n) // defind a func to find max
{
  int max = array[0];
  for (int i = 1; i < n; i++)
    if (array[i] > max)
      max = array[i];
  return max;
}
void countingSort(int array[], int size, int place)
{
  int output[size + 1];
  int max = (array[0] / place) % 10;
  for (int i = 1; i < size; i++)
  {
    if (((array[i] / place) % 10) > max)
      max = array[i];
  }
  int count[max + 1];
  for (int i = 0; i < max; ++i)
    count[i] = 0;
  for (int i = 0; i < size; i++)
    count[(array[i] / place) % 10]++;
  for (int i = 1; i < 10; i++)
    count[i] += count[i - 1];
  for (int i = size - 1; i >= 0; i--)
  {
    output[count[(array[i] / place) % 10] - 1] = array[i];
    count[(array[i] / place) % 10]--;
  }
  for (int i = 0; i < size; i++)
    array[i] = output[i];
}
void radixsort(int array[], int size)
{
  int max = getMax(array, size);
  for (int place = 1; max / place > 0; place *= 10)
    countingSort(array, size, place);
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
  int array[] = {121, 432, 564, 23, 1, 45, 788};
  int n = sizeof(array) / sizeof(array[0]);
  
  clock_t start=clock();
  radixsort(array, n);
  clock_t end=clock();

  printArray(array, n);
  
  printf("time passed[s] %lf \n", (double)(end-start)/CLOCKS_PER_SEC );  

}
