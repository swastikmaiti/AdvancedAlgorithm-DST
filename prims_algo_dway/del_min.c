//--------------------DELETE THE MINIMIN ITEM FROM THE d WAY HEAP-----------------------------
#include "del_min.h"
#include "adjust.h"
#include <stdio.h>
int del_min(node array[],long long int *n,int *vertex_index,int d)
{
    int min_item = array[0].vertex;//store the min item which is the first item
    vertex_index[array[0].vertex]=-1;//update index position of min item to -1
    vertex_index[array[*n-1].vertex]=0;//the last item is to be brought to first position so update its index position
    array[0]=array[*n-1];//bring the last item to first position
    *n = *n-1;//decrease the number of veritces
    adjust(array,0,*n,d,vertex_index);//call adjust function
    return min_item;
}
