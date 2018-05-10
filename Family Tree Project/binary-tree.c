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
s_node* TESTcreateNode(int ID,char ch)
{
    s_node* node = (s_node*)malloc(sizeof(s_node));

    node->bt_left   = NULL;
    node->bt_right  = NULL;

    node->height = 1;  // new node is initially added at leaf

    node->ID = ID;
    node->name[0] = ch;
    node->name[1] = '\0';
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
    int i = 0;
    for (i = COUNT; i < space; i++)
        printf(" ");
    printf("%c\n", root->name[0]);

    // Process left child
    print2DUtil(root->bt_left, space);
}

void print2D(s_node *root)
{
   print2DUtil(root, 0);
}
//Print functuions
//-----------------------------------------------------------------------------
