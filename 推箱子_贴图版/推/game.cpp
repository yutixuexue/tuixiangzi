#include "game.h"

void copy(int arr1[N][N], int arr2[N][N]) {
	for (int j = 0; j < N; j++)
		for (int z = 0; z < N; z++)
			arr2[j][z] = arr1[j][z];
}

game::game()
{
	//初始化小人位置和终点位置
	for (int i = 0; i < L; i++) {
		for (int j = 0, t = 0; j < N; j++) {
			for (int z = 0; z < N; z++) {
				if (maps[i][j][z] == 5) {
					me[i] = point(j, z);
					maps[i][j][z] = 1;
				}
				else if (maps[i][j][z] == 3 || maps[i][j][z] == 4 || maps[i][j][z] == 6) {
					win[i][t++] = point(j,z);
				}
			}
		}
	}


	//下载当前关卡地图
	init();


	//设置字体样式
	settextstyle(20, 0, _T("Consolas"));

	//下载地图图片
	loadimage(&Wall, _T("./source/wall.png"), 40, 40);
	loadimage(&Box, _T("./source/box.png"), 40, 40);
	loadimage(&End, _T("./source/end.png"), 40, 40);
	loadimage(&Me, _T("./source/me.png"), 40, 40);
	loadimage(&Box_yellow, _T("./source/box_yellow.png"), 40, 40);
}

void game::init() {
	copy(maps[level], tempMap);
	tempMe = me[level];
	stack<point>().swap(s);
}

void game::print() {
	//刷新地图
	cleardevice();
	int temp = tempMap[tempMe.x][tempMe.y];

	tempMap[tempMe.x][tempMe.y] = temp == 1 ? 5 : 6;
	outtextxy(0,0,L"*************游戏说明**************");
	outtextxy(0,20,L"******请使用w、a、s、d进行移动******");
	outtextxy(0,40,L"****e:结束游戏，r:重新开始*****");
	outtextxy(0, 60, L"****t:选择关卡，b:回退到上一步****");
	TCHAR s[50];
	_stprintf_s(s, _T("****现在是第%d关****"), level + 1);		// 高版本 VC 推荐使用 _stprintf_s 函数
	outtextxy(0, 80, s);
	int position = 100;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (tempMap[i][j] == 2)
				putimage(j * 40, i * 40 + position, &Box);
			else if (tempMap[i][j] == 4)
				putimage(j * 40, i * 40 + position, &Box_yellow);
			else if (tempMap[i][j] == 8)
				putimage(j * 40, i * 40 + position, &Wall);
			else if (tempMap[i][j] == 3)
				putimage(j * 40, i * 40 + position, &End);
			else if (tempMap[i][j] == 5 || tempMap[i][j] == 6)
				putimage(j * 40, i * 40 + position, &Me);
		}
		cout << endl;
	}
	tempMap[tempMe.x][tempMe.y] = temp;
}

void game::enter(char &start) {
	char temp = start;
	do {
		start = temp;
		temp = _getch();
		if (temp == 8) temp = ' ';
		outtextxy(0, Ask+20, temp);
	} while (temp != 13 && temp != 10);
}

bool game::judge() {
	bool flag = true;
	for (int i = 0; i < 6 && flag; i++) {
		if (win[level][i].x == -1 || win[level][i].y == -1)	break;
		if (tempMap[win[level][i].x][win[level][i].y] != 4)	flag = false;
	}
	if (flag) {
		print();
		outtextxy(0,Ask-20,L"游戏结束！！！\n");
		outtextxy(0,Ask,L"是否进入下一关(y/n)\n");
		char op = _getch();
		outtextxy(0, Ask+20, op);
		for (;;) {
			enter(op);
			if (op == 'y') {
				level = ++level%L;
				init();
				return false;
			}
			else if (op == 'n') return true;
		}
	}
	return flag;
}

bool game::end() {
	outtextxy(0,Ask,L"请确实是否(y/n)结束游戏");
	char end = _getch();
	outtextxy(0, Ask+20, end);
	for (;;) {
		enter(end);
		if (end == 'y')	return true;
		else if (end == 'n') return false;
	}
}

bool game::restart() {
	outtextxy(0,Ask,L"请确实是否(y/n)重新开始");
	char restart = _getch();
	outtextxy(0, Ask+20, restart);
	for (;;) {
		enter(restart);
		if (restart == 'y') {
			init();
			return false;
		}
		else if (restart == 'n') return false;
	}
}

bool game::turn() {
	outtextxy(0, Ask, L"请选择关卡(b:退出选关)：");
	for (int i = 1; i <= L; i++) {
		outtextxy(i * 40 + 200, Ask,(L'0'+i));
	}
	char g = _getch();
	outtextxy(0, Ask+20, g);
	for (;;) {
		enter(g);
		if (g == 'b')	return false;
		else if (g > '0' && g <= '0' + L) {
			level = g - '1';
			init();
			return false;
		}
	}
}

bool game::back() {
	if (!s.size())	return false;
	int i = s.top().x, flag = s.top().y;
	s.pop();
	if (flag) {
		point t = tempMe + w[i];
		tempMap[t.x][t.y] = tempMap[t.x][t.y] == 2 ? 1 : 3;
		tempMap[tempMe.x][tempMe.y] = tempMap[tempMe.x][tempMe.y] == 1 ? 2 : 4;
	}
	tempMe -= w[i];
	return false;
}

int game::option(char op) {
	int i = 10;
	switch (op)
	{
	case 'w':
	case 72:
		i = 0;
		break;
	case 'd':
	case 77:
		i = 1;
		break;
	case 's':
	case 80:
		i = 2;
		break;
	case 'a':
	case 75:
		i = 3;
		break;
	case 'e':
		i = 4;
		break;
	case 'r':
		i = 5;
		break;
	case 't':
		i = 6;
		break;
	case 'b':
		i = 7;
		break;
	}

	return i;
}

bool game::run(char op) {
	int i = option(op);

	//功能选项 
	if (i > 3) {
		if (i == 4) {
			return end();
		}
		else if (i == 5) {
			return restart();
		}
		else if (i == 6) {
			return turn();
		}
		else if (i == 7) {
			return back();
		}
		else if (i == 10) {
			return false;
		}
	}


	//移动操作 
	tempMe += w[i];
	//记录移动位置
	int xx = tempMe.x + w[i].x;
	int yy = tempMe.y + w[i].y;
	int isPush = 0; //记录是否推动箱子
	int isRun = 1;  //记录是否移动
	switch (tempMap[tempMe.x][tempMe.y])
	{
		//碰到墙壁回退 
	case 8:
		tempMe += w[(i+2)%4];
		isRun = 0;
		break;

		//推箱子操作 
	case 2:
	case 4:
		//箱子下一格是空地(1)或者终点(3)时进入 
		if (tempMap[xx][yy] % 2) {
			isPush = 1;
			//还原被箱子占住的位置
			tempMap[tempMe.x][tempMe.y] = tempMap[tempMe.x][tempMe.y] == 2 ? 1 : 3;
			if (tempMap[xx][yy] == 3)
				tempMap[xx][yy] = 4;
			else tempMap[xx][yy] = 2;
		}
		else {
			//箱子无法推动回退
			tempMe += w[(i + 2) % 4];
			isRun = 0;
		}
		break;
	}

	if (isRun) {
		s.push(point(i, isPush));
	}
	return judge();
}
