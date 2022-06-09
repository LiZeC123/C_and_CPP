#pragma once
#include <string>
#include <vector>

//将输入语句的一行按照分号切割成若干个有效语句的类
class CutStatement
{
public:
	//构造函数，初始化缓冲区
	CutStatement() {
		clearBuf(BufSize);
	}

	//读入一个字符串，返回按照分号切割的有效代码
	std::vector<std::string> cutStatement(std::string oneline);
	

private:
	//清空缓存
	void clearBuf(int size);

	//去除多余的空格,并产生结果,同时清空缓存区
	void cleanBlack(int bufSize);

	//判断当前位置是否普通形式的注释
	bool isNComment(const char * line, int start);

	//判断当前位置是否为包含星号的注释
	bool isSComment(const char * line, int start);

	//存放返回值的Vector
	std::vector<std::string> rtn;

	//缓冲区最大长度，对应每行最大字符数
	static const int BufSize = 256;

	//缓冲区
	char buf[BufSize];
};

