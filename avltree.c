#include<stdio.h>
#include<stdlib.h>

typedef struct node
{
    	int data;
    	struct node*  left;
    	struct node*  right;
    	int height;
} node;
 
 
void dispose(node* t);
node* find( int e, node *t );
node* findmin( node *t );
node* findmax( node *t );
node* insert( int data, node *t );
node* delete( int data, node *t );
void display(node* t);
int get( node* n );


void dispose(node* t)
{
    	if( t != NULL )
    	{
		dispose( t->left );
	        dispose( t->right );
        	free( t );
    	}
}

node* find(int e, node* t )
{
    	if( t == NULL )
        	return NULL;
    	if( e < t->data )
        	return find( e, t->left );
    	else if( e > t->data )
        	return find( e, t->right );
    	else
        	return t;
}
 
node* findmin( node* t )
{
    	if( t == NULL )
        	return NULL;
    	else if( t->left == NULL )
        	return t;
    	else
        	return findmin( t->left );
}
 
node* findmax( node* t )
{
    	if( t != NULL )
        	while( t->right != NULL )
            	t = t->right;
 
    	return t;
}
 
static int height( node* n )
{
    	if( n == NULL )
        	return -1;
    	else
        	return n->height;
}
 
static int max( int l, int r)
{
    	return l > r ? l: r;
}
 
static node* srlft( node* k2 )
{
    	node* k1 = NULL;
    	k1 = k2->left;
    	k2->left = k1->right;
    	k1->right = k2;
    	k2->height = max( height( k2->left ), height( k2->right ) ) + 1;
    	k1->height = max( height( k1->left ), k2->height ) + 1;
    	return k1; 
}
 
static node* srrht( node* k1 )
{
    	node* k2;
 	k2 = k1->right;
    	k1->right = k2->left;
    	k2->left = k1;
    	k1->height = max( height( k1->left ), height( k1->right ) ) + 1;
    	k2->height = max( height( k2->right ), k1->height ) + 1;
 	return k2; 
}

static node* drlft( node* k3 )
{
    	k3->left = srlft( k3->left );
    	return srlft( k3 );
}

static node* drrht( node* k1 )
{
    	k1->right = srlft( k1->right );
    	return srrht( k1 );
}
 
node* insert(int e, node* t )
{
    	if( t == NULL )
    	{
        	t = (node*)malloc(sizeof(node));
        	if( t == NULL )
        	{
            		exit(1);
        	}
        	else
        	{
            		t->data = e;
            		t->height = 0;
            		t->left = t->right = NULL;
        	}
    	}
    	else if( e < t->data )
    	{
        	t->left = insert( e, t->left );
        	if( height( t->left ) - height( t->right ) == 2 )
            		if( e < t->left->data )
                		t = srlft( t );
            		else
                		t = drlft( t );
    	}
    	else if( e > t->data )
    	{
        	t->right = insert( e, t->right );
        	if( height( t->right ) - height( t->left ) == 2 )
            		if( e > t->right->data )
                		t = srrht( t );
            		else
                		t = drrht( t );
    	}
    	t->height = max( height( t->left ), height( t->right ) ) + 1;
   	return t;
}
 
node* delete( int e, node* t )
{
    	return t;
}

int get(node* n)
{
    	return n->data;
}
 
void display(node* t)
{
    	if (t == NULL)
        	return;
    	printf("%d",t->data);
    	if(t->left != NULL)
        	printf("(Lft:%d)",t->left->data);
    	if(t->right != NULL)
        	printf("(Rht:%d)",t->right->data);
    	printf("\n");
    	display(t->left);
    	display(t->right);
}

int main()
{
    	printf("\n---AVL tree---\n\n\n");
   	node *t;
   	t = NULL;
    	printf("-Display-\n\n");
	t=insert(1,t);
    	t=insert(3,t);
    	t=insert(6,t);
    	t=insert(8,t);
    	t=insert(4,t);
    	display(t);
    	dispose(t);
    	return 0;
}
