#include "CutStatement.h"
#include <iostream>
#include<deque>
#include<stack>

std::vector<std::string> CutStatement::cutStatement(std::string oneline)
{
	//输入数据下标	
	int lineEdx = 0;
	//缓冲区下标
	int bufEdx = 0;

	rtn.clear();

	while(lineEdx < oneline.size()) {
		//发现普通注释，直接全部跳过
		if (isNComment(oneline.c_str(), lineEdx)) {
			break;
		}
		//发现含有星号的注释，跳过该部分
		else if (isSComment(oneline.c_str(), lineEdx)) {
			
			do {
				++lineEdx;
			}
			while (!isSComment(oneline.c_str(), lineEdx));
			lineEdx += 2;

		}
		//发现左括号，直接读取直到匹配的右括号之间的所有内容
		else if (oneline[lineEdx] == '(') {
			std::stack<char, std::deque<char>> stk;
			stk.push('(');
			buf[bufEdx++] = oneline[lineEdx++];

			while (!stk.empty()) {
				if (oneline[lineEdx] == '(') {
					stk.push('(');
				}
				if (oneline[lineEdx] == ')') {
					stk.pop();
				}
				buf[bufEdx++] = oneline[lineEdx++];
			}
		}
		//发现分号，分割当前语句
		else if (oneline[lineEdx] == ';') {
			buf[bufEdx] = ';';
			//加上标志，形成字符串
			buf[bufEdx+1] = '\0';
			//获得结果并重置缓冲区
			cleanBlack(bufEdx + 1);
			bufEdx = 0;
			++lineEdx;
		}
		//普通情况，直接读入
		else {
			buf[bufEdx++] = oneline[lineEdx++];
		}
	}

	//最后输出缓冲区剩余的字符
	cleanBlack(bufEdx + 1);

	return rtn;
}

inline void CutStatement::clearBuf(int size)
{
	for (int i = 0; i < size; ++i) {
		buf[i] = 0;
	}
}

void CutStatement::cleanBlack(int bufSize)
{
	int start = 0;
	//去除多余的空格
	while (isblank(buf[start])) {
		++start;
	}

	//非空才存入
	if (buf[start] != '\0') {
		rtn.push_back(std::string(buf + start));
	}
	
	clearBuf(bufSize);
}

inline bool CutStatement::isNComment(const char * line, int start)
{
	if (line[start] == '/'&& line[start + 1] == '/')
		return true;
	else
		return false;
	//if (line[start] == '/') {
	//	if (line[start + 1] == '/' || line[start + 1] == '*') {
	//		return true;
	//	}
	//}

	//return false;
}

bool CutStatement::isSComment(const char * line, int start)
{
	if (line[start] == '/'&& line[start + 1] == '*')
		return true;
	else if (line[start] == '*' && line[start + 1] == '/')
		return true;
	else
		return false;
}
