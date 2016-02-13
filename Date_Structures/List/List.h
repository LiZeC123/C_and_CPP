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

//condition			:��ʼ��һ������ 
//precondition		:plistָ��һ������ 
//postcondition		:��������ʼ��Ϊһ�������� 
void InitializeList(List * plist);

//condition			:ȷ�������Ƿ�Ϊ������ 
//precondition		:plistָ��һ���Ѿ���ʼ�������� 
//postcondition		:�������Ϊ�գ��򷵻�ture�����򷵻�false 
bool ListIsEmpty(const List * plist);

//condition			:ȷ�������Ƿ����� 
//precondition		:plistָ��һ���Ѿ���ʼ�������� 
//postcondition		:��������������򷵻�true�����򷵻�false 
bool ListIsFull(const List * plist);

//condition			:ȷ����������Ŀ�ĸ��� 
//precondition		:plistָ��һ���Ѿ���ʼ�������� 
//postcondition		:������������Ŀ�ĸ��� 
unsigned int ListItemCount(const List * plist);

//condition			:�������β�����һ�� ��Ŀ 
//precondition		:item��Ҫ��ӵ���Ŀ��plistָ��һ���Ѿ���ʼ�������� 
//postcondition		:������ܣ�������β�����һ����Ŀ�����ҷ���ture�����򷵻�false 
bool AddItem(Item item,List *plist);

//condition			:��һ�����������������ÿһ����Ŀ 
//precondition		:plistָ��һ���Ѿ���ʼ�������� ��pfunָ��һ������һ��Item�������޷���ֵ�ĺ��� 
//postcondition		:pfunָ��ĺ������õ������е�ÿ����Ŀһ�� 
void Traverse(const List * plist,void(*pfun)(Item item));

//condition			:�ͷ��ѷ�����ڴ棨����У� 
//precondition		:plistָ��һ���Ѿ���ʼ�������� 
//postcondition		:�����������ڴ汻�ͷţ�ͬʱ������Ϊ������ 
void EmptyTheList(List * plist);

#endif
