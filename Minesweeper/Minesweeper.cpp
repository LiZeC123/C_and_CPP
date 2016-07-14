#include "Minesweeper.h"


Screen::Screen()
{
	srand((unsigned int)time(0));
	int i = 0;
	while (i != SELF_MINE) {
		int ix, iy;
		ix = rand() % SELF_SIZE;
		iy = rand() % SELF_SIZE;
		if (Data[iy][ix].IsMine) {
			continue;
		}
		else {
			Data[iy][ix].IsMine = true;
			++i;
		}
	}
}

Screen & Screen::GoLeft()
{
	if (x > 0) {
		--x;
	}
	Show();
	return *this;
}

Screen & Screen::GoRight()
{
	//最大只能取15，因此减一
	if (x < Data.size() - 1) {
		++x;
	}
	Show();
	return *this;
}

Screen & Screen::GoUp()
{
	if (y > 0) {
		--y;
	}
	Show();
	return *this;
}

Screen & Screen::GoDown()
{	
	//同样的理由，所以减一
	if (y < Data[0].size() - 1) {
		++y;
	}
	Show();
	return *this;
}

Screen & Screen::Show()
{	
	//先刷新屏幕
	system("cls");

	//打印第一行的光标
	std::cout << "  ";
	for (int i = 0; i != x; ++i) {
		std::cout << "  ";
	}
	std::cout << 'V' << std::endl;

	//打印内容
	int count = 0;
	for (auto &r : Data) {
		if (count == y) {
			std::cout << "->";
		}
		else {
			std::cout << "  ";
		}
		for (auto &i : r) {
			std::cout << i.Cover()<< ' ';
		}
		std::cout << std::endl;
		++count;
	}

	//打印当前参数
	std::cout << "Mark:   " << MarkNum << std::endl;
	std::cout << "Remain: " << NotMineNum << std::endl;
	return *this;
}

Screen & Screen::DeadShow()
{	
	//如果游戏没有结束，则直接返回
	if (IsLive) {
		return *this;
	}
	//先刷新屏幕
	system("cls");

	//打印第一行的光标
	std::cout << "  ";
	for (int i = 0; i != x; ++i) {
		std::cout << "  ";
	}
	std::cout << 'V' << std::endl;

	//打印内容
	int count = 0;
	for (auto &r : Data) {
		if (count == y) {
			std::cout << "->";
		}
		else {
			std::cout << "  ";
		}
		for (auto &i : r) {
			if (i.IsMine)
				std::cout << 'M' << ' ';
			else
				std::cout << i.Cover() << ' ';
		}
		std::cout << std::endl;
		++count;
	}
	return *this;
}

Screen & Screen::WinShow()
{
	//如果游戏没有胜利，则直接返回
	if (!IsWin()) {
		return *this;
	}
	//先刷新屏幕
	system("cls");

	//打印第一行的光标
	std::cout << "  ";
	for (int i = 0; i != x; ++i) {
		std::cout << "  ";
	}
	std::cout << 'V' << std::endl;

	//打印内容
	int count = 0;
	for (auto &r : Data) {
		if (count == y) {
			std::cout << "->";
		}
		else {
			std::cout << "  ";
		}
		for (auto &i : r) {
			if (i.IsMine)
				std::cout << 'B' << ' ';
			else
				std::cout << i.Cover() << ' ';
		}
		std::cout << std::endl;
		++count;
	}
	return *this;
}

Screen & Screen::Check()
{
	//注意由于坐标系的定义和二维数组的定义
	//顺序是反的
	if (!Data[y][x].IsCheck && !Data[y][x].IsMark) {
		Data[y][x].IsCheck = true;
		if (Data[y][x].IsMine) {
			Data[y][x].Num = 'M';
			IsLive = false;
		}
		else {
			--NotMineNum;
			Data[y][x].Num = CheckMine(x, y);
			if (Data[y][x].Num == ' ') {
				RecuCheck(x, y);
			}
			Show();
		}
	}
	return *this;
}

Screen & Screen::Mark()
{
	if (!Data[y][x].IsCheck) {
		Data[y][x].IsMark = !Data[y][x].IsMark;
		if (Data[y][x].IsMark)
			++MarkNum;
		else
			--MarkNum;
	}
	Show();
	return *this;
}

bool Screen::IsWin()
{
	return NotMineNum == 0;
}

char Screen::CheckMine(int cx, int cy)
{
	int count = 0;
	for (int iy = cy - 1; iy <= cy + 1; ++iy) {
		for (int ix = cx - 1; ix <= cx + 1; ++ix) {
			if (iy < 0 || ix < 0)
				continue;
			if (iy >= Data.size() || ix >= Data[0].size())
				continue;
			if (ix == cx && iy == cy)
				continue;
			if (Data[iy][ix].IsMine)
				++count;
				}
			}
	if (count == 0) {
		return ' ';
	}
	else {
		return count + '0';
	}
	
}

void Screen::RecuCheck(int cx, int cy)
{
	for (int iy = cy - 1; iy <= cy + 1; ++iy) {
		for (int ix = cx - 1; ix <= cx + 1; ++ix) {
			if (iy < 0 || ix < 0)
				continue;
			if (iy >= Data.size() || ix >= Data[0].size())
				continue;
			if (ix == cx && iy == cy)
				continue;
			if ( !Data[iy][ix].IsCheck ) {
				Data[iy][ix].IsCheck = true;
				--NotMineNum;
				Data[iy][ix].Num = CheckMine(ix, iy);
				if (Data[iy][ix].Num == ' ') 
					RecuCheck(ix, iy);
			}

		}
	}
}

char Mine::Cover()
{
	if (IsCheck) {
		return  Num;
	}
	else if (IsMark) {
		return 'B';
	}
	else {
		return 'X';
	}
}
