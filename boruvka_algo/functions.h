#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED
#include "vertex_count.h"

int b;
//disjoint set union find structure
struct subset
{
    int parent;
    int rank_;
};
//leftist heap node structure
struct heap_node
{
    int u;
    int v;
    long long int key;
    int sval;
    int type;
    struct heap_node *left;
    struct heap_node *right;
};
//linked list node structure
struct linked_list_node
{
    struct heap_node* root;
    struct linked_list_node* left;
    struct linked_list_node* right;
};

int linked_list_count=0;
//front and end pointer to linked list
struct linked_list_node* front_=NULL;
struct linked_list_node* end_=NULL;
//front and end pointers to perform meld list() operation
struct linked_list_node* meld_front=NULL;
struct linked_list_node* meld_end=NULL;
//structure to store pointer to linked list node
struct linked_list
{
    struct linked_list_node *head;
};
//structure to access the vertex position of any node
struct vertex_pos
{
    int V;
    struct linked_list* array;
};

void insert_list_node(struct linked_list_node* new_node);
struct heap_node * meld(struct heap_node *h1,struct heap_node *h2,struct subset* subsets);
struct heap_node * meld_list(struct heap_node* Node);
struct heap_node * meld_proper(struct heap_node *h1,struct heap_node *h2);
struct heap_node * meld_proper(struct heap_node *h1,struct heap_node *h2);
void del(struct linked_list_node* Node);
struct vertex_pos* init(int v,long long int **edge_cost,struct Graph* graph);
int find_(struct subset subsets[], int i);
void Union(struct subset subsets[], int x, int y);
void find_min2(struct heap_node *root,struct subset subsets[]);
struct heap_node* del_min2(struct heap_node *root,struct subset subsets[]);
//subroutine that create a Vertex structure to store the addresses of nodes in linked list
struct vertex_pos* create_vertex(int v)
{
    struct vertex_pos* Vertex =(struct vertex_pos*)malloc(sizeof(struct vertex_pos));
    Vertex->V=v;
    Vertex->array=(struct linked_list*)malloc((v+1)*sizeof(struct linked_list));
    for(int i=1;i<=v;i++)
    {
        Vertex->array[i].head=NULL;
    }
    return Vertex;
};
//subroutine to insert a new new into the linked list
void insert_list_node(struct linked_list_node* new_node)
{
    if(front_==NULL)
    {
        new_node->left=new_node;
        new_node->right=new_node;
        front_=new_node;
        end_=new_node;
    }
    else
    {
        end_->right=new_node;
        new_node->left=end_;
        new_node->right=front_;
        front_->left=new_node;
        end_=new_node;
    }
    linked_list_count+=1;
};
//subroutine to insert a new node to meld_list queue
void insert_meldlist_node(struct linked_list_node* new_node)
{
    if(meld_front==NULL)
    {
        new_node->left=NULL;
        new_node->right=NULL;
        meld_front=new_node;
        meld_end=new_node;
    }
    else
    {
        meld_end->right=new_node;
        new_node->left=NULL;
        new_node->right=NULL;
        meld_end=new_node;
    }
};
//subroutine to create linked list containing the root of trees of edges incident on that vertex
struct vertex_pos* init(int v,long long int **edge_cost,struct Graph* graph)
{
    struct vertex_pos* Vertex=create_vertex(v);//
    for(int i=1;i<=v;i++)
    {
        int u=i;
        struct linked_list_node *new_linked_node=(struct linked_list_node*)malloc(sizeof(struct linked_list_node));//new linked list for each vertex
        new_linked_node->root=NULL;
        insert_list_node(new_linked_node);
        Vertex->array[u].head=new_linked_node;//update the position of new liked list node for vertex position
        struct AdjListNode* temp = graph->array[i].head;
        //add all the edges incident on that vertex to leftist tree
        while(temp)
        {
            int v=temp->des;
            struct heap_node *new_tree_node=(struct heap_node*)malloc(sizeof(struct heap_node));
            new_tree_node->key=edge_cost[u][v];

            new_tree_node->sval=0;
            new_tree_node->type=1;
            new_tree_node->left=NULL;
            new_tree_node->right=NULL;
            new_tree_node->u=u;
            new_tree_node->v=v;
            new_linked_node->root=meld_proper(new_linked_node->root,new_tree_node);
            temp=temp->next;
        }
    }
    return Vertex;
}
//subroutine for lazy meld
struct heap_node * meld(struct heap_node *h1,struct heap_node *h2,struct subset* subsets)
{
    if(h1==NULL)
        return h2;
    if(h2==NULL)
        return h1;
    struct heap_node *temp=(struct heap_node*)malloc(sizeof(struct heap_node));//create a dummy node
    temp->type=0;
    temp->key=-999;
    temp->u=-111;
    temp->v=-111;
    if(h1->sval>h2->sval)
    {
        temp->left=h1;
        temp->right=h2;
        temp->sval=temp->right->sval+1;
    }
    else
    {
        temp->left=h2;
        temp->right=h1;
        temp->sval=temp->right->sval+1;;
    }
    return temp;
};
//sub routine to implement meld_list operation
struct heap_node * meld_list(struct heap_node* Node)
{
    if(meld_front==NULL)//if no trees to meld
    {
        return NULL;
    }
    if(meld_front->right==NULL)//if only one leftist tree
    {
        struct heap_node* h1=meld_front->root;
        meld_front=NULL;
        meld_end=NULL;
        return h1;
    }
    if(meld_front->right->right==NULL)////if exactly two leftist tree
    {

        struct heap_node* h1=meld_front->root;
        struct heap_node* h2=meld_front->right->root;
        meld_front=NULL;
        meld_end=NULL;
        return meld_proper(h1,h2);
    }
    //melf first two leftist tree
    struct heap_node* h1=meld_front->root;
    struct heap_node* h2=meld_front->right->root;

    struct linked_list_node* temp=meld_front;
    meld_front=meld_front->right->right;//update the front
    temp->root=meld_proper(h1,h2);
    meld_end->right=temp;//insert the merged tree at end
    temp->left=NULL;
    meld_end=temp;
    meld_end->right=NULL;
    meld_front->left=NULL;
    return meld_list(Node);//merge the next trees recursively
};
//sub routine to implement meld operation(NOT LAZY MELD)
struct heap_node * meld_proper(struct heap_node *h1,struct heap_node *h2)
{
    if(h1==NULL)
        return h2;
    if(h2==NULL)
        return h1;
    if(h1->key>h2->key)//make h1 the smaller rooted tree
    {
        struct heap_node *temp=h1;
        h1=h2;
        h2=temp;
    }
    h1->right=meld_proper(h1->right,h2);//recursively merge the right child of h1 and h2 and make merged tree the right child of h1
    if(h1->left==NULL)//if h1 has no left child
    {
        h1->left=h1->right;//move left child to right child
        h1->right=NULL;
    }
    else
    {
        if(h1->right->sval>h1->left->sval)//make the right child as lower s value
        {
            struct heap_node *temp=h1->left;
            h1->left=h1->right;
            h1->right=temp;
        }
        h1->sval=h1->right->sval+1;//increment s value
    }
    return h1;
};
//sub routine to delete linked list node
void del(struct linked_list_node* Node)
{
    if(Node==front_)
    {
        struct linked_list_node* temp=front_;
        front_=front_->right;
        free(temp);
        front_->left=end_;
        end_->right=front_;
    }
    else if(Node==end_)
    {
        struct linked_list_node* temp=end_;
        end_=end_->left;
        free(temp);
        front_->left=end_;
        end_->right=front_;
    }
    else
    {
        struct linked_list_node* temp=Node;
        Node->left->right=Node->right;
        Node->right->left=Node->left;
        free(temp);
    }
}
//subroutine for disjoint set union find() operation
int find_(struct subset subsets[], int i)
{
    if (subsets[i].parent != i)
      subsets[i].parent=find_(subsets, subsets[i].parent);

    return subsets[i].parent;
}
//union of two disjoint set
void Union(struct subset subsets[], int x, int y)
{
    int xroot = find_(subsets, x);
    int yroot = find_(subsets, y);
    if (subsets[xroot].rank_ < subsets[yroot].rank_)
        subsets[xroot].parent = yroot;
    else if (subsets[xroot].rank_ > subsets[yroot].rank_)
        subsets[yroot].parent = xroot;
    else
    {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank_++;
    }
}
//subrotine to implement find_min() opreartion
void find_min2(struct heap_node *root,struct subset subsets[])
{
    if(root!=NULL)
    {
        if(root->type==1)
        {
            struct linked_list_node* meld_list_node=(struct linked_list_node*)malloc(sizeof(struct linked_list_node));
            meld_list_node->root=root;
            int u=root->u;
            int v=root->v;
            if(find_(subsets,u)==find_(subsets,v))//if edge belong to same set delete it
            {
                find_min2(root->left,subsets);
                find_min2(root->right,subsets);
                free(root);
            }
            else
            {
                insert_meldlist_node(meld_list_node);//non dummy node and edges are not in same set
            }
        }
        else// dummy node so delete it
        {
            find_min2(root->left,subsets);
            find_min2(root->right,subsets);
            free(root);
        }
    }

};
//lazy delete() function
struct heap_node* del_min2(struct heap_node *root,struct subset subsets[])
{
    root->type=0;
    return root;
};

#endif // FUNCTIONS_H_INCLUDED
