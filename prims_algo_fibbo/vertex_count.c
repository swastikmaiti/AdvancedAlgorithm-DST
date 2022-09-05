#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vertex_count.h"

int vertex_count()
{
    FILE *fptr;
    fptr = fopen("C:\\Users\\swast\\OneDrive\\Desktop\\Prgramming_Assignment\\assignment1\\edge_file1.txt","r");
    if(fptr==NULL)
    {
        printf("Cant open FILE");
        exit(1);
    }
    char c[110];
    int vertex,i=0;
    int uv[2],v;
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
    fclose(fptr);
    return v;
}
