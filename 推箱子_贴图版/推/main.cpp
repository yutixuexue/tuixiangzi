#include <iostream>
#include "game.h"
using namespace std;

void init() {
	system("title ������С��Ϸ");	//���ñ��� 
	initgraph(800, 600);	// ������ͼ���ڣ���СΪ 800x600 ����
	//system("mode con cols=48 lines=25");	//���ô��ڴ�С 
}

int main() {
	init();
	char op;
	game g;

	do {
		g.print();
		op = _getch();
	} while (!g.run(op));
	
	closegraph();			// �رջ�ͼ����
	return 0;
}
