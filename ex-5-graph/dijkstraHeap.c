#include <stdlib.h>
#include<stdio.h>
#include <time.h>
#include <limits.h>

struct Node{
  int id; //id of the Vertex
  int distance; //distance from the source
  int position; //needed for the implementation with the Heap
  struct Node * prev_node; //predecessor node (parent)
};
typedef struct Node Node;

struct Heap {
  Node **array;
  int size;
  //enum {MIN,MAX} type;//0 min, 1 max --> in this case we need only a minheap
};
typedef struct Heap Heap;
    
Node* findMin(Heap *H){
  return H->array[0];
}

size_t right(size_t i){
    return 2*i + 2;
}

size_t left(size_t i){
    return 2*i + 1;
}

int parent(int i){
    return (i-1)/2;
}

void printHeap(Heap *H){
  if (H->size == 0) {
    printf("The heap is empty\n");
    return;
  }

  for (int i = 0; i < H->size; i++) {
    if (H->array[i]->distance == INT_MAX) printf("INF\t");
    else printf("%d\t",H->array[i]->distance);
  }
  printf("\nThe size of the heap is: %d\n",H->size);
}

int isRoot(int i){
  return i == 0;
}

int is_valid_node(Heap* H, int i){
  return i <= (H->size -1);
}

void swapHeap(Node** a, Node** b){

    int t_pos = (**a).position;
    (**a).position = (**b).position;
    (**b).position = t_pos;

    Node* temp = *a;
    *a = *b;
    *b = temp;
}

int emptyHeap(Heap* H) {return H->size==0; }

void decreaseKey(Heap *H, int i, int value){
  // if (H->array[i]->distance < value) printf("The value is not smaller.\n");
  // else{
    H->array[i]->distance = value;
    while (!isRoot(i) && H->array[i]<=H->array[parent(i)]){
      swapHeap(&(H->array[i]),&(H->array[parent(i)]));
      i = parent(i);
    //}
  }
}

void updateDistance(Heap* H, Node* v, int w)
{
    int pos = v->position;
    decreaseKey(H, pos, w);
}

// for MinHeap
void minHeapify(Heap *H, size_t m){
  size_t k = -1;
  while (k!=m){
    k = m;
    int children[2] = {left(k),right(k)}; //indices of right and left
    for (int j = 0; j < 2; j++)
      if (is_valid_node(H, children[j]) && ((H->array[children[j]]->distance) <= (H->array[m]->distance)))
        m = children[j];
    if (k!=m)
      swapHeap(&(H->array[k]),&(H->array[m]));
  }
}

Heap buildMinHeap(Node *sourceArray, int n){
   Node** node_pointers = (Node**) malloc(sizeof(Node*)*n);
   for(int i=0; i<n; i++)
   {
       sourceArray[i].position = i;
       node_pointers[i]=&(sourceArray[i]);
   }

   Heap H;
   H.size = n;
   H.array = node_pointers;

    int lastParentIdx = parent(H.size-1);
    for (int i =  lastParentIdx; i >= 0; i--) {
      minHeapify(&H,i);
    }
    return H;
}

Node* extractMin(Heap *H){
  Node* min = H->array[0];
  H->array[0] = H->array[H->size-1];
  H->size--;
  minHeapify(H,0);
  return min;
}

double get_execution_time(const struct timespec b_time, const struct timespec e_time){
  return (e_time.tv_sec-b_time.tv_sec) +
                   (e_time.tv_nsec-b_time.tv_nsec)/1E9;
}

struct Graph{
  Node *nodes; //list of nodes
  int **adj_list;  //adjacency matrix
  int num_vertex; //number of vertex
};
typedef struct Graph Graph;

void relax(Heap* q, Node* u, Node* v, int w)
{
    if(u->distance + w < v->distance)
    {
        updateDistance(q, v, u->distance + w);
        v->prev_node = u;
    }
}

void initializeGraph(Graph *g){
  for (int i = 0; i < g->num_vertex; i++) {
    g->nodes[i].id = i;
    g->nodes[i].distance = INT_MAX;
    g->nodes[i].prev_node = NULL;
  }
}

Node* getNode(Graph *g, int idNode){
  for (int i = 0; i < g->num_vertex; i++) {
    if (g->nodes[i].id == idNode) return &(g->nodes[i]);
  }
  return NULL;
}

int weight(Graph* g, Node* from, Node* to){
  return g->adj_list[from->id][to->id];
}

int lengthAdj(Graph *g, Node *u){
  int n = 0;
  for(int i=0; i<g->num_vertex; i++){
      if((g->nodes)[i].id == u->id) continue;
      n+=(weight(g,u,&(g->nodes)[i]))< INT_MAX;
  }
  return n;
}

Node** adjacents(Graph* g, Node* u, int n)
{
    Node** adj = (Node**) malloc(sizeof(Node*)*n);
    int a = 0;
    for(int i=0; i<g->num_vertex; i++)
    {
        int w = weight(g,u,&(g->nodes)[i]);
        if(w<INT_MAX && (g->nodes)[i].id != u->id)
                adj[a++] = &(g->nodes)[i];
    }

    return adj;
}

void dijkstraHeap(Graph *g, int start_node){
  initializeGraph(g);
  Node *s = getNode(g,start_node);
  s->distance = 0;

  Heap Q = buildMinHeap(g->nodes, g->num_vertex); //create the queue as a MinHeap
  Heap *Q_pointer = &Q; //create a Q_pointer

  while(!emptyHeap(Q_pointer)){
    Node* u = extractMin(Q_pointer);

    int n =  lengthAdj(g, u);
    Node** u_adj = adjacents(g, u, n);

    for(int i=0; i<n; i++)
      relax(Q_pointer, u, u_adj[i], weight(g, u, u_adj[i]));
    // //free(u_adj);
  }
  //free(Q_pointer);
}


void printGraph(Graph* g)
{
    int size = g->num_vertex;
    for(int i=0; i<size; i++)
    {
        Node x = g->nodes[i];
        printf("\nnode %d, dist=%d", x.id, x.distance);
        if((x.prev_node)!=NULL)
            printf(", pred=%d", x.prev_node->id);
        else
            printf(", /");

    }
    printf("\n");
}

void printMatrix(int** matrix, int n_row, int n_col){
  for (int i = 0; i < n_row; i++) {
    for (int j = 0; j < n_col; j++) {
      if (matrix[i][j] == INT_MAX) printf("INF\t");
      else printf("%d\t",matrix[i][j]);
    }
    printf("\n");
  }
}

int main() {
  struct timespec b_time, e_time;
  double heapTime;
  int size = 6;
  int** adj_matrix = (int**) malloc(sizeof(int*)*size);
  for (int i = 0; i < size; i++)
    adj_matrix[i] = (int*)malloc(sizeof(int)*size);

  for(int i=0; i<size; i++){
    for (int j = 0; j < size; j++){
      adj_matrix[i][j]=INT_MAX;
    }
  }

  adj_matrix[0][1] = 1;
  adj_matrix[0][2] = 5;
  adj_matrix[1][5] = 15;
  adj_matrix[2][3] = 2;
  adj_matrix[3][4] = 1;
  adj_matrix[4][5] = 3;

  Graph g;
  g.num_vertex=size;
  g.adj_list = adj_matrix;
  g.nodes = (Node*) malloc(sizeof(Node)*size);
  printf("**** Adj Matrix ****\n");
  printMatrix(adj_matrix,size,size);

  printf("\n**** Heap solution ****\n");
  clock_t start = clock();
  clock_gettime(CLOCK_REALTIME, &b_time);
  dijkstraHeap(&g, 0);
  clock_t end = clock();
  clock_gettime(CLOCK_REALTIME, &e_time);
  heapTime = get_execution_time(b_time,e_time);
  double heapTime2 = (double)(end-start)/CLOCKS_PER_SEC;
  printf("Time[clock_gettime] = %lf\n",heapTime );
  printGraph(&g);

    return 0;
}