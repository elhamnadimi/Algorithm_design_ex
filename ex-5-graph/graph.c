#include <stdio.h>
#include <stdlib.h>
#include<time.h>
/*****
This is Dijkstra's algorithm (a greedy algorithm) 
for finding the shortest path between nodes in a graph.
The algortihm works by starting from the starting node(here node 0), 
finds the next neighbor node with the shortest path from node 0, 
visits that node, then finds the shortest path to the next neighboring node.
we will continue this procedure until all nodes are visited.

For an extended explanation of the algorithm you can refer to:
https://www.thecrazyprogrammer.com/2014/03/\
dijkstra-algorithm-for-finding-shortest-path-of-a-graph.html
*/

#define INF  9999
#define MAX 5

void dijkstra(int G[MAX][MAX], int n, int startnode) // no : node-----G: MATRIX
{
	int cost[MAX][MAX], distance[MAX], pred[MAX];
	int visited[MAX], count, mindistance, nextnode, i, j;

	/**
	cost matrix is the same as Graph matrix, except that
	nodes that are not connected immediately to startnode are
	initialized to infinity.
	*/
	for(i = 0; i< n; ++i)
		for(j = 0; j < n; ++j)
		{
			if(G[i][j] == 0)
				cost[i][j] = INF;
			else
				cost[i][j] = G[i][j];
		}							

	/**
	distance[i]: is the distance of node i from 
	starting node.
	pred[i]: is the predecessor node of node i
	*/
	for( i = 0; i < n; ++i)
	{
		distance[i] = cost[startnode][i]; // distance[i] IS ARRAY
		pred[i] = startnode;
		visited[i] = 0; //ARRAY
	}
	/**
	at first we're just visited starting node
	and it's distance from iteself is zero
	and so far we have just visited one node.
	*/
	distance[startnode] = 0;
	visited[startnode] = 1;
	count = 1;

	/**
	loop over all nodes until we are finished
	*/
	while(count < n-1)
	{
		mindistance = INF;
		/**
		find a node with minimum distance from startnode
		that is not yet visited and visit that node.
		*/
		for(i = 0; i < n; i++)
			if(distance[i]<mindistance && !visited[i])
			{
				mindistance = distance[i]; //NODE
				nextnode = i;
			}
		visited[nextnode] = 1;

		/**
		for all the nodes i that is not yet visited if the path-length of going from 
		nextnode of startnode to that node i is less than the distance of going directly from
		startnode to that node i, then update distance[i] to go to node i from nextnode rather than
		directly, this is the same thing that we did for startnode to find its closest node, here
		we do it for all other nodes.
		*/
		for(i = 0; i < n; i++)
			if(mindistance+cost[nextnode][i]<distance[i] && !visited[i])
			{
				distance[i] = mindistance + cost[nextnode][i];
				pred[i] = nextnode;
			}

			count++;
	}

	for(i = 0; i < n; ++i)
		if(i != startnode)
		{
			printf("\nDistance of node %d=%d", i, distance[i]); // i = node
			printf("\nPath=%d", i);
			j = i;
			do
			{
				j = pred[j]; // we always print previous nodes becuse it means path 
				printf("<-%d", j); 
			}while(j != startnode);
		}
	printf("\n");
}

int main()
{	//Adjacency Matrices to present a graph! 
	// int G[MAX][MAX]={{0,1,0,3,10},{1,0,5,0,0},{0,5,0,2,1},{3,0,2,0,6},{10,0,1,6,0}};
	int G[MAX][MAX] = {{0,10,0,30,100},{10,0,50,0,0},{0,50,0,20,10},{30,0,20,0,60},{100,0,10,60,0}};
	int n = 5;
	int u = 1; //start node 
	clock_t start = clock();
	dijkstra(G, n, u);
	clock_t stop = clock();
	printf("\nTime passed[s]: %lf \n", (double)(stop-start)/CLOCKS_PER_SEC);

	return 0;

}
