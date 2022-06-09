#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include "../Space.h"
#include "../GlobelValue.h"


enum runState {
	execution,
	non_execution
};

class OperationExpression {
public:

	//��ֵ��䴦������ֵexecution�����ִ��
	runState assignOperDeal(std::vector<std::string> &Oper);

	//������䴦������ֵexecution�����ִ��,non_execution����䲻ִ��
	runState stateOperDeal(std::vector<std::string> &Oper);

	//������ʽ
	int caculate(std::string operLink);

	//�Ƚϱ��ʽ
	bool compareExp(std::string exp);

private:

	//���ʽ���ڵȺ�
	void exitEqual(std::string evalOper, int evalNum);

	//���ʽ�����ڵȺ�,����ֵΪ999999
	void exitNoEqual(std::string evalOper);

	//����+-*/����ֽ����ַ��������㸳ֵ���м䲽�裩
	void analyzeString(std::string operLink, std::vector<std::string> &operSplit);

	//��׺ʽ���׺ʽ�����㸳ֵ���м䲽�裩
	void changeExp(std::vector<std::string> minExp, std::vector<std::string> &lastExp);

	//ƥ����������ǲ�����������Ӧ�������Ƿ���-1��change�����м䲽�裩
	int matchOptr(std::string str);

	//�жϲ����������ȼ���change�������м䲽�裩
	char preceed(std::string stackOptr, std::string minOptr);

	//�����׺���ʽ��ֵ
	int caculateLastOper(std::vector<std::string> &lastOper);

	//�������
	int oper(int a, int b, std::string optr);
};