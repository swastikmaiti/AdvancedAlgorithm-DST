//----------------------------REDUCE THE KEY OF A NODE AT A GIVEN INDEX-----------------------------
#include <stdio.h>
#include "reduce_key.h"
#define child_index(i,d,k)((d*i)+k)
#define parent_index(i,d)((i-1)/d)
void reduce_key(node array[],int n,int index,int new_val,int d,int *vertex_index)
{
    node item = array[index];item.key=new_val;//retrieve the item to reduce and update new value
    //vertex_index[array[n-1].vertex]=index;
    //array[index] = array[n-1];
    //int i = n-1;
    int i = index;
    //compare with parent till heap proprty satisfied or first position is reached
    while(i>0 && array[parent_index(i,d)].key>item.key)
    {
        vertex_index[array[parent_index(i,d)].vertex] = i;//update the index position of node
        array[i] = array[parent_index(i,d)];//bring down parent of current node to its position
        i = parent_index(i,d);//move up to the position of parent
    }
    vertex_index[item.vertex] = i;
    array[i]=item;
}
