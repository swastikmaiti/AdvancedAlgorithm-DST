#include "cost.h"
#include <stdlib.h>
#include <stdio.h>
long long int** cost(int v)
{
    int i,j;
    long long int **edge = (long long int**)malloc((v+1)*sizeof(long int*));
    for(i = 0;i<=v;i++)
        edge[i] = (long long int *)malloc((v+1)*sizeof(long long int));
    for(i = 0;i<=v;i++)
        for(j = 0;j<=v;j++)
            edge[i][j] = 0;
    return edge;
}
