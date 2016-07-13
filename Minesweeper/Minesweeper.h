#pragma once
#include <array>
#include <iostream>
#include <ctime>

//ע�⣬������ֵ����Ҫȫ�����±���
#define SMALL_SIZE		9
#define MIDDLE_SIZE		16
#define SELF_SIZE       SMALL_SIZE

#define SMALL_MINE      10
#define MIDDLE_MINE     40
#define SELF_MINE		SMALL_MINE


class Mine
{
public:
	char Cover();
	bool IsMine = false;
	bool IsCheck = false;
	bool IsMark = false;
	char  Num = 0;
};

class Screen
{
public:
	Screen();
public:
	Screen & GoLeft();
	Screen & GoRight();
	Screen & GoUp();
	Screen & GoDown();

	Screen & Show();
	Screen & DeadShow();
	Screen & WinShow();

	Screen & Check();
	Screen & Mark();

	bool IsLive = true;
	bool IsWin();

private:
	std::array<std::array<Mine, SELF_SIZE>, SELF_SIZE> Data;
	int x = 0;
	int y = 0;
	//���ָ��λ�õ��׵�������������
	char CheckMine(int cx, int cy);
	//�ݹ鷭������������Ϊ0��λ��
	void RecuCheck(int cx, int cy);
	//��������������ʱ��Ϸʤ��
	unsigned int NotMineNum = SELF_SIZE * SELF_SIZE - SELF_MINE;
	unsigned int MarkNum = 0;

};