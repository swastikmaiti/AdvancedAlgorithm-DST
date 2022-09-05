#include<stdio.h>
#include<stdbool.h>
#include "cost.h"
#include "edge_count.h"
#include "generate_graph.h"
#include "insert_edge.h"
#include "print_graph.h"
#include "print_aug_graph.h"
#include "structures.h"
#include "vertex_count.h"
#include "generate_incoming_graph.h"
#include "stack.h"
#include "level_graph.h"

int z;


void phase(struct Graph* graph,struct Graph* augmenting_graph,long long int **edge_cost,long long int **augmenting_edge_cost,long long int **prime_edge_cost);


void dinics(struct Graph* graph,struct Graph* incoming_graph,long long int **edge_cost,int t,struct Graph* augmenting_graph,long long int **augmenting_edge_cost,int n,long long int **prime_edge_cost);
int retreat(int v,struct Graph* incoming_graph,long long int **edge_cost,long long int **prime_edge_cost);
void del_vertex(int v,struct Graph* incoming_graph,long long int **edge_cost,long long int **prime_edge_cost);
int augment(struct Graph* augmenting_graph,long long int **edge_cost,long long int **augmenting_edge_cost,int n,long long int **prime_edge_cost);

int main()
{
    long long int v = vertex_count();// get the vertex count
    long long int e = edge_count();// get the edge count
    printf("No of Vertex = %lli\n",v);
    printf("No of edge = %lli\n",e);
    long long int **edge_cost = cost(v);//initialize the edges to -1 in edge cost adjacency matrix

    long long int **prime_edge_cost = cost(v);
    struct Graph* prime_graph=generate_graph(prime_edge_cost);


    long long int **augmenting_edge_cost = cost(v);
    struct Graph* graph=generate_graph(edge_cost);//creates graph and returns the adjacency list to graph and also updates the edges
    struct Graph* incoming_graph=generate_incoming_graph();
    struct Graph* augmenting_graph = create_graph(v);
    //print_graph(graph);
    printf("\n\n");


    //dinics(graph,incoming_graph,edge_cost,v,augmenting_graph,augmenting_edge_cost,v);

    phase(graph,augmenting_graph,edge_cost,augmenting_edge_cost,prime_edge_cost);

    printf("\nAUGMENTING GRAPH\n");
    print_aug_graph(augmenting_graph,augmenting_edge_cost);
    return 0;
}

void phase(struct Graph* graph,struct Graph* augmenting_graph,long long int **edge_cost,long long int **augmenting_edge_cost,long long int **prime_edge_cost)
{
    while(true)
    {
        //print_aug_graph(graph,edge_cost);
        int status=0;
        int v = vertex_count();
        int t=v;
        long long int **level_cost = cost(v);
        struct Graph* level_graph=generate_level_graph(graph,prime_edge_cost,level_cost);

        struct Graph* incoming_level_graph=generate_incoming_graph2(graph);


        for(int i=1;i<=v;i++)
        {

            struct AdjListNode* temp = level_graph->array[i].head;
            while(temp)
            {

                int V=temp->des;
                if(V==v)
                    status=1;
                if(V!=v && level_graph->array[V].head==NULL)
                {
                    struct AdjListNode* T = level_graph->array[i].head;
                    temp->des=T->des;
                    level_graph->array[i].head=level_graph->array[i].head->next;
                    //free(T);
                }
            temp=temp->next;
            }
        }

        if(status==1)
        {

            for(int i=0;i<=v;i++)
                for(int j=0;j<=v;j++)
                    edge_cost[i][j]=prime_edge_cost[i][j];
            dinics(level_graph,incoming_level_graph,edge_cost,v,augmenting_graph,augmenting_edge_cost,v,prime_edge_cost);
        }
        else
            break;
    }
}





void dinics(struct Graph* graph,struct Graph* incoming_graph,long long int **edge_cost,int t,struct Graph* augmenting_graph,long long int **augmenting_edge_cost,int n,long long int **prime_edge_cost)
{
    struct AdjListNode* temp;
    int s = 1;
    int v = s;
    int status=0;
    push(s);
    do
    {
        status=0;
        temp = graph->array[v].head;//get the adjacencies of node u
        while(temp)//loop through all adjacencies of vertex u
        {
            int w = temp->des;
            if(edge_cost[v][w]>0)
            {
                push(w);
                v=w;
                temp = graph->array[v].head;
            }
            else
            {
                temp=temp->next;
            }
        }
        if(v==t)
        {
            v = augment(augmenting_graph,edge_cost,augmenting_edge_cost,n,prime_edge_cost);
        }
        else
            v = retreat(v,incoming_graph,edge_cost,prime_edge_cost);
        temp = graph->array[v].head;
        while(temp)//loop through all adjacencies of vertex u
        {
            int w = temp->des;
            if(edge_cost[v][w]>0)
            {
                status=1;
                break;
            }
            temp = temp->next;
        }
        if(v==s && status==0)
        {
            break;
        }
    }while(true);
}

int retreat(int v,struct Graph* incoming_graph,long long int **edge_cost,long long int **prime_edge_cost)
{
    del_vertex(v,incoming_graph,edge_cost,prime_edge_cost);
    pop();
    int item = pop();
    push(item);
    return item;
}

void del_vertex(int v,struct Graph* incoming_graph,long long int **edge_cost,long long int **prime_edge_cost)
{
    struct AdjListNode* temp = incoming_graph->array[v].head;//get the adjacencies of node u
    while(temp)//loop through all adjacencies of vertex u
    {
        int w = temp->des;
        if(edge_cost[w][v]>0)
        {
            edge_cost[w][v]=0;
        }
        temp=temp->next;
    }
}

int augment(struct Graph* augmenting_graph,long long int **edge_cost,long long int **augmenting_edge_cost,int n,long long int **prime_edge_cost)
{
    int delta=100;
    int path[n+2];
    int i=0;
    while(true)
    {
        int v = pop();
        path[i++]=v;
        int u = top();
        if(u!=-1 && edge_cost[u][v]<delta)
            delta = edge_cost[u][v];
        if(v==-1)
            break;
    }
    i=i-2;
    push(path[i--]);
    int push_status=1;
    while(i>=0)
    {
        int v = path[i--];
        int u = path[i+2];
        edge_cost[u][v]-=delta;
        edge_cost[v][u]+=delta;
        if(push_status==1 && edge_cost[u][v]>0)
        {
            push(v);
        }
        else
        {
            push_status=0;
        }
        if(augmenting_edge_cost[u][v]==0)
        {
            insert_edge(augmenting_graph,u,v);
        }
        augmenting_edge_cost[u][v]+=delta;

            prime_edge_cost[u][v]-=delta;
    }
    return top();
}

