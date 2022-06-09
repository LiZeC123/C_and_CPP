#pragma once
#include <string>
#include <vector>

//����������һ�а��շֺ��и�����ɸ���Ч������
class CutStatement
{
public:
	//���캯������ʼ��������
	CutStatement() {
		clearBuf(BufSize);
	}

	//����һ���ַ��������ذ��շֺ��и����Ч����
	std::vector<std::string> cutStatement(std::string oneline);
	

private:
	//��ջ���
	void clearBuf(int size);

	//ȥ������Ŀո�,���������,ͬʱ��ջ�����
	void cleanBlack(int bufSize);

	//�жϵ�ǰλ���Ƿ���ͨ��ʽ��ע��
	bool isNComment(const char * line, int start);

	//�жϵ�ǰλ���Ƿ�Ϊ�����Ǻŵ�ע��
	bool isSComment(const char * line, int start);

	//��ŷ���ֵ��Vector
	std::vector<std::string> rtn;

	//��������󳤶ȣ���Ӧÿ������ַ���
	static const int BufSize = 256;

	//������
	char buf[BufSize];
};

