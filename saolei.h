#ifndef __SAOLEI_H__
#define __SAOLEI_H__


#pragma once
#include<iostream>
#include<iomanip>
#include<random>
#include<vector>
using namespace std;

struct aassert {
	int x;
	int y;
	int nums; // 尚未预警雷数
	vector<int*> possible;
	aassert();
	~aassert();
};

class mineta {
public:
	void getspace();
	void inil();
	int len; //宽度
	int heigth; //高度
	int tablesize; //len * height
	int numofmines; // 雷数
	int hasopen;
	int haswarn;
	int** mines; // 前numofmines为地雷 表中前两位为坐标
	int** minetable; // 自然数为该格子周围雷数 -1表示该格有雷
	int** worktable; // -1表示未知， -2表示预警后的地雷， 自然数表示点开的该格子周围雷数。
	mineta(int len, int heigth, int numofmines);
	~mineta();
	bool leclick(int x, int y); //左键点击
	void riclick(int x, int y); // 右键点击
	void findwarn(int x, int y);// 左右键一同点击
	void show();
};
class autosaolei {
public:
	int warns = 0; // 统计已预警地雷数
	bool survival = true;
	vector<int*> known; // 放置已点开而周边有未点开格子的格子
	vector<aassert> asserts; // 放置所有的断言
	void restart(); // 从新开始
	bool working(mineta& mi); // 核心工作进程
	void getknown(mineta &mi); // 得到点开和未点开边界上的已知所有格子
	void getasserts(mineta &mi); //刷新所有断言
	void smartjudge(mineta &mi); //高级判断
	void trywarn(mineta &mi, int x, int y); // 若周边未点开格子等于该格数字 全部预警
	void randclick(mineta &mi); //没有推断余地时随机挑选
};



#endif 