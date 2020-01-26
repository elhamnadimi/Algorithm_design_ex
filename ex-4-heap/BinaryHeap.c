#include<stdio.h>
#include<stdlib.h>
#include "limits.h"

//When we use “typedef” keyword before struct <tag_name> like above,
// after that we can simply use type definition “status” in the C
// program to declare structure variable.


//A Binary Heap is a Complete Binary Tree
//Root is at index 0 in array.
//Left child of i-th node is at (2*i + 1)th index.
//Right child of i-th node is at (2*i + 2)th index.
//Parent of i-th node is at (i-1)/2 index.

typedef struct BinaryHeap
//We declare the size of the heap explicitly and it
// may differ from the size of the array. For example,
// for an array with a size of Array.length, the heap
// will only contain the elements which are within the
// declared size of the heap.
{
    int* H; // pointer to array of elements in heap
    size_t size; // Current number of elements in min heap
    int (*compare)(int,int);
}
BinaryHeap;

// to get index of left child of node at index i
int left_child(int i_child)
{
    return 2*(i_child+1)-1;
}
// to get index of right child of node at index i
int right_child(int i_child)
{
    return 2*(i_child+1);
}
// to get parent

int parent(int i_child)
{
    return (i_child-1)/2;
}
// to extract the root which is the minimum element
int root()
{
    return 0;
}

int is_root(int i_child)
{
    return i_child == root();
}

int last(BinaryHeap h)
{
    return h.size-1;
}


int is_valid_node(BinaryHeap h, int i)
{
    return h.size>i;
}


int heap_minimum(BinaryHeap h)
{
    return(h.H[root()]);
}


void freeBinaryHeap(BinaryHeap bh)
{
    free(bh.H);
}


void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
//The heapify procedure calls itself recursively to build heap
// in top down manner.


//    heapify(array)
//        Root = array[0]
//        Largest = largest( array[0] , array [2*0 + 1]. array[2*0+2])
//        if(Root != Largest)
//              Swap(Root, Largest)
void heapify(BinaryHeap h, int i)
{
    int m = i;
    int lc, rc; //left = 2*i + 1   // right = 2*i + 2
    int old = m;
    int finished = 0;

    while(!finished)
    {   //If the index of any element in the array is i,
        // the element in the index 2i+1 will become
        // the left child and element in 2i+2 index will
        // become the right child. Also, the parent of any
        // element at index i is given by the lower bound of (i-1)/2.
        rc = right_child(m);
        lc = left_child(m);
        m = (is_valid_node(h, rc) && h.compare(h.H[rc],h.H[m])) ? rc : m; //return the largest.
        m = (is_valid_node(h, lc) && h.compare(h.H[lc],h.H[m])) ? lc : m;
        if(old!=m) // here  if rc >m or lc>m ,it mean ! we change the amount of old
        {
            swap(&(h.H[m]), &(h.H[old]));
            old = m;
        } // here  // Recursively heapify the affected sub-tree
        else
            finished = 1; //just to exit program!
    }
}

//////////////////////////
/*void heapify(int arr[], int n, int i)
{
    int largest = i; // Initialize largest as root
    int l = 2*i + 1; // left = 2*i + 1
    int r = 2*i + 2; // right = 2*i + 2

    // If left child is larger than root
    if (l < n && arr[l] > arr[largest])
        largest = l;

    // If right child is larger than largest so far
    if (r < n && arr[r] > arr[largest])
        largest = r;

    // If largest is not root
    if (largest != i)
    {
        swap(arr[i], arr[largest]);

        // Recursively heapify the affected sub-tree
        heapify(arr, n, largest);
    }
}*//////////////////////////////////


void remove_minimum(BinaryHeap *h)
{
    h->H[root()] = h->H[last(*h)];
    h->size--;
    heapify(*h,root());
}


BinaryHeap build_binary_heap(int* A, size_t n, int (*compare_function)(int,int))
{
    BinaryHeap h;
    h.size=n;
    h.H=A; //?
    h.compare=compare_function;
    //the first index of non-leaf node is given by n/2 - 1.
    // All other nodes after that are leaf-nodes and thus don’t need to be heapified.
    for(int i=n/2-1;i>=0;i--)
        heapify(h, i);

    return h;
}
// Decreases key value of key at index i to new_val
void heap_decrease_key(BinaryHeap h, int i, int value)
{
    if(h.compare(h.H[i],value)) //????
    {
        printf("%d is not smaller than the selected element", value);  //??
    }

    h.H[i]=value;

    while( !is_root(i) && h.compare(h.H[i],h.H[parent(i)]) )
    {
        swap(&(h.H[i]),&(h.H[parent(i)]));
        i = parent(i);
    }

}

// Inserts a new key 'k'
void heap_insert(BinaryHeap* h, int value)
{
    (h->size)++;   //increase size!
    h->H[last(*h)] = INT_MAX;
    heap_decrease_key(*h, last(*h), value);
}
//INT_MAX is a macro that specifies that an integer
// variable cannot store any value beyond this limit.

void show_heap(BinaryHeap h)
{
    printf("\nheap: %d", h.H[0]);
    for(int i=1;i<h.size;i++)
        printf(", %d", h.H[i]);
    printf("\n");
}
//Just "%d" means "print an integer", and it should correspond to
// an integer value or a variable of type int in the corresponding position in the argument list.