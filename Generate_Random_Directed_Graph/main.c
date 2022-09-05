#include <stdio.h>
#include <stdlib.h>
#include<math.h>
#include<stdbool.h>
#include<time.h>
#include "edge_str.h"

void random_graph(int v,int e);

int k = 1;

int main()
{
    FILE *fptr;//file pointer
    fptr = fopen("edge_file4.txt","w");//creating "edge_file.txt" in the same directory
    int v;
    long long e;
    srand(1);//using seed to generate different random numbers according to seed
    printf("Random Grapg Generation\n");
    printf("\nEnter the number of vertices:-\n");
    scanf("%d",&v);
    printf("Nuber of vertices = %d\n",v);
    long long max_e = (v*(v-1))-2*(v-2)-1;//mamimun number of edge possible with given vertex
    long long min_e = (v*pow(log(v),2))/4;//minimum number edge required according to question constrained
    printf("maximum number of edges = %lli\n",max_e);
    printf("minimum number of edges = %lli\n",min_e);
    e = (rand()%(max_e - min_e + 1))+min_e;//generating random number of edges with in max and min values.
    fprintf(fptr,"%d %lli\n",v,e);//writing (v,e) to file
    fclose(fptr);//close file
    random_graph(v,e);//calling function to generate random graph
    printf("\nGENERATED RANDOM GRAPG WITH %d VERTICES AND %lli EDGES\n",v,e);
    return 0;
}

void random_graph(int v,int e)
{
    int src = 1,des = v;
    long long max_edge=v*(v-1);
    long long upper=max_edge-1;
    struct edge * array_index=(struct edge*)malloc(max_edge*sizeof(struct edge));
    long long int p,q,t=0;
    for(p=1;p<=v;p++)
    {
        for(q=1;q<=v;q++)
        {
            if(p!=q)
            {
                array_index[t].u=p;
                array_index[t].v=q;
                t++;
            }
        }
    }


    FILE *fptr;
    fptr = fopen("edge_file4.txt","a");//writing to an already existing file
    if(fptr==NULL)
    {
        printf("\nCant open file\n");
        exit(1);
    }
    //int *edge[v+1];//adjacency matrix to represent graph
    int **edge = (int **)malloc((v+1)*sizeof(int *));
    for(int i = 0;i<v+1;i++)
        edge[i] = (int *)malloc((v+1)*sizeof(int));// array allocated in heap section to prevent stack overflow
    //int *edges[e+1];// array to store random edges generated in sequence
    int **edges = (int **)malloc((e+1)*sizeof(int *));
    for(int i = 0;i<e+1;i++)
    {
        edges[i] = (int *)malloc(3*sizeof(int));// array allocated in heap section to prevent stack overflow
    }
    for(int i = 0;i<=v;i++)
        for(int j = 0;j<=v;j++)
            edge[i][j] = 0;// initializing adjacency matrix
    int random_tree[v+1];//array to vertex that are not yet part of random tree
    for(int l =0;l<=v;l++)
        random_tree[l]=l;//initialization
    int current = 1;//generate random tree starting from vertex 1
    int random_vertex;

    for(int i=v;i>=2;i--)
    {
        int random_index = (rand()%(i - 2 + 1))+2;//generate a random index from 2 to i as we are staring from vertex 1 to generate random tree
        random_vertex = random_tree[random_index];//random vertex is the vertex at the random_index
        edge[current][random_vertex]=(k%3)+1;// updating adjacency matrix
        edges[v-i+1][0]=current;//storing random tree edge initial vertex
        edges[v-i+1][1]=random_vertex;//storing random tree edge destination vertex
        current = random_vertex;//updating current vertex to random vertex
        random_tree[random_index] = random_tree[i];//reducing index array size by one and copying the last vertex to the random_index pos whose vertex is already in random tree
        k++;
        if(random_vertex==v)
            break;
    }
    /*Random Tree Created.Assign remaining edges at random*/
    printf("\nv= %d e = %d\n",v,e);
    for(int i=k;i<=e;i++)
    {
        while(true)
        {
            long long random_index = (rand()%(upper + 1));
            int u=array_index[random_index].u;
            int v=array_index[random_index].v;
            if(edge[u][v]==0 && v!=src && u!=des)
            {
                array_index[random_index]=array_index[upper];
                upper--;
                edge[u][v]=(k%3)+1;// updating adjacency matrix
                //edge[v][u]=1;// updating adjacency matrix as it is undirected the matrix is symmetric
                edges[i][0]=u;//storing random tree edge initial vertex
                edges[i][1]=v;//storing random tree edge destination vertex
                if(edge[v][u]!=0 && edge[v][u]<(k%3)+1)
                    edge[v][u]=(k%3)+1;
                else if(edge[v][u]!=0 && edge[v][u]>=(k%3)+1)
                    edge[u][v]=edge[v][u];
                break;
            }
            else
            {
                array_index[random_index]=array_index[upper];
                upper--;
            }
        }
        k++;
    }
    printf("\n\nTHE (V,E) AND EDGES ARE\n\n");
    printf("(%d,%d)\n",v,e);
    /*Display the edges*/
    for(int i =1;i<=e;i++)
    {
        printf("%d ->(%d,%d)cost = %d\n",i,edges[i][0],edges[i][1],edge[edges[i][0]][edges[i][1]]);
        fprintf(fptr,"%d %d %d\n",edges[i][0],edges[i][1],edge[edges[i][0]][edges[i][1]]);//writing edges to file
    }
    fclose(fptr);//close file
}
