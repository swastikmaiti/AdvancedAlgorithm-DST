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
#include "tree_operation.h"
#include "splay.h"
#include "level_graph.h"

int high=500;

void dinics2(struct Graph* graph,struct Graph* incoming_graph,long long int **level_cost,long long int **edge_cost,int t,struct Graph* augmenting_graph,long long int **augmenting_edge_cost,int n,long long int **prime_edge_cost);
void print_all(struct vertex **ptr);
void advance(struct vertex *S,struct vertex *T,struct Graph* graph,struct Graph* incoming_graph,long long int **edge_cost,long long int **level_cost,struct vertex **ptr,long long int **augmenting_edge_cost,long long int **prime_edge_cost,struct Graph* augmenting_graph);
void augment(struct vertex *S,struct vertex *T,long long int **augmenting_edge_cost,long long int **edge_cost,long long int **level_cost,struct vertex **ptr,struct Graph* graph,struct Graph* augmenting_graph,struct Graph* incoming_graph,long long int **prime_edge_cost);
void delete_(struct vertex *S,struct vertex *V,struct vertex *T,long long int **augmenting_edge_cost,long long int **edge_cost,long long int **level_cost,struct vertex **ptr,struct Graph* graph,struct Graph* incoming_graph,long long int **prime_edge_cost,struct Graph* augmenting_graph);
//void retreat(struct vertex *S,struct vertex *V,struct vertex *T,struct Graph* graph,struct Graph* incoming_graph,long long int **edge_cost,struct vertex **ptr,long long int **augmenting_edge_cost);
void retreat(struct vertex *S,struct vertex *V,struct vertex *T,struct Graph* graph,struct Graph* incoming_graph,long long int **edge_cost,long long int **level_cost,struct vertex **ptr,long long int **augmenting_edge_cost,long long int **prime_edge_cost,struct Graph* augmenting_graph);
void terminate(struct vertex *V,struct Graph* graph,struct Graph* incoming_graph,long long int **edge_cost,long long int **level_cost,struct vertex **ptr,long long int **augmenting_edge_cost,long long int **prime_edge_cost);


void phase(struct Graph* graph,struct Graph* augmenting_graph,long long int **edge_cost,long long int **augmenting_edge_cost,long long int **prime_edge_cost);


int z;


int main()
{
    long long int v = vertex_count();// get the vertex count
    long long int e = edge_count();// get the edge count
    printf("No of Vertex = %lli\n",v);
    printf("No of edge = %lli\n",e);
    high=v+500;
    long long int **edge_cost = cost(v);//initialize the edges to -1 in edge cost adjacency matrix


    long long int **prime_edge_cost = cost(v);
    struct Graph* prime_graph=generate_graph(prime_edge_cost);

    long long int **augmenting_edge_cost = cost(v);

    struct Graph* graph=generate_graph(edge_cost);//creates graph and returns the adjacency list to graph and also updates the edges

    struct Graph* incoming_graph=generate_incoming_graph();
    struct Graph* augmenting_graph = create_graph(v);

    printf("\n\n");

    long long int **level_cost = cost(v);

    //dinics2(graph,incoming_graph,level_cost,edge_cost,v,augmenting_graph,augmenting_edge_cost,v);
    phase(graph,augmenting_graph,edge_cost,augmenting_edge_cost,prime_edge_cost);
    printf("\nAUGMENTING GRAPH\n");
    print_aug_graph(augmenting_graph,augmenting_edge_cost);
    return 0;
}



void phase(struct Graph* graph,struct Graph* augmenting_graph,long long int **edge_cost,long long int **augmenting_edge_cost,long long int **prime_edge_cost)
{
    while(true)
    {
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

            dinics2(level_graph,incoming_level_graph,level_cost,edge_cost,v,augmenting_graph,augmenting_edge_cost,v,prime_edge_cost);
        }
        else
            break;
    }
}


void dinics2(struct Graph* graph,struct Graph* incoming_graph,long long int **level_cost,long long int **edge_cost,int t,struct Graph* augmenting_graph,long long int **augmenting_edge_cost,int n,long long int **prime_edge_cost)
{
    struct vertex **ptr=(struct vertex**)malloc((t+1)*sizeof(struct vertex*));
    for(int i=1;i<=t;i++)
    {
        ptr[i]=maketree(i);
        //ptr2[i]=ptr[i];
    }
     for(int i=1;i<=t;i++)
    {
        add_cost(ptr[i],high);
    }
    struct vertex *S=ptr[1];
    struct vertex *T=ptr[t];
    advance(S,T,graph,incoming_graph,edge_cost,level_cost,ptr,augmenting_edge_cost,prime_edge_cost,augmenting_graph);
}

void advance(struct vertex *S,struct vertex *T,struct Graph* graph,struct Graph* incoming_graph,long long int **edge_cost,long long int **level_cost,struct vertex **ptr,long long int **augmenting_edge_cost,long long int **prime_edge_cost,struct Graph* augmenting_graph)
{
    struct vertex *V=find_root(S);
    struct AdjListNode* temp;
    if(V==T)
    {
        augment(S,T,augmenting_edge_cost,edge_cost,level_cost,ptr,graph,augmenting_graph,incoming_graph,prime_edge_cost);
    }

    int v=V->vertex,status=0,w;
    temp = graph->array[v].head;

    while(temp)//loop through all adjacencies of vertex u
    {
        w = temp->des;
        if(edge_cost[v][w]>0)
        {
            status=1;
            break;
        }
        temp=temp->next;
    }

    if(status==0)
    {
        if(V!=T)
            retreat(S,V,T,graph,incoming_graph,edge_cost,level_cost,ptr,augmenting_edge_cost,prime_edge_cost,augmenting_graph);
    }
    else
    {
        add_cost(ptr[v],edge_cost[v][w]-high);
        int cost_v = edge_cost[v][w];



        link(ptr[v],ptr[w]);
        //ptr[v]->parent=ptr[w];
        //ptr[v]->successor=NULL;
        //ptr[w]->lc=ptr[v];
        //ptr[v]->dcost=ptr[v]->dcost-ptr[v]->parent->dcost;
        //ptr[v]->dmin=cal_dmin(ptr[v]);
        //ptr[w]->dmin=cal_dmin(ptr[w]);





        /*ptr[v]->parent=ptr[w];
        ptr[v]->successor=NULL;
        ptr[w]->lc=ptr[v];*/

        if(ptr[w]==T)
        {
            augment(S,T,augmenting_edge_cost,edge_cost,level_cost,ptr,graph,augmenting_graph,incoming_graph,prime_edge_cost);
        }
        else
        {
            advance(S,T,graph,incoming_graph,edge_cost,level_cost,ptr,augmenting_edge_cost,prime_edge_cost,augmenting_graph);

        }


    }
}

void augment(struct vertex *S,struct vertex *T,long long int **augmenting_edge_cost,long long int **edge_cost,long long int **level_cost,struct vertex **ptr,struct Graph* graph,struct Graph* augmenting_graph,struct Graph* incoming_graph,long long int **prime_edge_cost)
{

    //struct vertex *temp=find_cost(S);
    struct vertex *temp=find_min(S);




    int v,d;
    v=temp->vertex;
    d=find_cost(ptr[v]);



    add_cost(S,-d);
    int R=vertex_count();
    int path[R+1];
    for(int i=0;i<=R;i++)
    {
        path[i]=0;
    }
    int t=1;
    int k;
    for(k=1;k<=R;k++)
    {
        if(path[k]==0)
            break;
    }
    int l=k-1;
    for(k=1;k<=l;k++)
    {
        int cost=find_cost(ptr[path[k]]);
        if(cost>0 && k<l)
        {

            if(augmenting_edge_cost[path[k]][path[k+1]]==0)
            {
                insert_edge(augmenting_graph,path[k],path[k+1]);
            }

            augmenting_edge_cost[path[k]][path[k+1]]+=edge_cost[path[k]][path[k+1]]-cost;



            prime_edge_cost[path[k]][path[k+1]]-=edge_cost[path[k]][path[k+1]]-cost;

            level_cost[path[k]][path[k+1]]-=edge_cost[path[k]][path[k+1]]-cost;

            edge_cost[path[k]][path[k+1]]=cost;
        }
    }
    delete_(S,ptr[v],T,augmenting_edge_cost,edge_cost,level_cost,ptr,graph,incoming_graph,prime_edge_cost,augmenting_graph);
}

void delete_(struct vertex *S,struct vertex *V,struct vertex *T,long long int **augmenting_edge_cost,long long int **edge_cost,long long int **level_cost,struct vertex **ptr,struct Graph* graph,struct Graph* incoming_graph,long long int **prime_edge_cost,struct Graph* augmenting_graph)
{
    //normal_splay(ptr2[4]);
    find_root(V);




    int v=V->vertex,v_rc;
    if(V->rc!=NULL)
        v_rc=V->rc->vertex;
    else
        v_rc=V->parent->vertex;


    if(augmenting_edge_cost[v][v_rc]==0)
    {
        insert_edge(augmenting_graph,v,v_rc);
    }

    augmenting_edge_cost[v][v_rc]+=edge_cost[v][v_rc];

    prime_edge_cost[v][v_rc]-=edge_cost[v][v_rc];

    level_cost[v][v_rc]-=edge_cost[v][v_rc];

    edge_cost[v][v_rc]=0;



    cut(V);


    add_cost(V,high);


    struct vertex *temp=find_min(S);
    int d;
    v=temp->vertex;
    d=find_cost(ptr[v]);

    if(d==0)
    {
        delete_(S,ptr[v],T,augmenting_edge_cost,edge_cost,level_cost,ptr,graph,incoming_graph,prime_edge_cost,augmenting_graph);
    }
    else
    {
        advance(S,T,graph,incoming_graph,edge_cost,level_cost,ptr,augmenting_edge_cost,prime_edge_cost,augmenting_graph);
    }
}

void retreat(struct vertex *S,struct vertex *V,struct vertex *T,struct Graph* graph,struct Graph* incoming_graph,long long int **edge_cost,long long int **level_cost,struct vertex **ptr,long long int **augmenting_edge_cost,long long int **prime_edge_cost,struct Graph* augmenting_graph)
{
    if(V==S)
        terminate(V,graph,incoming_graph,edge_cost,level_cost,ptr,augmenting_edge_cost,prime_edge_cost);
    else
    {
        int v=V->vertex;
        struct AdjListNode* temp = incoming_graph->array[v].head;

        int statu=0;
        while(temp)
        {
            int u = temp->des;
            if(edge_cost[u][v]>0)
            {
                struct vertex *parent=NULL;
                parent=ptr[u]->parent;
                if(parent!=NULL)
                {
                    //printf("\nRETREAT ELSE\n");
                    while(parent->parent!=NULL)
                        parent=parent->parent;

                }

                if(parent!=V)
                {
                    edge_cost[u][v]=0;

                    augmenting_edge_cost[u][v]=0;


                    prime_edge_cost[u][v]=0;

                    level_cost[u][v]=0;

                }
                else
                {
                    edge_cost[u][v]=0;
                    cut(ptr[u]);
                    int p=u;

                    struct vertex *temp=find_min(ptr[u]);
                    int u=temp->vertex;

                    int d=find_cost(ptr[u]);

                    struct vertex *x=find_root(ptr[u]);
                    struct vertex *y=find_root(S);

                    if(x==y && p!=u)
                        printf("\n");
                    else
                        add_cost(ptr[u],high-d);
                }
            }
            //printf("\ncheck temp=%d\n",temp->des);
            temp=temp->next;
            //printf("\ncheck temp next=%d\n",temp->next->des);
        }

        advance(S,T,graph,incoming_graph,edge_cost,level_cost,ptr,augmenting_edge_cost,prime_edge_cost,augmenting_graph);
    }
}

void terminate(struct vertex *V,struct Graph* graph,struct Graph* incoming_graph,long long int **edge_cost,long long int **level_cost,struct vertex **ptr,long long int **augmenting_edge_cost,long long int **prime_edge_cost)
{
    int v=V->vertex;
    struct AdjListNode* temp = incoming_graph->array[v].head;
    while(temp)
    {
        int u = temp->des;
        if(edge_cost[u][v]>0)
        {
            struct vertex *parent=NULL;
            parent=ptr[u]->parent;
            if(parent!=NULL)
            {
                while(parent->parent!=NULL)
                    parent=parent->parent;
            }
            if(parent!=V)
            {


                augmenting_edge_cost[u][v]=0;

                prime_edge_cost[u][v]=0;

                level_cost[u][v]=0;
            }
            else
            {
                cut(ptr[u]);
                struct vertex *temp=find_min(ptr[u]);
                int u=temp->vertex;
                int d=find_cost(ptr[u]);
                add_cost(ptr[u],high-d);

            }
        }
    temp=temp->next;
    }

}
