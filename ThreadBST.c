#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
// convention is taken rthread(p)=1 if there is no right child of p
// and lthread(p)=1 if there is no left child of p
struct node
{
     struct node *left;
     struct node *right;
     int info;
     int rthread;
     int lthread;
};

struct node *tree=NULL;
void maketree(int n);
void createtree(int n);
void insert(struct node *, int x);
struct node * search(struct node *tree ,int x);
struct node* insuccessor(struct node *x);
struct node*   inpredecessor(struct node *x);
void inorder(struct node *p);
void preorder( struct node *p);
void setleft(struct node *p,int x);
void setright(struct node *p,int x);

void main()
{
     int a,n,x,c,b,ch,e;
     struct node *p;
     //clrscr();
    do
     {
	  printf("\n 1.Create 2. Insert \t 3. Search");
	  printf("\n 4.Inoder Traversal \t 5.Preorder Traversal");
	  printf("\n 6.Inorder Predecessor \t 7.Inorder Successor ");
	  printf("\n 8.To Exit \n Enter your choice:");
	  scanf("%d",&ch);
	  switch(ch)
	  {
	     case 1: printf("\n Enter how many nodes");
		     scanf("%d",&n);
		     createtree(n);
		     inorder(tree);
		     break;
	     case 2: printf("\n Enter new node value to insert");
		     scanf("%d",&x);
		     insert(tree,x);
		     inorder(tree);
		     break;

	     case 3: printf("\n enter element to search");
		     scanf("%d",&x);
		     p=search(tree,x);
		      if(p==NULL)
			 printf("\n node is not present");
		      else
		      printf("\n node is present");
		     break;
	     case 4:
		    inorder(tree);
		    break;

	     case 5:  preorder(tree);
		     break;
	     case 6: printf("\n Enter element whose predecessor you want");
		     scanf("%d",&x);
		     p=search(tree,x);
		      if(p==NULL)
			 printf("\n Existing node not present");
		      else
		      { p=inpredecessor(p);
		       if(p==NULL)
			 printf("\n no predecessor exist");
		       else
		       printf("\n The predecessor of %d is %d",x,p->info);
		       }
		     break;
	      case 7: printf("\n Enter element whose successor you want");
		     scanf("%d",&x);
		     p=search(tree,x);
		     if(p==NULL)
			 printf("\n Existing node not present");
		      else
		      {  p=insuccessor(p);
			if(p==NULL)
			 printf("\n no successor exist");
			else
			printf("\n The successor of %d is %d",x,p->info);
			}
		     break;

	     case 8:   printf("\n thank you");
		     break;
	  }//switch
	  fflush(stdin);
     }while(ch>=1 && ch <=7);
     getch();
}

// search a node from TBT
struct node * search(struct node *tree ,int x)
{
     struct node *p,*q;
     p=tree;

    if(tree==NULL || tree->info==x)  return p;
    else if( x< tree->info)
      {  if(tree->lthread==1)  return NULL;
	     else
	      return search(tree->left,x);
	      
      }
    else if (x >tree->info)
	  {  if(tree->rthread==1) return NULL;
	     else
	        return search(tree->right,x);
	      
	  }
 }

// Create a single node  and point to tree
void maketree(int x)
{
     struct node *p;
     p=(struct node *)malloc(sizeof(struct node));
     p->info=x;
     p->left=NULL;
     p->right=NULL;
     p->rthread=1;  // p->right is thread pointer
     p->lthread=1; // p->left is thread pointer
     tree=p;
}

// create a TBT using n nodes
void createtree(int n)
{  int i,x;
   printf("\n Enter the %d values");
   for(i=0;i<n;i++)
    {
      scanf("%d",&x);
       if(i==0)  maketree(x);
       else
	  insert(tree,x);
     }
}

// Insert a node into TBT
void insert(struct node *tree, int x)
{
    
     if(tree==NULL) maketree(x);
      else if( x< tree->info)
      { if(tree->lthread==1)  setleft(tree,x);
	    else
	     { insert(tree->left,x);
	     }
       }
    else if (x >=tree->info)
	 {  if(tree->rthread==1) setright(tree,x);
	   else
	      { insert(tree->right,x);
	      }
	 }
  }

// Set a new node to left of node P
void setleft(struct node *p, int x)
 {
     struct node *q,*r;
       q=(struct node *)malloc(sizeof(struct node));
       q->info=x;
       r=p->left;
       q->left=r;
       p->left=q;
       q->right=p;
       q->rthread=1;
       q->lthread=1;
       p->lthread=0;
  }


// Set a new node to right of node P
void setright(struct node *p,int x)
{
     struct node *q,*r;
     if(p==NULL)
	  printf("\ncan't insert");
     else if(p->rthread==0)
	  printf("\n void insertion");
	  else
	  {
	       q=(struct node *)malloc(sizeof(struct node));
	       q->info=x;
	       r=p->right;
	       p->right=q;
	       q->right=r;
	       p->rthread=0;
	       q->rthread=1;
	       q->left=p;
	       q->lthread=1;
	  }
}

//Find successor of a given node x
struct node* insuccessor(struct node *x)
{
    struct node *s;
    s=x->right;
    if(x->rthread==0)
     {
	while(s->lthread==0)
	   s=s->left;
      }
   return s;
 }

// Find the predecessor of a given node p;
struct node*   inpredecessor(struct node *x)
{
    struct node *p;
    p=x->left;
    if(x->lthread==0)
      {
	 while(p->lthread==0)
	    p=p->left;
       }
    return p;
}

// Preorder traversal of TBT
void preorder( struct node *p)
{
  struct node *q;
   do
     {
	  q=p;
	  while((p!=NULL)&&(p->lthread==0))
	  {    printf("%d\t",p->info);
	       p=p->left;
	       q=p;
	  }
	  if(q!=NULL)
	  {
	      printf("%d\t",q->info);
	      p=q->right;
	    while((p!=NULL)&&(q->rthread==1))
	      {
		   //printf("%d\t",p->info);
		   q=p;
		   p=p->right;
	      }
		  }
     }while(p!=NULL);
 }

 //Inorder traveral of TBT
void inorder(struct node *p)
{
     struct node *q;
     do
     {	  q=p;
	    while((p!=NULL)&&(p->lthread==0))
	     {
	       p=p->left;
	       q=p;
	     }
	  if(q!=NULL)
	    {
	      printf("%d\t",q->info);
	      p=q->right;
	      while((p!=NULL)&&(q->rthread==1))
	      {
		   printf("%d\t",p->info);
		   q=p;
		   p=p->right;
	      }//while
	  }//if
     }while(p!=NULL);
}




