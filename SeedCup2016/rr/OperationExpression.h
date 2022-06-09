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

	//赋值语句处理。返回值execution：语句执行
	runState assignOperDeal(std::vector<std::string> &Oper);

	//声明语句处理。返回值execution：语句执行,non_execution：语句不执行
	runState stateOperDeal(std::vector<std::string> &Oper);

	//计算表达式
	int caculate(std::string operLink);

	//比较表达式
	bool compareExp(std::string exp);

private:

	//表达式存在等号
	void exitEqual(std::string evalOper, int evalNum);

	//表达式不存在等号,赋初值为999999
	void exitNoEqual(std::string evalOper);

	//按“+-*/”拆分解析字符串（计算赋值的中间步骤）
	void analyzeString(std::string operLink, std::vector<std::string> &operSplit);

	//中缀式变后缀式（计算赋值的中间步骤）
	void changeExp(std::vector<std::string> minExp, std::vector<std::string> &lastExp);

	//匹配操作符。是操作符返回相应数，不是返回-1（change函数中间步骤）
	int matchOptr(std::string str);

	//判断操作符的优先级（change函数的中间步骤）
	char preceed(std::string stackOptr, std::string minOptr);

	//计算后缀表达式的值
	int caculateLastOper(std::vector<std::string> &lastOper);

	//具体计算
	int oper(int a, int b, std::string optr);
};