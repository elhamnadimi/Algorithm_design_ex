#include <stdlib.h>
#include <stdio.h>
#include <time.h>


void swap (int* x,int* y)
{
    int temp = * x;
    * x = * y;
    * y = temp;
}

void selection_sort (int arr[], int n) // or  int *arr
{
    int i, j;
    int min_index;
     for (i=0;i<n-1;i++)
     {
         min_index=i;
         for (j=i+1; j<n; j++)
             if (arr[j] < arr[min_index])
                 min_index=j;
             swap(&arr[min_index],&arr[i]);
     }
}

int main ()
{
    int i;
    int arr[]={20,30,60, 54, 1, 2, 3, 3, 7, 8, 8, 100};
    unsigned long int n= sizeof(arr)/ sizeof(arr[0]);
    printf("Array before selection sort: \n");
    for(i = 0; i < n; ++i)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
    clock_t start = clock();
    selection_sort(arr,n);
    clock_t stop = clock();
    printf("Array after selection sort: \n");
    for(i=0;i<n;i++)
    {
        printf("%d ", arr[i]);
    }

    printf("\nTime passed[s]: %lf \n", (double)(stop-start)/CLOCKS_PER_SEC);

}
