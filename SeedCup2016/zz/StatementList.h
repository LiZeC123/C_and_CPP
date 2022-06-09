#pragma once
#include <list>
#include <string>
#include <fstream>
#include <vector>
#include <stack>
#include "../rr/OperationExpression.h"
#include "../bb/analysisCut.h"


//���ڶ�ȡ�ı���ִ�����д������
class StatementList
{
public:
	using iterator = std::list<StatementNode>::iterator;
	//��һ���ƶ����ļ����ж�ȡ���룬������ṹ��
	StatementList(std::ifstream & inf);
	//ִ���Ѿ��ṹ���Ĵ���
	void Run();

	//����ṹ���Ĵ������Ϣ�����ڵ���
	void Print();
private:
	//��Žṹ�����������
	std::list<StatementNode> data;

	//���ڽ�������ƥ��Ķ�ջ
	std::stack<iterator> BracketStack;

	//�������������к�
	std::vector<int> printList;

	//���ڶԸ������͵ı��ʽ���м�������ʵ��
	OperationExpression Oe;

	//һ�º�������ִ�и������͵���䣬��������ִ������λ��
	iterator doEmpty(iterator it);
	iterator doInt(iterator it);
	iterator doNormal(iterator it);
	iterator doIf(iterator it);
	iterator doElseIf(iterator it);
	iterator doElse(iterator it);
	iterator doForInt(iterator it);
	iterator doForNormal(iterator it);
	iterator doDo(iterator it);
	iterator doWhile(iterator it);
	iterator doBreak(iterator it);
	iterator doPrintf(iterator it);

	//���ص�����ָʾ��λ��֮ǰ��������֧����ִ�����
	//�����ִ�е���䣬����true�����򷵻�false
	bool getBackBool(iterator it);

	//�������
	void printAnswer();

};
