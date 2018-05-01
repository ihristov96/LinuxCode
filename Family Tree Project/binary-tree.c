/*
 ============================================================================
 Name        : weight_balanced_tree.c
 Author      : 
 Version     :
 Copyright   : 
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

typedef int bool;
#define true 1
#define false 0
#define male_flag 0x00000020
#define ac_flag 0x80000000
#define EMPTY_SPACE -1

// A tree node
typedef struct nodeStruct
{
	//Weight balanced tree data
	struct nodeStruct* bt_left;
	struct nodeStruct* bt_right;
	int height;

	//Personal info
	int birth_year;
	int birth_month;
	int birth_day;
	int birth_order;
	char name[10];
	char surname[20];
	char partnerName[10];
	char partnerSurname[20];
	bool isMale;
	bool isAlive;

	//Other info
	unsigned int ID;
	struct nodeStruct* ft_parent;
} s_node;

unsigned long idGenerator(s_node node)
{
	unsigned long ID = 0x00000000;

	if (node.isMale)
	{
		ID |= male_flag;
	}

	if (node.birth_year > 0)
	{
		ID |= ac_flag;
	}

	ID |= (abs(node.birth_year) << 19);
	ID |= (node.birth_month << 15);
	ID |= (node.birth_day << 10);
	ID |= (node.birth_order << 6);

	return ID;
}

/* Allocates a new node*/
s_node* createNode(int birth_year, int birth_month, int birth_day, int birth_order, char* name, char* surname, bool isMale, bool isAlive, s_node* parent)
{
	char* c;
	int idx = 0;

    s_node* node = (s_node*)malloc(sizeof(s_node));

    node->bt_left   = NULL;
    node->bt_right  = NULL;

    node->height = 1;  // new node is initially added at leaf

	node->birth_year = birth_year;
	node->birth_month = birth_month;
	node->birth_day = birth_day;
	node->birth_order = birth_order;

	c = name;
	while('\0' != *c)
	{
		if (idx >= sizeof(node->name) - 1)
		{
			free(node);
			return NULL;
		}
		node->name[idx] = *c;
		idx++;
		c++;
	}
	node->name[idx] = '\0';
	idx = 0;

	c = surname;
	while('\0' != *c)
	{
		if (idx >= sizeof(node->surname) - 1)
		{
			free(node);
			return NULL;
		}
		node->surname[idx] = *c;
		idx++;
		c++;
	}
	node->surname[idx] = '\0';
	idx = 0;

	node->isMale = isMale;
	node->isAlive = isAlive;

	node->ft_parent = parent;

    node->ID = idGenerator(*node);

    return(node);
}
/* TEST ONLY. actual createNode is above*/
s_node* TESTcreateNode(int ID)
{
    s_node* node = (s_node*)malloc(sizeof(s_node));

    node->bt_left   = NULL;
    node->bt_right  = NULL;

    node->height = 1;  // new node is initially added at leaf

    node->ID = ID;

    return(node);
}

int max(int a, int b)
{
    return (a > b)? a : b;
}

int height(s_node *node)
{
    if (node == NULL)
        return 0;
    return node->height;
}

// A utility function to right rotate subtree rooted with y
s_node *rightRotate(s_node *y)
{
	s_node *x = y->bt_left;
	s_node *T2 = x->bt_right;

    // Perform rotation
    x->bt_right = y;
    y->bt_left = T2;

    // Update heights
    y->height = max(height(y->bt_left), height(y->bt_right))+1;
    x->height = max(height(x->bt_left), height(x->bt_right))+1;

    // Return new root
    return x;
}

// A utility function to left rotate subtree rooted with x
s_node *leftRotate(s_node *y)
{
	s_node *x = y->bt_right;
	s_node *T2 = x->bt_left;

    // Perform rotation
    x->bt_left = y;
    y->bt_right = T2;

    //  Update heights
    y->height = max(height(y->bt_left), height(y->bt_right))+1;
    x->height = max(height(x->bt_left), height(x->bt_right))+1;

    // Return new root
    return x;
}

// Get Balance factor of node N
int getBalance(s_node *N)
{
    if (N == NULL)
        return 0;
    return height(N->bt_left) - height(N->bt_right);
}

// Recursive function to insert key in subtree rooted
// with node and returns new root of subtree.
s_node* insert(s_node* root, s_node* node)
{
    /* 1.  Perform the normal insertion */
    if (root == NULL)
        return(node);

    if (node->ID < root->ID)
    {
        root->bt_left  = insert(root->bt_left, node);
    }
    else if (node->ID > root->ID)
    {
        root->bt_right = insert(root->bt_right, node);
    }
    else // Equal keys are not allowed
        return root;

    /* 2. Update height of this ancestor node */
    root->height = 1 + max(height(root->bt_left),
                           height(root->bt_right));

    /* 3. Get the balance factor of this ancestor
          node to check whether this node became
          unbalanced */
    int balance = getBalance(root);

    // If this node becomes unbalanced, then
    // there are 4 cases

    // Left Left Case
    if (balance > 1 && node->ID < root->bt_left->ID)
        return rightRotate(root);

    // Right Right Case
    if (balance < -1 && node->ID > root->bt_right->ID)
        return leftRotate(root);

    // Left Right Case
    if (balance > 1 && node->ID > root->bt_left->ID)
    {
        root->bt_left =  leftRotate(root->bt_left);
        return rightRotate(root);
    }

    // Right Left Case
    if (balance < -1 && node->ID < root->bt_right->ID)
    {
        root->bt_right = rightRotate(root->bt_right);
        return leftRotate(root);
    }

    /* return the (unchanged) node pointer */
    return root;
}

//-----------------------------------------------------------------------------
//Print functuions
// Function to print binary tree in 2D
#define COUNT 10
void print2DUtil(s_node *root, int space)
{
    // Base case
    if (root == NULL)
        return;

    // Increase distance between levels
    space += COUNT;

    // Process right child first
    print2DUtil(root->bt_right, space);

    // Print current node after space
    // count
    printf("\n");
    for (int i = COUNT; i < space; i++)
        printf(" ");
    printf("%d\n", root->ID);

    // Process left child
    print2DUtil(root->bt_left, space);
}

void print2D(s_node *root)
{
   print2DUtil(root, 0);
}
//Print functuions
//-----------------------------------------------------------------------------

// It is needed to calculate the size of array.
int heightOfTree(s_node* root)
{
    if(root == NULL)
        return 0;
    else
        return max(heightOfTree(root->bt_left), heightOfTree(root->bt_right)) + 1;
}
// Traverse the tree in inorder and keep storing
// each node at right place in the array arr.
// Initial value of pos is 0
void populateNodesInArray(s_node* r, int* arr, int pos)
{
    if(r == NULL){ return; }
    
    arr[pos] = r->ID;
    if(r->bt_left != NULL){
        populateNodesInArray(r->bt_left, arr, 2*pos + 1);
    }
    
    if(r->bt_right != NULL){
        populateNodesInArray(r->bt_right, arr, 2*pos + 2);
    }
}
void treeToArray(s_node* root, int* arr, int maxNodes)
{
    // Initialize all the nodes with -1
    for(int i=0; i<maxNodes; i++)
        arr[i] = -1;
    
    // Populating nodes in array
    populateNodesInArray(root, arr, 0);
}
// pos is the position of root in array
void populateTreeFromArray(s_node* r, int* arr, int n, int pos)
{
    if(r == NULL || arr == NULL || n==0){ return; }
    
    // Setting the left subtree of root
    int newPos = 2*pos+1;
    if(newPos < n && arr[newPos] != EMPTY_SPACE)
    {
        //r->bt_left = new s_node(arr[newPos]);
        r->bt_left = TESTcreateNode(arr[newPos]);
        populateTreeFromArray(r->bt_left, arr, n, newPos);
    }
    // Setting the Right subtree of root
    newPos = 2*pos+2;
    if(newPos < n && arr[newPos] != EMPTY_SPACE)
    {
        //r->bt_right = new s_node(arr[newPos]);
        r->bt_right = TESTcreateNode(arr[newPos]);
        populateTreeFromArray(r->bt_right, arr, n, newPos);
    }
}
// We will discard all the negative values as empty spaces
s_node* arrayToTree(int* arr, int n)
{
    if(arr == NULL || arr[0] == EMPTY_SPACE){ return NULL; }
    
    // We will populate the root node here
    // and leave the responsibility of populating rest of tree
    // to the recursive function
    s_node* root = TESTcreateNode(arr[0]);
    populateTreeFromArray(root, arr, n, 0);
    
    return root;
}
// Helper function to print the tree in InOrder
void inOrder(s_node* r)
{
    if(r==NULL){
    	return;}
    inOrder(r->bt_left);
    	printf("%d ",r->ID );
    inOrder(r->bt_right);
    
}
// Helper function to print values of the array
void printArray(int* arr, int n)
{
	printf("\nArray is : ");
    for(int i=0; i<n; i++)
    {
    	printf("%d ",arr[i] );
    }
    printf("\n");
} 
int main(void)
{
	s_node *root = NULL;

	s_node *node0 = createNode(1996, 12, 18, 2, "Ivan", "Novakov", true, true, NULL);
	s_node *node1 = TESTcreateNode(10);
	s_node *node2 = TESTcreateNode(20);
	s_node *node3 = TESTcreateNode(30);
	s_node *node4 = TESTcreateNode(40);
	s_node *node5 = TESTcreateNode(50);
	s_node *node6 = TESTcreateNode(25);
	s_node *node7 = TESTcreateNode(15);
	s_node *node8 = TESTcreateNode(62);
	s_node *node9 = TESTcreateNode(76);
	s_node *node10 = TESTcreateNode(45);
	s_node *node11 = TESTcreateNode(35);
	s_node *node12 = TESTcreateNode(64);
	s_node *node13 = TESTcreateNode(46);
	s_node *node14 = TESTcreateNode(47);
	s_node *node15 = TESTcreateNode(48);
	s_node *node16 = TESTcreateNode(49);
	s_node *node17 = TESTcreateNode(51);
	s_node *node18 = TESTcreateNode(52);
	s_node *node19 = TESTcreateNode(53);
	s_node *node20 = TESTcreateNode(54);
	s_node *node21 = TESTcreateNode(55);
	// Constructing tree given in the above figure
	//root = insert(root, node0);
	root = insert(root, node1);
	root = insert(root, node2);
	root = insert(root, node3);
	root = insert(root, node4);
	root = insert(root, node5);
	root = insert(root, node6);
	root = insert(root, node7);
	root = insert(root, node8);
	root = insert(root, node9);
	root = insert(root, node10);
	root = insert(root, node11);
	root = insert(root, node12);
	root = insert(root, node13);
	root = insert(root, node14);
	root = insert(root, node15);
	root = insert(root, node16);
	root = insert(root, node17);
	root = insert(root, node18);
	root = insert(root, node19);
	root = insert(root, node20);
	root = insert(root, node21);

	print2D(root);
	printf("\n");
	int height = heightOfTree(root);

	// Max number of nodes possible of this height.
	// is 2^height - 1
	int maxNodes = (1<<height) - 1;
	//int *arr = new int[maxNodes];
	int arr[maxNodes];
	printf("Inorder Traversal of tree: ");
	inOrder(root);

	treeToArray(root, arr, maxNodes);
    printArray(arr, maxNodes);
    
    s_node* newTree = arrayToTree(arr, maxNodes);
    
	printf("Inorder Traversal of tree: ");
    inOrder(newTree);
    printf("\n");
    print2D(newTree);
	  return 0;
}
