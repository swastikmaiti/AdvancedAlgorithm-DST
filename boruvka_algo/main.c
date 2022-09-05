#include <stdio.h>
#include <stdlib.h>

#include "cost.h"
#include "edge_count.h"
#include "generate_graph.h"
#include "insert_edge.h"
#include "print_graph.h"
#include "structures.h"
#include "vertex_count.h"
#include "functions.h"
int a;

int main()
{
    int i;
    int v = vertex_count();// get the vertex count
    long long int e = edge_count();// get the edge count
    printf("No of Vertex = %d\n",v);
    printf("No of edge = %lli\n",e);
    long long int **edge_cost = cost(v);//initialize the edges to -1 in edge_cost adjacency matrix
    struct Graph* graph=generate_graph(edge_cost);//creates graph and returns the adjacency list to graph and also updates the edges

    struct vertex_pos* Vertex = init(v,edge_cost,graph);
    int const n=v;
    int edge[v+1][2],t=1;
    struct subset* subsets =(struct subset*)malloc((v+1)*sizeof(struct subset));//create disjoint set of vertices
    for (i=1;i<=v;i++)
    {
        subsets[i].parent = i;//initialization of disjoint set
        subsets[i].rank_ = 0;//initialization of disjoint set union find rank
        edge[i][0]=-1;
        edge[i][1]=-1;
    }
    while(linked_list_count>1)
    {
        find_min2(front_->root,subsets);//find the min item i.e bring min item to root
        front_->root=meld_list(front_->root);//meld list crated after deleting dummy nodes

        struct heap_node* min_heap_node=del_min2(front_->root,subsets);//delete the min item
        //store edge (u,v)
        int u=min_heap_node->u;
        int v=min_heap_node->v;
        //meld the leftist tree containing (u,v) and insert at end of list
        struct heap_node *h1=front_->root;
        int x = find_(subsets,v);//root of set containing v
        struct heap_node *h2=Vertex->array[x].head->root;//retrieve memory location of other node v
        struct heap_node *temp=meld(h1,h2,subsets);//meld leftist trees
        Union(subsets,u,v);//union if set containing the vertices
        int y = find_(subsets,v);//find the root of new union vertices
        del(front_);//delete the node at front of linked list
        del(Vertex->array[x].head);//delete the linked list node containing the tree for other vertex
        linked_list_count-=2;//as two linked list nodes are deleted
        struct linked_list_node *new_node=(struct linked_list_node*)malloc(sizeof(struct linked_list_node));//create new linked list node
        new_node->root=temp;//insert the merged tree into new list node
        insert_list_node(new_node);//insert new list node at end
        //update vertex position of all the vertices into the root of union of all current vertices
        Vertex->array[y].head=new_node;
        Vertex->array[y].head=new_node;
        Vertex->array[y].head->root=temp;
        Vertex->array[y].head->root=temp;
        //update the MST edge
        edge[t][0]=u;
        edge[t][1]=v;
        t++;

    }
    printf("\nMST EDGES\n");
    long long int sum=0;
    int u;
    for(i=1;i<n;i++)
    {
        u=edge[i][0];
        v=edge[i][1];
        sum+=edge_cost[u][v];
        printf("%d->%d %d\n",i,u,v);
    }
    printf("\nTOTAL MST COST = %lli\n",sum);
    return 0;
}
