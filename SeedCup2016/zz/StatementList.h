#pragma once
#include <list>
#include <string>
#include <fstream>
#include <vector>
#include <stack>
#include "../rr/OperationExpression.h"
#include "../bb/analysisCut.h"


//用于读取文本和执行其中代码的类
class StatementList
{
public:
	using iterator = std::list<StatementNode>::iterator;
	//从一个制定的文件流中读取代码，并将其结构化
	StatementList(std::ifstream & inf);
	//执行已经结构化的代码
	void Run();

	//输出结构化的代码的信息，用于调试
	void Print();
private:
	//存放结构化代码的链表
	std::list<StatementNode> data;

	//用于进行括号匹配的堆栈
	std::stack<iterator> BracketStack;

	//存放用于输出的行号
	std::vector<int> printList;

	//用于对各种类型的表达式进行计算的类的实例
	OperationExpression Oe;

	//一下函数用于执行各种类型的语句，并返回下执行语句的位置
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

	//返回迭代器指示的位置之前的其他分支语句的执行情况
	//如果有执行的语句，返回true，否则返回false
	bool getBackBool(iterator it);

	//输出最后答案
	void printAnswer();

};
