#include <stdio.h>
#include <stdlib.h>
#include "Types.h"
int main()
{
	#if 0
	typedef struct treeNode
{
	int ID;
	struct treeNode* bt_left;
	struct treeNode* bt_right;
    struct treeNode* ft_parent;

	int bt_colour; //not used

	//int birth_year;
	int birth_month;
	int birth_day;

	char name[10];
	char partnerName[10];

	bool isAlive;
}node;
#endif

	FILE* fp;
	if((fp=fopen("BinaryTree.txt","w"))==NULL)
		 printf("the file cant open");

	int number = 1;
	node n;
	n.ID = 0;
	n.bt_left = NULL;
	n.bt_right = NULL;
	n.ft_parent = NULL;
	n.bt_colour = 0;
	n.birth_month = 10;
	n.birth_day = 4;
	n.name[0] = 'I';
	n.name[1] = '\0';
	n.partnerName[0] = 'H';
	n.partnerName[1] = '\0';
	n .isAlive = 1;
	node* ptr = &n;
	if(fwrite(&number,sizeof(int),1,fp)!=1)
 		printf("writening error");

	if(fwrite(ptr,sizeof(node),1,fp)!=1)
 		printf("writening error");

 	fclose(fp);
 	if((fp=fopen("BinaryTree.txt","r"))==NULL)
		 printf("the file cant open");
	int size = 0;
	node readNode;

	if(fread(&size,sizeof(int),1,fp)!=1)
	{
		printf("reading error");
	}
	if(fread(&readNode,sizeof(node),1,fp)!=1)
	{
		printf("reading error");
	}
	printf("%c\n",readNode.name[0] );


}