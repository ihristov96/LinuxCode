#include <stdio.h>
#include "binaryTreeFileOperation.c"

int main(void)
{
	s_node *root = NULL;
	//						  year,month,day,order,name,surname,isMale,isAlive,parent
	s_node *node0 = createNode(1950, 12, 18, 1, "Ivan", "Ivanov", true, true, NULL);

	s_node *node1 = createNode(1970, 5, 10, 1, "Desislava", "Dobreva", false, true, node0);

	s_node *node2 = createNode(1972, 10, 04, 2, "Ivailo", "Hristov", true, true, node0);

	s_node *node3 = createNode(1973, 12, 18, 2, "Simeon", "Petkov", true, true, node1);

	s_node *node4 = createNode(1974, 12, 18, 2, "Gosho", "Otpochivka", true, true, node2);

	s_node *node5 = createNode(1975, 12, 18, 2, "Pesho", "Georgiev", true, true, node2);
	printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ %u\n",node5->ft_parent->ID );
	/*
	s_node *node1 = TESTcreateNode(10, 'a');
	s_node *node2 = TESTcreateNode(20, 'b');
	s_node *node3 = TESTcreateNode(30, 'c');
	s_node *node4 = TESTcreateNode(40, 'd');
	s_node *node5 = TESTcreateNode(50, 'e');
	s_node *node6 = TESTcreateNode(25, 'f');
	s_node *node7 = TESTcreateNode(15, 'g');
	s_node *node8 = TESTcreateNode(62, 'h');
	s_node *node9 = TESTcreateNode(76, 'i');
	s_node *node10 = TESTcreateNode(45, 'j');
	s_node *node11 = TESTcreateNode(35, 'k');
	s_node *node12 = TESTcreateNode(64, 'l');
	s_node *node13 = TESTcreateNode(46, 'm');
	s_node *node14 = TESTcreateNode(47, 'n');
	s_node *node15 = TESTcreateNode(48, 'o');
	s_node *node16 = TESTcreateNode(49, 'p');
	s_node *node17 = TESTcreateNode(51, 'q');
	s_node *node18 = TESTcreateNode(52, 'r');
	s_node *node19 = TESTcreateNode(53, 's');
	s_node *node20 = TESTcreateNode(54, 't');
	s_node *node21 = TESTcreateNode(55, 'u');
	*/
	// Constructing tree given in the above figure
	root = insert(root, node0);
	root = insert(root, node1);
	root = insert(root, node2);
	root = insert(root, node3);
	root = insert(root, node4);
	 root = insert(root, node5);
	// root = insert(root, node6);
	// root = insert(root, node7);
	// root = insert(root, node8);
	// root = insert(root, node9);
	// root = insert(root, node10);
	// root = insert(root, node11);
	// root = insert(root, node12);
	// root = insert(root, node13);
	// root = insert(root, node14);
	// root = insert(root, node15);
	// root = insert(root, node16);
	// root = insert(root, node17);
	// root = insert(root, node18);
	// root = insert(root, node19);
	// root = insert(root, node20);
	// root = insert(root, node21);

	print2D(root);
	printf("\n");
	int height = heightOfTree(root);

	// Max number of nodes possible of this height.
	// is 2^height - 1
	int maxNodes = (1<<height) - 1;
	//int *arr = new int[maxNodes];
	s_node arr[maxNodes];
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
