#pragma once
#include <array>
#include <iostream>
#include <ctime>

//注意，调整宏值，需要全部重新编译
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
	//检查指定位置的雷的数量，并返回
	char CheckMine(int cx, int cy);
	//递归翻开所有雷数量为0的位置
	void RecuCheck(int cx, int cy);
	//非雷数量，归零时游戏胜利
	unsigned int NotMineNum = SELF_SIZE * SELF_SIZE - SELF_MINE;
	unsigned int MarkNum = 0;

};