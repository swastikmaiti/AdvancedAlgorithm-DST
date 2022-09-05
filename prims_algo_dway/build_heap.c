//-------------------------BUILD MIN HEAP IN BOTTOM UP APPROACH USING ADJUST FUNCTION---------------------
#include <stdio.h>
#include <math.h>
#include "build_heap.h"
#include "adjust.h"

void build_heap(node array[],int n,int d,int vertex_index[])
{
    int k = (n-2)/d;
    for(int i=k;i>=0;i--)
    {
        adjust(array,i,n,d,vertex_index);
    }
}
