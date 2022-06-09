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
	//行号
	int lineNo;
	//左侧执行语句
	std::vector<std::string> left;
	//判读语句
	std::string judgement;
	//右侧执行语句
	std::vector<std::string> right;
	//语句leixing
	Attribute attr;
	//特殊语句跳转指针
	std::list<StatementNode>::iterator Goto;
	//if语句上次调用的结果
	bool lastAnswer;
};;
/*************************************
传入处理过的字符串和需要修改的node
将node中的数据作为函数分析的结果
返回值为字符串中的括号的信息
*************************************/
/*分析字符串方法*/
BracketStatu analysis_one(std::string &former, StatementNode &node);