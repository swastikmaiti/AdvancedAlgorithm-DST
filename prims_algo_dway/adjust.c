//-------------------GIVEN NODE POSITION i ADJUST THE POSITION OF THE NODE TO CORRECT POSTION FROM i TO n----------------------------
#include<stdio.h>
#include "adjust.h"
#include "structure.h"
#define child_index(i,d,k)((d*i)+k)//returns the k'th child of i in a d way heap
#define parent_index(i,d)((i-1)/d)//returns the parent of i in a d way heap
void adjust(node array[], int i, int n, int d,int *vertex_index)
{
    int child_indexes[d+1];//array to store all the child index of a node
    int j = child_index(i,d,1);
    node item = array[i];// store the item
    //compare and check por correct position of node i till the last node
    while(j<=n)
    {
        int min_child_index = j;//initialize min child index
        int min_child = array[j].key;//initialize min child value
        //store all the child indexes of current node
        for(int child_no=1;child_no<=d;child_no++)
        {
            child_indexes[child_no] = (child_no+j<n)?child_no+j:-1;
        }
        //find out the min child value and its index
        for(int i=1;i<=d;i++)
        {
            if(child_indexes[i]==-1)
                break;
            if(array[child_indexes[i]].key<=min_child)
            {
                min_child = array[child_indexes[i]].key;
                min_child_index = child_indexes[i];
            }
        }
        //compare current node value with min child value
        if(min_child>=item.key)//min heap property satisfied
            break;
        vertex_index[array[min_child_index].vertex] = parent_index(j,d);//update the index position of the min child as the moves up
        array[parent_index(j,d)]=array[min_child_index];//move min child to its parent's position
        j = child_index(min_child_index,d,1);//update j to child of of the min child
    }
    vertex_index[item.vertex] = parent_index(j,d);//finally update the index position of item
    array[parent_index(j,d)]=item;
}
