#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "generate_graph.h"
#include "insert_edge.h"

struct Graph* generate_graph(long long int **edge)
{

    FILE *fptr;
    fptr = fopen("C:\\Users\\swast\\OneDrive\\Documents\\Programming_Assignment2\\question1\\problem1\\edge_file4.txt","r");
    if(fptr==NULL)
    {
        printf("Cant open FILE");

        exit(1);
    }
    char c[110];
    int vertex,i=0,counter=1;
    int uv[3],v,e;
    fgets(c,100,fptr);
    char *token = strtok(c," ");
    while(i<2)
    {
        vertex = atoi(token);
        uv[i]=vertex;
        token = strtok(NULL, " ");
        i++;
    }
    v = uv[0];
    e = uv[1];
    struct Graph* graph = create_graph(v);
    while(fgets(c,100,fptr)!=NULL)
    {
        char *token = strtok(c," ");
        i=0;
        while(i<3)
        {
            vertex = atoi(token);
            uv[i]=vertex;
            token = strtok(NULL, " ");
            i++;
        }
        edge[uv[0]][uv[1]]=uv[2];
        insert_edge(graph,uv[0],uv[1]);
        counter++;
    }
    fclose(fptr);
    return graph;
}
