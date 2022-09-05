#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "generate_incoming_graph.h"
#include "insert_edge.h"

struct Graph* generate_incoming_graph()
{

    FILE *fptr;
    fptr = fopen("C:\\Users\\swast\\OneDrive\\Documents\\Programming_Assignment2\\question1\\problem1\\edge_file.txt","r");
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
    struct Graph* graph2 = create_graph(v);
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
        insert_edge(graph2,uv[1],uv[0]);
        counter++;
    }
    fclose(fptr);
    return graph2;
}

struct Graph* generate_incoming_graph2(struct Graph* graph)
{
    int v=vertex_count();
    struct Graph* graph2 = create_graph(v+1);
    for(int i=1;i<=v;i++)
    {
        struct AdjListNode* temp = graph->array[i].head;
        while(temp)
        {
            int V=temp->des;
            insert_edge(graph2,V,i);
            temp=temp->next;
        }
    }
    return graph2;
}
