#include <stdio.h>
#include <stdlib.h>
#include "splay.h"

int pi;

void splay(struct vertex *v)
{
    /*printf("\nsplay entry\n");
    print_all2();
    scanf("%d",&pi);*/

    //printf("\ncheck 1\n");
    pass1(v);
    //printf("\ncheck 2\n");

    /*printf("\nsplay after pass1\n");
    print_all2();
    scanf("%d",&pi);*/

    pass2(v);
    //printf("\ncheck 3\n");

    /*printf("\nsplay after pass2\n");
    print_all2();
    scanf("%d",&pi);*/

    pass3(v);
    //printf("\ncheck 4\n");

    /*printf("\nsplay exit\n");
    print_all2();
    scanf("%d",&pi);*/
}

void pass1(struct vertex *v)
{
    struct vertex *P=v->parent;
    struct vertex *G=NULL;
    while(P!=NULL)
    {
        if(P!=NULL)
            G=P->parent;
        else
            G=NULL;

        if(G==NULL)
        {
            if(P->lc==v)
            {
               // printf("\n call 1\n");
                right_rotate(P);
            }
            else
            {
               // printf("\n call 2\n");
                left_rotate(P);
            }
        }
        else
        {
            if(G->lc==P)
            {
                if(P->lc==v)
                {
                    //printf("\n call 3\n");
                    right_rotate(G);
                    right_rotate(P);
                }
                else
                {
                    //printf("\n call 4\n");
                    left_rotate(P);
                    right_rotate(G);
                }
            }
            else
            {
                if(P->rc==v)
                {
                    //printf("\n call 5\n");
                    left_rotate(G);
                    left_rotate(P);
                }
                else
                {
                    //printf("\n call 6\n");
                    right_rotate(P);
                    left_rotate(G);
                }
            }
        }
        P=v->parent;
    }
    if(v->successor!=NULL)
        pass1(v->successor);
};

void right_rotate(struct vertex *w)
{
    struct vertex *v=w->lc;
    struct vertex *a=v->lc;
    struct vertex *b=v->rc;
    struct vertex *c=w->rc;


    struct vertex *w_par=NULL;
    if(w->parent!=NULL)
    {
        w_par=w->parent;
        if(w_par->lc==w)
        {
            w_par->lc=v;
        }
        else if(w_par->rc==w)
        {
            w_par->rc=v;
        }
    }

    v->rc=w;
    v->parent=w->parent;
    v->successor=w->successor;
    w->parent=v;
    w->successor=NULL;
    w->lc=b;
    if(b!=NULL)
        b->parent=w;

    int v_dcost=v->dcost,a_dcost=0,a_dmin=0,b_dcost=0,b_dmin=0,c_dcost=0,c_dmin=0;
    v->dcost=v->dcost+w->dcost;
    w->dcost=-v_dcost;

    if(b!=NULL)
    {
        b->dcost=v_dcost+b->dcost;
        b_dcost=b->dcost;
        b_dmin=b->dmin;
    }
    if(a!=NULL)
    {
        a_dcost=a->dcost;
        a_dmin=a->dmin;
    }
    if(c!=NULL)
    {
        c_dcost=c->dcost;
        c_dmin=c->dmin;
    }
    w->dmin=maximum(0,b_dmin-b_dcost,c_dmin-c_dcost);
    v->dmin=maximum(0,a_dmin-a_dcost,w->dmin-w->dcost);

}

void left_rotate(struct vertex *w)
{

    struct vertex *v=w->rc;
    struct vertex *a=v->rc;
    struct vertex *b=v->lc;
    struct vertex *c=w->lc;

    struct vertex *w_par=NULL;
    if(w->parent!=NULL)
    {
        w_par=w->parent;
        if(w_par->lc==w)
        {
            w_par->lc=v;
        }
        else if(w_par->rc==w)
        {
            w_par->rc=v;
        }
    }

    v->lc=w;
    v->parent=w->parent;
    v->successor=w->successor;
    w->parent=v;
    w->successor=NULL;
    w->rc=b;
    if(b!=NULL)
        b->parent=w;

    int v_dcost=v->dcost,a_dcost=0,a_dmin=0,b_dcost=0,b_dmin=0,c_dcost=0,c_dmin=0;
    v->dcost=v->dcost+w->dcost;
    w->dcost=-v_dcost;
    if(b!=NULL)
    {
        b->dcost=v_dcost+b->dcost;
        b_dcost=b->dcost;
        b_dmin=b->dmin;
    }
    if(a!=NULL)
    {
        a_dcost=a->dcost;
        a_dmin=a->dmin;
    }
    if(c!=NULL)
    {
        c_dcost=c->dcost;
        c_dmin=c->dmin;
    }
    w->dmin=maximum(0,b_dmin-b_dcost,c_dmin-c_dcost);
    v->dmin=maximum(0,a_dmin-a_dcost,w->dmin-w->dcost);
}

void pass2(struct vertex *v)
{
    struct vertex *w=v->successor;
    while(w!=NULL)
    {
        struct vertex *u=w->lc;

        w->lc=v;
        v->parent=w;
        v->successor=NULL;

        if(u!=NULL)
        {
            u->parent=NULL;
            u->successor=w;
        }
        struct vertex *d=w->rc;

        v->dcost=v->dcost-w->dcost;
        if(u!=NULL)
        {
            u->dcost=u->dcost+w->dcost;
        }
        int right_w_dmin=0,right_w_dcost=0;
        if(d!=NULL)
        {
            right_w_dmin=d->dmin;
            right_w_dcost=d->dcost;
        }
        w->dmin=maximum(0,v->dmin-v->dcost,right_w_dmin-right_w_dcost);
        w=w->successor;
    }
}

void pass3(struct vertex *v)
{
    pass1(v);
}

int maximum(int n1,int n2,int n3)
{
    return (n1 > n2) ? (n1 > n3 ? n1 : n3) : (n2 > n3 ? n2 : n3);
}

void normal_splay(struct vertex *v)
{
    struct vertex *P=v->parent;
    struct vertex *G=NULL;
    while(P!=NULL)
    {
        if(P!=NULL)
            G=P->parent;
        else
            G=NULL;

        if(G==NULL)
        {
            if(P->lc==v)
            {
               // printf("\n call 1\n");
                right_rotate(P);
            }
            else
            {
               // printf("\n call 2\n");
                left_rotate(P);
            }
        }
        else
        {
            if(G->lc==P)
            {
                if(P->lc==v)
                {
                    //printf("\n call 3\n");
                    right_rotate(G);
                    right_rotate(P);
                }
                else
                {
                    //printf("\n call 4\n");
                    left_rotate(P);
                    right_rotate(G);
                }
            }
            else
            {
                if(P->rc==v)
                {
                    //printf("\n call 5\n");
                    left_rotate(G);
                    left_rotate(P);
                }
                else
                {
                    //printf("\n call 6\n");
                    right_rotate(P);
                    left_rotate(G);
                }
            }
        }
        P=v->parent;
    }
}

