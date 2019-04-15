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
	int nums; // ��δԤ������
	vector<int*> possible;
	aassert();
	~aassert();
};

class mineta {
public:
	void getspace();
	void inil();
	int len; //���
	int heigth; //�߶�
	int tablesize; //len * height
	int numofmines; // ����
	int hasopen;
	int haswarn;
	int** mines; // ǰnumofminesΪ���� ����ǰ��λΪ����
	int** minetable; // ��Ȼ��Ϊ�ø�����Χ���� -1��ʾ�ø�����
	int** worktable; // -1��ʾδ֪�� -2��ʾԤ����ĵ��ף� ��Ȼ����ʾ�㿪�ĸø�����Χ������
	mineta(int len, int heigth, int numofmines);
	~mineta();
	bool leclick(int x, int y); //������
	void riclick(int x, int y); // �Ҽ����
	void findwarn(int x, int y);// ���Ҽ�һͬ���
	void show();
};
class autosaolei {
public:
	int warns = 0; // ͳ����Ԥ��������
	bool survival = true;
	vector<int*> known; // �����ѵ㿪���ܱ���δ�㿪���ӵĸ���
	vector<aassert> asserts; // �������еĶ���
	void restart(); // ���¿�ʼ
	bool working(mineta& mi); // ���Ĺ�������
	void getknown(mineta &mi); // �õ��㿪��δ�㿪�߽��ϵ���֪���и���
	void getasserts(mineta &mi); //ˢ�����ж���
	void smartjudge(mineta &mi); //�߼��ж�
	void trywarn(mineta &mi, int x, int y); // ���ܱ�δ�㿪���ӵ��ڸø����� ȫ��Ԥ��
	void randclick(mineta &mi); //û���ƶ����ʱ�����ѡ
};



#endif 