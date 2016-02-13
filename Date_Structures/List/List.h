#ifndef LIST_H
#define LIST_H
#include<stdbool.h>

#define TSIZE 45
struct file{
	char title[TSIZE];
	int rating;
};

typedef struct file Item;

typedef struct node{
	Item item;
	struct node * next;
}Node;

typedef Node *  List;

//condition			:初始化一个链表 
//precondition		:plist指向一个链表 
//postcondition		:该链表被初始化为一个空链表 
void InitializeList(List * plist);

//condition			:确定链表是否为空链表 
//precondition		:plist指向一个已经初始化的链表 
//postcondition		:如果链表为空，则返回ture，否则返回false 
bool ListIsEmpty(const List * plist);

//condition			:确定链表是否已满 
//precondition		:plist指向一个已经初始化的链表 
//postcondition		:如果链表已满，则返回true，否则返回false 
bool ListIsFull(const List * plist);

//condition			:确定链表中项目的个数 
//precondition		:plist指向一个已经初始化的链表 
//postcondition		:返回链表中项目的个数 
unsigned int ListItemCount(const List * plist);

//condition			:向链表的尾部添加一个 项目 
//precondition		:item是要添加的项目，plist指向一个已经初始化的链表 
//postcondition		:如果可能，向链表尾部添加一个项目，并且返回ture，否则返回false 
bool AddItem(Item item,List *plist);

//condition			:把一个函数作用于链表的每一个项目 
//precondition		:plist指向一个已经初始化的链表 ，pfun指向一个接受一个Item参数的无返回值的函数 
//postcondition		:pfun指向的函数作用到链表中的每个项目一次 
void Traverse(const List * plist,void(*pfun)(Item item));

//condition			:释放已分配的内存（如果有） 
//precondition		:plist指向一个已经初始化的链表 
//postcondition		:该链表分配的内存被释放，同时链表置为空链表 
void EmptyTheList(List * plist);

#endif
