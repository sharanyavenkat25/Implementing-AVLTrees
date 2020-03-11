#include<stdio.h>
#include<time.h>
typedef struct{
        int id;
        int marks;
}stud;
 
typedef struct node
{
	stud st;
	struct node *left;
	struct node *right;
	int height;
}node;


node *insertAVL(node *,int,int);
node *insertBST(node *,int,int);
node *rotateright(node *);
node *rotateleft(node *);
node *RightRight(node *);
node *LeftLeft(node *);
node *LeftRight(node *);
node *RightLeft(node *);
node *newNode(int,int);
int BalanceFactor(node *);
int height( node *);
void preorder(node *);
void inorder(node *);
int Search(node *root, int key);


node *newNode(int id,int marks) 
{   stud st;
    node *temp =  (node*)malloc(sizeof(node)); 
    temp->st.id=id;
    temp ->st.marks =marks; 
    temp->left = temp->right = NULL; 
    return temp; 
} 

node * rotateright(node *x)
{
	node *y;
	y=x->left;
	x->left=y->right;
	y->right=x;
	x->height=height(x);
	y->height=height(y);
	return(y);
}
 
node * rotateleft(node *x)
{
	node *y;
	y=x->right;
	x->right=y->left;
	y->left=x;
	x->height=height(x);
	y->height=height(y);
	
	return(y);
}

node * RightRight(node *T)
{
	T=rotateleft(T);
	return(T);
}
 
node * LeftLeft(node *T)
{
	T=rotateright(T);
	return(T);
}
 
node * LeftRight(node *T)
{
	T->left=rotateleft(T->left);
	T=rotateright(T);
	
	return(T);
}
 
node * RightLeft(node *T)
{
	T->right=rotateright(T->right);
	T=rotateleft(T);
	return(T);
}

int BalanceFactor(node *T)
{
	int lh,rh;
	if(T==NULL)
		return(0);
 
	if(T->left==NULL)
		lh=0;
	else
		lh=1+T->left->height;
 
	if(T->right==NULL)
		rh=0;
	else
		rh=1+T->right->height;
 
	return(lh-rh);
}

int height(node *T)
{
	int lh,rh;
	if(T==NULL)
		return(0);
	
	if(T->left==NULL)
		lh=0;
	else
		lh=1+T->left->height;
		
	if(T->right==NULL)
		rh=0;
	else
		rh=1+T->right->height;
	
	if(lh>rh)
		return(lh);
	
	return(rh);
}

node * insertAVL(node *T,int id,int marks)
{	stud st;
	if(T==NULL)
	{
		T=(node*)malloc(sizeof(node));
		T->st.id=id;
		T->st.marks=marks;
		T->left=NULL;
		T->right=NULL;
	}
	else
		if(id > T->st.id)		// insert in right subtree
		{
			T->right=insertAVL(T->right,id,marks);
			if(BalanceFactor(T)==-2)
				if(id > T->right->st.id)
					T=RightRight(T);
				else
					T=RightLeft(T);
		}
		else
			if(id < T->st.id) //insert in left subtree
			{
				T->left=insertAVL(T->left,id,marks);
				if(BalanceFactor(T)==2)
					if(id < T->left->st.id)
						T=LeftLeft(T);
					else
						T=LeftRight(T);
			}
		
		T->height=height(T);
		
		return(T);
}


node* insertBST(node* node, int id,int marks) 
{   stud st;
   
    if (node == NULL) return newNode(id,marks); 
  
    
    if (id < node->st.id) 
        node->left  = insertBST(node->left,id,marks); 
    else if (id > node->st.id) 
        node->right = insertBST(node->right,id,marks);    
  
    /* return the (unchanged) node pointer */
    node->height=height(node);
    return node;
} 

int Search(node *root, int key) 
{ stud st;
    // Traverse untill root reaches to dead end 
    while (root != NULL) 
    { 
        // pass right subtree as new tree 
        if (key > root->st.id) 
            root = root->right; 
  
        // pass left subtree as new tree 
        else if (key < root->st.id) 
            root = root->left; 
        else
            return 1;// if the key is found return 1 
    } 
    return 0; 
} 

void preorder(node *T)
{ stud st;
	if(T!=NULL)
	{
		printf("%d %d (Bf=%d)\n",T->st.id,T->st.marks,BalanceFactor(T));
		preorder(T->left);
		preorder(T->right);
	}
}
 


int main()
{	
	struct timespec start,stop;
	double t1,t2,t3,t4;
	node *root1=NULL;
	node *root2=NULL;
	int x,n,i,op,studid;
	char choice;
	
	
	//printf("hello");
	
	do
	{
		printf("\n1)Create:");
		printf("\n2)Insert:");
		printf("\n3)Search:");
		printf("\n4)Print:\n");
		
	
		//printf("\n\nEnter Your Choice: ");
		scanf("%d",&op);
		
		switch(op)
		{
			case 1: printf("\nEnter no. of elements: ");
					scanf("%d",&n);
					int *arr=(int*)malloc(sizeof(int)*n);
					int *id=(int*)malloc(sizeof(int)*n);

					//printf("\nEnter tree data: \n");
					root1=NULL;
					root2=NULL;
					for(i=0;i<n;i++)
					{
						scanf("%d %d",&id[i],&arr[i]);
						/*root1=insertAVL(root1,x);
						root2=insertBST(root2,x);*/
					}
					clock_gettime(CLOCK_REALTIME,&start);
					for(i=0;i<n;i++)
					{
						root1=insertAVL(root1,id[i],arr[i]);
					}
					clock_gettime(CLOCK_REALTIME,&stop);
					t1=difftime(stop.tv_nsec,start.tv_nsec);

					clock_gettime(CLOCK_REALTIME,&start);
					for(i=0;i<n;i++)
					{
						root2=insertBST(root2,id[i],arr[i]);
					}
					clock_gettime(CLOCK_REALTIME,&stop);
					t2=difftime(stop.tv_nsec,start.tv_nsec);

					printf("\nAVL tree and BST tree has been successfully created\n");
					printf("\nTime taken for AVL tree: %lf sec\n",t1/1000000000);
					printf("\nTime taken for BST tree: %lf sec\n",t2/1000000000);

					break;
				
			case 2: printf("\nEnter a data (id , marks): ");
					scanf("%d %d",&studid,&x);
					clock_gettime(CLOCK_REALTIME,&start);
					root1=insertAVL(root1,studid,x);
					clock_gettime(CLOCK_REALTIME,&stop);
					t3=difftime(stop.tv_nsec,start.tv_nsec);

					clock_gettime(CLOCK_REALTIME,&start);
					root2=insertBST(root2,studid,x);
					clock_gettime(CLOCK_REALTIME,&stop);
					t4=difftime(stop.tv_nsec,start.tv_nsec);

					printf("\nData has been successfully inserted into the tree\n");
					printf("\nTime taken for insertion in AVL tree: %lf sec",t3/1000000000);
					printf("\nTime taken for insertion in BST tree: %lf sec",t4/1000000000);

					break;


			case 3: printf("\nEnter id to be searched\n");
					   scanf("%d",&x);
					   int search1,search2;
					   clock_gettime(CLOCK_REALTIME,&start);
					   search1=Search(root1,x);
					   clock_gettime(CLOCK_REALTIME,&stop);
					   t3=difftime(stop.tv_nsec,start.tv_nsec);

					   clock_gettime(CLOCK_REALTIME,&start);
					   search2=Search(root2,x);
					   clock_gettime(CLOCK_REALTIME,&stop);
					   t4=difftime(stop.tv_nsec,start.tv_nsec);

					   if(search1 && search2)
					   {
					   	printf("\nData has been found in the tree\n");

						printf("\nTime taken for search in AVL tree: %lf sec",t3/1000000000);
						printf("\nTime taken for search in BST tree: %lf sec",t4/1000000000);
					   }
					   else
					   	printf("Data not found");
					   break;
			
			case 4: printf("\nAVL:\n");
					preorder(root1);
					
					printf("\nBST\n");
					preorder(root2);
					//printf("\n\nInorder sequence:\n");
					printf("\n");
					break;
				
				
			default : printf("\nEnter Valid choice");
		}
		printf("\nDo you want to perform another operation? (y/n)  : ");
		scanf("%s",&choice);
	
}while(choice=='y');
	
	return 0;
}

