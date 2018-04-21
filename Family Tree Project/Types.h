typedef int bool;

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

typedef enum  
{
	showFamilyTree_c =1,
	addChildren_c = 2,
	killFamilyMember_c = 3
}commandRequests;
