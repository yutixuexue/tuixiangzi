#include <iostream>
#include "game.h"
using namespace std;

void init() {
	system("title 推箱子小游戏");	//设置标题 
	initgraph(800, 600);	// 创建绘图窗口，大小为 800x600 像素
	//system("mode con cols=48 lines=25");	//设置窗口大小 
}

int main() {
	init();
	char op;
	game g;

	do {
		g.print();
		op = _getch();
	} while (!g.run(op));
	
	closegraph();			// 关闭绘图窗口
	return 0;
}
