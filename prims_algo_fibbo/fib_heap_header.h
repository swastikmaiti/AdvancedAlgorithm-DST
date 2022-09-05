#ifndef FIB_HEAP_HEADER_H_INCLUDED
#define FIB_HEAP_HEADER_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>


int del_min();
void arrange();
struct node* Fibonnaci_link(struct node* ptr2, struct node* ptr1);

// fibonacci heap node structure
struct node
{
    struct node* parent; // Parent pointer
    struct node* child; // Child pointer
    struct node* left; // Pointer to the node on the left
    struct node* right; // Pointer to the node on the right
    int vertex;
    long long int key; // Value of the node
    int rank_; // Degree of the node
    int mark;
    char c;
};

void insert_node(int vertex,long long int key,struct node * Vertex_pos[]);
struct node* link(struct node* ptr1,struct node* ptr2);
void cut(struct node* Node);
void reduce_key(struct node* Node,long long int new_val);

struct node* min_node = NULL;

int node_count = 0;

//function to insert a new node int fibonacci heap lazy variant
void insert_node(int vertex,long long int key,struct node * Vertex_pos[])
{
    struct node* new_node = (struct node*)malloc(sizeof(struct node));//allocate memory
    Vertex_pos[vertex]=new_node;//update memory location of node
    new_node->vertex = vertex;
    new_node->key = key;
    new_node->rank_=1;
    new_node->parent = NULL;
    new_node->child = NULL;
    new_node->left = new_node;
    new_node->right = new_node;
    new_node->mark=0;
    new_node->c='N';
    if (min_node != NULL)//insert new node to the left of min node
    {
        (min_node->left)->right = new_node;
        new_node->right = min_node;
        new_node->left = min_node->left;
        min_node->left = new_node;
        if (new_node->key < min_node->key)
            min_node = new_node;
    }
    else
    {
        min_node = new_node;//if its the first node created
    }
    node_count++;//increment node count
}
//funtion to delete min node from fibonacci heap
int del_min()
{
    if(min_node==NULL)
    {
        printf("\nHeap is Empty\n");
        return -1;
    }
    if(node_count==1)//if only one node is left in fobonacci heap
    {
        node_count=0;
        int item = min_node->vertex;
        min_node=NULL;
        return item;
    }
    else
    {
        int min_updated=0;
        struct node* temp = min_node;
        struct node* ptr;
        ptr=temp;
        struct node* X=NULL;
        int item=min_node->vertex;
        //add children of min node to list of roots
        if(temp->child!=NULL)
        {
            X=temp->child;
            do
            {
                ptr=X->right;
                (min_node->left)->right = X;
                X->right = min_node;
                X->left = min_node->left;
                min_node->left = X;
                X->parent=NULL;
                if (X->key < min_node->key)//if childern has value less than min_node update min_node
                {
                    min_node = X;
                    min_updated=1;
                }
                X=ptr;
            }while(ptr!=temp->child);
        }
        //remove the deleted node from list of roots
        (temp->left)->right=temp->right;
        (temp->right)->left=temp->left;
        if(temp==temp->right && temp->child==NULL)//if only one node was left to delete
        {
            min_node=NULL;
        }
        else// if min_node had no children delete it and update min_node pointer
        {
            if(min_updated==0)
            {
                min_node=temp->right;
            }
        }
        node_count--;//decrement node count
        arrange();// call arrange to ensure no two root of same rank exist in the list of roots
        return item;
    }
}
//sweep through the list of roots and link heaps with same root rank i.e ensure no to roots has the same rank
void arrange()
{
    int length=(log(node_count))+10;//maximum number of roots after linking
    struct node* arra[length];//array to store the roots
    for(int i=0;i<length;i++)//initialize array to be NULL
    {
        arra[i]=NULL;
    }
    struct node* temp2=min_node->right;
    struct node* fixed=min_node;
    do
    {
        int rank_ = temp2->rank_;//rank of current node
        if(arra[rank_]==NULL)//if the array doesn't contain any root so no other root of same rank present for now
        {
            arra[rank_]=temp2;
            temp2=temp2->right;
        }
        else// if two roots with same rank found join them and go to next rank position in array
        {
            struct node* linked=NULL;
            int k=rank_;//keep track of array index
            struct node* next_node=temp2->right;
            do
            {
                linked=link(temp2,arra[k]);//link current tree root and previous tree root with sam rank
                arra[k]=NULL;
                k++;
                temp2=linked;
            }while(arra[k]!=NULL);//keep no linking successively until empty position found in array
            arra[k]=linked;//insert the linked root at empty position
            temp2=next_node;
        }
        if(temp2==fixed)//terminating condition for moving through list of roots
        {
            if(temp2->left->rank_==fixed->rank_ && temp2->left!=fixed)
                link(temp2->left,fixed);
            break;

        }
    }while(true);
}
//linking two heaps
struct node* link(struct node* ptr1,struct node* ptr2)
{
    if(ptr1->key<ptr2->key)//compare the key value of roots
    {
        if(min_node==ptr2)
            min_node=min_node->right;//update the min_node if the min_node is made child of other root
        ptr2->parent=ptr1;//update parent pointer
        ptr1->rank_+=1;//increment rank of parent
        (ptr2->left)->right=ptr2->right;//remove the child node from list of roots
        (ptr2->right)->left=ptr2->left;
        // update the child pointers of parent node
        if(ptr1->child!=NULL)//if parent had previous children insert new node into list of childern
        {
            struct node* child=ptr1->child;
            ptr2->right=child->right;
            ptr2->left=child;
            (child->right)->left=ptr2;
            child->right=ptr2;
        }
        else//if parent had no previous children make new node the only childern
        {
            ptr2->left=ptr2;
            ptr2->right=ptr2;
        }
        ptr1->child=ptr2;//update child pointer of parent to new node
        return ptr1;
    }
    else
    {
        if(min_node==ptr1)
            min_node=min_node->right;
        ptr1->parent=ptr2;
        ptr2->rank_+=1;
        (ptr1->left)->right=ptr1->right;
        (ptr1->right)->left=ptr1->left;
        if(ptr2->child!=NULL)
        {
            struct node* child=ptr2->child;
            ptr1->right=child->right;
            ptr1->left=child;
            (child->right)->left=ptr1;
            child->right=ptr1;
        }
        else
        {
            ptr1->right=ptr1;
            ptr1->left=ptr1;
        }
        ptr2->child=ptr1;
    }
    return ptr2;
}

//reduce the key of a node
void reduce_key(struct node* Node,long long int new_val)
{
    if(min_node==NULL)
    {
        printf("\nHeap is empty\n");
    }
    Node->key=new_val;//update to new key value
    if(Node->parent!=NULL && new_val<Node->parent->key)//if reduced value less than parent value cut the node
    {
        cut(Node);
    }
    if(Node->parent==NULL && new_val<min_node->key)//f reduced value less than min_node value and its the root node
    {
        min_node=Node;
    }
}
//subroutine to cut a given node
void cut(struct node* Node)
{
    struct node* root=NULL;
    struct node* temp=Node;
    while(temp->parent!=NULL)
        temp=temp->parent;
    root=temp;
    temp=Node->parent;
    if(Node!=root && Node->parent->mark==0)//if the parent is unmarked
    {
        Node->parent->mark=1;//mark parent
        Node->mark=0;//unmark node
        if(temp->child==Node)//update child pointer of parent if it was pointing to the cut node
        {
            if(Node!=Node->right)
                temp->child=Node->right;
            else
                temp->child=NULL;
        }
        //update sibling pointers of cut node
        (Node->left)->right=Node->right;
        (Node->right)->left=Node->left;
        Node->parent->rank_-=1;//decrement rank of parent
        //add node to list of roots
        (min_node->left)->right = Node;
        Node->right = min_node;
        Node->left = min_node->left;
        min_node->left = Node;
        if (Node->key < min_node->key)//update min_node pointer if required
        {
            min_node = Node;
        }
        Node->parent=NULL;
    }
    else if(Node!=root && Node->parent->mark==1)//if parent was marked repeat the same procedure and cut the parent recursively
    {
        Node->mark=0;
        if(temp->child==Node)
        {
            if(Node!=Node->right)
                temp->child=Node->right;
            else
                temp->child=NULL;
        }
        (Node->left)->right=Node->right;
        (Node->right)->left=Node->left;
        Node->parent->rank_-=1;
        (min_node->left)->right = Node;
        Node->right = min_node;
        Node->left = min_node->left;
        min_node->left = Node;
        if (Node->key < min_node->key)
        {
            min_node = Node;
        }
        Node->parent=NULL;
        cut(temp);
    }
}

#endif // FIB_HEAP_HEADER_H_INCLUDED
