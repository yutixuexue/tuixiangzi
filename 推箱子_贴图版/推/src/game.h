#ifndef GAME_H
#define GAME_H
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>
#include <stack>
#include <conio.h>
#include "point.h"
using namespace std;

const int N = 10; //迷宫最大边 
const int L = 3;  //迷宫最大层数 
const int M = 6;  //箱子最大数
const int Ask = 540; //提示信息显示位置
const point w[4] = { {-1,0},{0,1},{1,0},{0,-1} };//定义移动方向 

/*
	0:空白区域
	1:可通行的区域
	2(o):未到达终点的箱子
	3(x):终点处
	4(O):到达终点处的箱子
	5(i):小人的位置
	6(I):到达终点处的小人
	8(*):墙壁
*/

void copy(int arr1[N][N], int arr2[N][N]); //复制迷宫地图

class game
{
public:
	game();
	void print(); //打印地图信息 
	int option(char op); //操作选项 
	bool run(char op); //进行移动 
	bool judge();  //判断游戏结束 
	bool end();	//结束游戏
	bool restart();	//重新开始 
	bool turn();	//切换关卡 
	bool back();    //回退到上一步 
	void init();    //初始化地图等数据 
	void enter(char &start);   //换行符输入

private:
	int level = 0;			//当前关卡
	int maps[L][N][N] = {	//每关地图
						{
							{8,8,8,8,8,8},
							{8,5,1,3,1,8},
							{8,3,2,1,1,8},
							{8,2,1,2,1,8},
							{8,3,1,1,1,8},
							{8,8,8,8,8,8}
						},
						{
							{0,0,8,8,8,8,8,8,8,8},
							{0,0,8,1,1,1,1,8,8,8},
							{0,0,8,1,2,1,1,1,1,8},
							{8,8,8,1,2,1,8,8,1,8},
							{8,3,3,3,1,2,1,1,1,8},
							{8,3,3,3,2,8,2,1,8,8},
							{8,8,8,8,1,8,1,2,1,8},
							{0,0,0,8,1,1,1,5,1,8},
							{0,0,0,8,8,8,8,8,8,8}
						},{
							{8,8,8,8,8,8,8,8},
							{8,1,1,8,1,1,1,8},
							{8,1,2,3,3,2,1,8},
							{8,5,2,3,4,1,8,8},
							{8,1,2,3,3,2,1,8},
							{8,1,1,8,1,1,1,8},
							{8,8,8,8,8,8,8,8}
					} };
	int tempMap[N][N];		//当前地图
	point me[L];// = { {1,1},{7,7},{3,1} }; //小人每关起始位置
	point tempMe;			//当前小人位置
	stack<point> s;         //保存历史状态(移动方向，是否移动箱子)
	point win[L][M];/* = {		
					{{1,3},{2,1},{4,1}},
					{{4,1},{4,2},{4,3},{5,1},{5,2},{5,3}},
					{{2,3},{2,4},{3,3},{3,4},{4,3},{4,4}}};*///每关胜利位置
	IMAGE Wall, Box, Box_yellow , End, Me; //保存地图图片
};

#endif
