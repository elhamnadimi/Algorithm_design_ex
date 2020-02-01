#include <iostream>
#include <iomanip>

using namespace std;

#define SIZE 9


/* swap a[i] and a[j] */
void swap(int arr[], int i, int j)
{ 
  int temp;
  temp = arr[i];
  arr[i] = arr[j];
  arr[j] = temp;
}

void print(const int arr[])
{
  for(int i=0;i < SIZE; i++) {
    cout << setw(3) << arr[i];
  }
  cout << endl;
}

/* sort arr[left]...arr[right] into increasing order */
void qsort(int arr[], int left_index, int right_index)
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
    print(arr);   
  }
    
        // recursion
  qsort(arr,left_index,right);
  qsort(arr,left,right_index);
}

int main()
{
  int arr[SIZE]={1, 12, 5, 26, 7, 14, 3, 7, 2};
  print(arr);
  qsort(arr,0,SIZE-1);
  print(arr);
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


