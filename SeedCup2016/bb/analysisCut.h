#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <list>
enum Attribute
{
	EMPTY,
	INT,
	IF,
	ELSE_IF,
	ELSE,
	FOR_INT,
	FOR_NORMAL,
	DO,
	WHILE,
	BREAK,
	PRINTF,
	NORMAL,
};

enum BracketStatu {
	NO_BRACKET,
	LEFT_BRACKET,
	RIGHT_BRACKET,
	BOTH_BRACKET,
};

struct StatementNode
{
	//�к�
	int lineNo;
	//���ִ�����
	std::vector<std::string> left;
	//�ж����
	std::string judgement;
	//�Ҳ�ִ�����
	std::vector<std::string> right;
	//���leixing
	Attribute attr;
	//���������תָ��
	std::list<StatementNode>::iterator Goto;
	//if����ϴε��õĽ��
	bool lastAnswer;
};;
/*************************************
���봦������ַ�������Ҫ�޸ĵ�node
��node�е�������Ϊ���������Ľ��
����ֵΪ�ַ����е����ŵ���Ϣ
*************************************/
/*�����ַ�������*/
BracketStatu analysis_one(std::string &former, StatementNode &node);