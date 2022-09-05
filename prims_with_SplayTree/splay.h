#ifndef SPLAY_H_INCLUDED
#define SPLAY_H_INCLUDED
//node structure of splay tree
struct node
{
    struct node* parent;
    struct node* left;
    struct node* right;
    int vertex;
    long long int key;
};

void insert_node(int vertex,long long int key);
struct node* splay(struct node* root,long long int key);
struct node* rightRotate(struct node* Node);
struct node* leftRotate(struct node* Node);
int del_min();
void reduce_key(long long int key,int new_vel,int vertex);

struct node* root = NULL;
int node_count=0;
//subroutine to insert a new node
void insert_node(int vertex,long long int key)
{
    struct node* new_node = (struct node*)malloc(sizeof(struct node));
    new_node->vertex = vertex;
    new_node->key = key;
    if(root==NULL)
    {
        new_node->left=NULL;
        new_node->right=NULL;
        new_node->parent=NULL;
    }
    else
    {
        root=splay(root,key);//bring the node just smaller or grater than new node to root
        if(root->key>key)//make old tree right child of new node
        {
            new_node->right=root;
            new_node->left=root->left;
            root->left=NULL;
        }
        else//make old tree left child of new node
        {
            new_node->left=root;
            new_node->right=root->right;
            root->right=NULL;
        }
    }
     root=new_node;//update root pointer
     node_count++;//increment node count
}
//subroutine to splay given the key value
struct node* splay(struct node* root,long long int key)
{
    if(root==NULL || root->key==key)
        return root;
    if(key<root->key)//key is in left subtree
    {
        if(root->left==NULL)//if key not in tree
            return root;
        //left-left pattern
        if(key<root->left->key)
        {
            root->left->left=splay(root->left->left,key);//recursively bring the key node as left child of root left
            root = rightRotate(root);//first rotate root
        }
        //left-right pattern
        else if(key>root->left->key)
        {
            root->left->right=splay(root->left->right,key);//recursively bring the key node as right child of root left
            if(root->left->right!=NULL)
                root->left=leftRotate(root->left);//first rotation for root left
        }
        return (root->left==NULL)?root:rightRotate(root);//second rotation if required
    }
    else
    {
        if(root->right==NULL)
            return root;
        if(key<root->right->key)
        {
            root->right->left=splay(root->right->left,key);
            if(root->right->left!=NULL)
                root->right = rightRotate(root->right);
        }
        else if(key>root->right->key)
        {
            root->right->right=splay(root->right->right,key);
            root=leftRotate(root);
        }
        return (root->right==NULL)?root:leftRotate(root);
    }
}
//subroutine for single right rotation
struct node* rightRotate(struct node* Node)
{
    struct node* temp=Node->left;
    Node->left=temp->right;
    temp->right=Node;
    return temp;
};
//subroutine for single left rotation
struct node* leftRotate(struct node* Node)
{
    struct node* temp=Node->right;
    Node->right=temp->left;
    temp->left=Node;
    return temp;
};
//subroutine to delete the minimum item
int del_min()
{
    if(root==NULL)
    {
        printf("\nEmpty\n");
        return -1;
    }
    struct node* temp=splay(root,-1);//bring the min item to root and store in temp
    struct node* left_tree=splay(temp->left,99999999999999);//bring the largest element of left sub tree to root and store
    struct node* right_tree=temp->right;//right subtree
    int item=temp->vertex;//item to return
    free(temp);
    if(left_tree!=NULL)//merge left and right tree
    {
        left_tree->right=right_tree;
        root=left_tree;
    }
    else
    {
        root=right_tree;
    }
    node_count--;
    return item;
}
//subroutine to reduce key IMPLEMENTED AS DELTE THE NODE AND INSERT NEW NODE WITH REDUCED VALUE
void reduce_key(long long int key,int new_vel,int vertex)
{
    struct node* temp=splay(root,key);
    struct node* left_tree=splay(temp->left,99999999999999);
    struct node* right_tree=temp->right;
    if(left_tree!=NULL)
    {
        left_tree->right=right_tree;
        root=left_tree;
    }
    else
    {
        root=right_tree;
    }
    node_count--;
    free(temp);//delete the node
    insert_node(vertex,new_vel);//Inserting new node with reduced value
}

#endif // SPLAY_H_INCLUDED
