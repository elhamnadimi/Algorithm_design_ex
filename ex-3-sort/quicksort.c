
#include <stdlib.h>
#include<stdio.h>
#include<time.h>

/*
    Each time the Quick Sort performs the partition()
     on the input array, the pivot selected is the 
     smallest/largest value in the array */

void quicksort(int arr[25],int first,int last){
   int i, j, pivot, temp;

   if(first<last){
      pivot=first;
      i=first;  // first index of array
      j=last;  //last index of array


      // while array[left] < pivot
                //left := left + 1
      //while array[right] > pivot
                //right := right - 1

      while(i<j){ // while first ≤ last
         while(arr[i]<=arr[pivot]&&i<last)
            i++;
         while(arr[j]>arr[pivot])
            j--;
         if(i<j){  //swap array[left] with array[right]
            temp=arr[i];
            arr[i]=arr[j];
            arr[j]=temp;
         }
      }

      temp=arr[pivot];
      arr[pivot]=arr[j];
      arr[j]=temp;
      quicksort(arr,first,j-1); //left side of pivot is not sorted yet
      quicksort(arr,j+1,last);  // right side of pivot is not sorted yet! 

   }
}

int main(){
   int i, count, number[25];

   printf("How many elements are u going to enter?: ");
   scanf("%d",&count);

   printf("Enter %d elements: ", count);
   for(i=0;i<count;i++)
      scanf("%d",&number[i]);
	
	clock_t start=clock();
	quicksort(number,0,count-1);
	clock_t end=clock();


   printf("Order of Sorted elements: ");
   for(i=0;i<count;i++)
      printf(" %d",number[i]);

  	printf("time passed[s] %lf \n", (double)(end-start)/CLOCKS_PER_SEC );  


   return 0;
}
/*The answer depends on strategy for choosing pivot. 
In early versions of Quick Sort where leftmost (or rightmost)
 element is chosen as pivot, the worst occurs in following cases.

1) Array is already sorted in same order.
2) Array is already sorted in reverse order.
3) All elements are same (special case of case 1 and 2) */


