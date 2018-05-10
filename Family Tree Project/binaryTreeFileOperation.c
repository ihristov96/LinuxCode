#include "Types.h"
#include "binary-tree.c"
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
void populateNodesInArray(s_node* r, s_node* arr, int pos)
{
    if(r == NULL){ return; }
    
    arr[pos] = *((struct nodeStruct*)r);
    if(r->bt_left != NULL){
        populateNodesInArray(r->bt_left, arr, 2*pos + 1);
    }
    
    if(r->bt_right != NULL){
        populateNodesInArray(r->bt_right, arr, 2*pos + 2);
    }
}
void treeToArray(s_node* root, s_node* arr, int maxNodes)
{
    // Initialize all the nodes with -1
    int i = 0;
    s_node s;
    s.ID = -1;
    for( i = 0; i<maxNodes; i++)
        arr[i] = s;
    
    // Populating nodes in array
    populateNodesInArray(root, arr, 0);
}
// pos is the position of root in array
void populateTreeFromArray(s_node* r, s_node* arr, int n, int pos)
{
    if(r == NULL || arr == NULL || n==0){ return; }
    
    // Setting the left subtree of root
    int newPos = 2*pos+1;
    if(newPos < n && arr[newPos].ID != EMPTY_SPACE)
    {
        //r->bt_left = new s_node(arr[newPos]);
        //r->bt_left = TESTcreateNode(arr[newPos].ID,arr[newPos].name[0]);
        r->bt_left = createNodeFromStructure(arr[newPos]);
        populateTreeFromArray(r->bt_left, arr, n, newPos);
    }
    // Setting the Right subtree of root
    newPos = 2*pos+2;
    if(newPos < n && arr[newPos].ID != EMPTY_SPACE)
    {
        //r->bt_right = new s_node(arr[newPos]);
        //r->bt_right = TESTcreateNode(arr[newPos].ID,arr[newPos].name[0]);
        r->bt_right = createNodeFromStructure(arr[newPos]);
        populateTreeFromArray(r->bt_right, arr, n, newPos);
    }
}
// We will discard all the negative values as empty spaces
s_node* arrayToTree(s_node* arr, int n)
{
    if(arr == NULL || arr[0].ID == EMPTY_SPACE){ return NULL; }
    
    // We will populate the root node here
    // and leave the responsibility of populating rest of tree
    // to the recursive function
    //s_node* root = TESTcreateNode(arr[0].ID,arr[0].name[0]);
    s_node* root = createNodeFromStructure(arr[0]);
    populateTreeFromArray(root, arr, n, 0);
    
    return root;
}
// Helper function to print the tree in InOrder
void inOrder(s_node* r)
{
    if(r == NULL)
    {
    	return;
    }
    inOrder(r->bt_left);
    	printf("\n Name: %s #:%u pointer %d\n",r->name,r->ID,r);
        if(r->ft_parent != NULL)
        {
            printf("fatherName: %s\n",r->ft_parent->name );
        }
    inOrder(r->bt_right);
    
}
// Helper function to print values of the array
void printArray(s_node* arr, int n)
{
	printf("\nArray is : ");
    int i = 0;
    for(i=0; i<n; i++)
    {
    	printf("%u ",arr[i].ID );
    }
    printf("\n");
} 
