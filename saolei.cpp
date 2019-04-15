#include"saolei.h"

void mineta::getspace() {
	mines = new int*[tablesize];
	minetable = new int*[tablesize];
	worktable = new int*[tablesize];
}
void mineta::inil() {
	int x, y, randomint;
	int *swap = NULL;
	hasopen = 0;
	haswarn = 0;
	if (mines == NULL) {
		getspace();
	}
	for (int i = 0; i < tablesize; i++) {
		mines[i] = new int[3];
		minetable[i] = new int[3];
		worktable[i] = new int[3];
	}
	for (int i = 0; i < tablesize; i++) {
		x = i % len;
		y = i / len;
		mines[i][0] = x;
		minetable[i][0] = x;
		worktable[i][0] = x;
		mines[i][1] = y;
		minetable[i][1] = y;
		worktable[i][1] = y;
		mines[i][2] = 0;
		minetable[i][2] = 0;
		worktable[i][2] = -1;
	}
	for (int i = 0; i < tablesize; i++) { //����˳��
		randomint = rand() % tablesize;
		swap = mines[i];
		mines[i] = mines[randomint];
		mines[randomint] = swap;
	}
	for (int i = 0; i < numofmines; i++) { //��ǵ���
		mines[i][2] = 1;
		minetable[mines[i][0] + len * mines[i][1]][2] = -1;
	}
	for (int i = 0; i < tablesize; i++) {
		if (minetable[i][2] != -1) {
			x = i % len;
			y = i / len;
			if ((x - 1 >= 0) && (y - 1 >= 0) && (minetable[i - len - 1][2] == -1)) minetable[i][2] += 1;
			if ((y - 1 >= 0) && (minetable[i - len][2] == -1)) minetable[i][2] += 1;
			if ((x + 1 < len) && (y - 1 >= 0) && (minetable[i - len + 1][2] == -1)) minetable[i][2] += 1;
			if (((x - 1) >= 0) && (minetable[i - 1][2] == -1)) minetable[i][2] += 1;
			if (((x + 1) < len) && (minetable[i + 1][2] == -1)) minetable[i][2] += 1;
			if ((x - 1 >= 0) && (y + 1 < heigth) && (minetable[i + len - 1][2] == -1)) minetable[i][2] += 1;
			if ((y + 1 < heigth) && (minetable[i + len][2] == -1)) minetable[i][2] += 1;
			if ((x + 1 < len) && (y + 1 < heigth) && (minetable[i + len + 1][2] == -1)) minetable[i][2] += 1;
		}
	}
}
mineta::mineta(int len, int heigth, int numofmines) {
	this->len = len;
	this->heigth = heigth;
	this->tablesize = len * heigth;
	this->numofmines = numofmines;
	srand(unsigned int(time(NULL)));
	inil();	
}
// ������ ���Ҽ����� ���Ҽ�ͬʱ���
bool mineta::leclick(int x, int y) {		
	if (worktable[y * len + x][2] >= 0) return true; //�Ѿ��㿪�ĸ��ӾͲ��ٲ���
	if (minetable[y * len + x][2] == -1) {
		return false;
	}	
	if (minetable[y * len + x][2] == 0) {
		worktable[y * len + x][2] = 0;
		if ((x - 1 >= 0) && (y - 1 >= 0)) leclick(x - 1, y - 1);
		if (y - 1 >= 0) leclick(x, y - 1);
		if ((x + 1 < len) && (y - 1 >= 0)) leclick(x + 1, y - 1);
		if (x - 1 >= 0) leclick(x - 1, y);
		if (x + 1 < len) leclick(x + 1, y);
		if ((x - 1 >= 0) && (y + 1 < heigth)) leclick(x - 1, y + 1);
		if (y + 1 < heigth) leclick(x, y + 1);
		if ((x + 1 < len) && (y + 1 < heigth)) leclick(x + 1, y + 1);
	}
	hasopen += 1;
	worktable[y * len + x][2] = minetable[y * len + x][2];
	return true;
}
void mineta::riclick(int x, int y) {
	if (worktable[y * len + x][2] >= 0) {
		return;
	}
	if (worktable[y * len + x][2] == -1) { // Ԥ��
		worktable[y * len + x][2] = -2;
		haswarn += 1;
		return;
	}
	if (worktable[y * len + x][2] == -2) { // ���Ԥ��
		worktable[y * len + x][2] = -1;
		haswarn -= 1;
		return;
	}
}
void mineta::findwarn(int x, int y) {
	int ad = 0; // ͳ�Ƹø�����Χ�����Ƿ���ø�������ͬ
	if ((x - 1 >= 0) && (y - 1 >= 0) && (worktable[(y - 1) * len + x - 1][2] == -2)) ad += 1;
	if ((y - 1 >= 0) && (worktable[(y - 1) * len + x][2] == -2)) ad += 1;
	if ((x + 1 < len) && (y - 1 >= 0) && (worktable[(y - 1) * len + x + 1][2] == -2)) ad += 1;
	if (((x - 1) >= 0) && (worktable[y * len + x - 1][2] == -2)) ad += 1;
	if (((x + 1) < len) && (worktable[y * len + x + 1][2] == -2)) ad += 1;
	if ((x - 1 >= 0) && (y + 1 < heigth) && (worktable[(y + 1) * len + x - 1][2] == -2)) ad += 1;
	if ((y + 1 < heigth) && (worktable[(y + 1) * len + x][2] == -2)) ad += 1;
	if ((x + 1 < len) && (y + 1 < heigth) && (worktable[(y + 1) * len + x + 1][2] == -2)) ad += 1;
	if (ad == worktable[y * len + x][2]) { //����ͬ�� ��������ΧһȦ
		if ((x - 1 >= 0) && (y - 1 >= 0) && (worktable[(y - 1) * len + x - 1][2] == -1)) leclick(x - 1, y - 1);
		if ((y - 1 >= 0) && (worktable[(y - 1) * len + x][2] == -1)) leclick(x, y - 1);
		if ((x + 1 < len) && (y - 1 >= 0) && (worktable[(y - 1) * len + x][2] == -1)) leclick(x + 1, y - 1);
		if (((x - 1) >= 0) && (worktable[y * len + x - 1][2] == -1)) leclick(x - 1, y);
		if (((x + 1) < len) && (worktable[y * len + x + 1][2] == -1)) leclick(x + 1, y);
		if ((x - 1 >= 0) && (y + 1 < heigth) && (worktable[(y + 1) * len + x - 1][2] == -1)) leclick(x - 1, y + 1);
		if ((y + 1 < heigth) && (worktable[(y + 1) * len + x][2] == -1)) leclick(x, y + 1);
		if ((x + 1 < len) && (y + 1 < heigth) && (worktable[(y + 1) * len + x + 1][2] == -1)) leclick(x + 1, y + 1);
	}
}
mineta::~mineta() {
	if (mines != NULL) {
		for (int i = 0; i < tablesize; i++) {
			delete mines[i];
		}
		delete mines;
	}
	if (minetable != NULL) {
		for (int i = 0; i < tablesize; i++) {
			delete minetable[i];
		}
		delete minetable;
	}
	if (worktable != NULL) {
		for (int i = 0; i < tablesize; i++) {
			delete worktable[i];
		}
		delete worktable;
	}
}
void mineta::show() {
	system("cls");
	for (int i = 0; i < tablesize; i++) {
		cout<< setw(3) << worktable[i][2];
		if (!((i + 1) % len)) {
			cout << endl;
		}
	}
	cout << "-----------------------------" << endl;
	for (int i = 0; i < tablesize; i++) {
		cout << setw(3) << minetable[i][2];
		if (!((i + 1) % len)) {
			cout << endl;
		}
	}
}




