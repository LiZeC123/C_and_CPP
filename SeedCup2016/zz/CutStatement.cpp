#include "CutStatement.h"
#include <iostream>
#include<deque>
#include<stack>

std::vector<std::string> CutStatement::cutStatement(std::string oneline)
{
	//���������±�	
	int lineEdx = 0;
	//�������±�
	int bufEdx = 0;

	rtn.clear();

	while(lineEdx < oneline.size()) {
		//������ͨע�ͣ�ֱ��ȫ������
		if (isNComment(oneline.c_str(), lineEdx)) {
			break;
		}
		//���ֺ����Ǻŵ�ע�ͣ������ò���
		else if (isSComment(oneline.c_str(), lineEdx)) {
			
			do {
				++lineEdx;
			}
			while (!isSComment(oneline.c_str(), lineEdx));
			lineEdx += 2;

		}
		//���������ţ�ֱ�Ӷ�ȡֱ��ƥ���������֮�����������
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
		//���ַֺţ��ָǰ���
		else if (oneline[lineEdx] == ';') {
			buf[bufEdx] = ';';
			//���ϱ�־���γ��ַ���
			buf[bufEdx+1] = '\0';
			//��ý�������û�����
			cleanBlack(bufEdx + 1);
			bufEdx = 0;
			++lineEdx;
		}
		//��ͨ�����ֱ�Ӷ���
		else {
			buf[bufEdx++] = oneline[lineEdx++];
		}
	}

	//������������ʣ����ַ�
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
	//ȥ������Ŀո�
	while (isblank(buf[start])) {
		++start;
	}

	//�ǿղŴ���
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
