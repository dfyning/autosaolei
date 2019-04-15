#include"saolei.h"

int main() {
	vector<vector<int>> difs{ { 9, 9, 10 },{ 16, 16, 40 },{ 16, 30, 99 } };
	
	autosaolei ai;
	int j = 0;
	for (int dif = 0; dif < 3; dif++) {
		mineta tab(difs[dif][0], difs[dif][1], difs[dif][2]);
		j = 0;
		for (int i = 0; i < 1000; i++) {
			ai.restart();
			tab.inil();
			if (ai.working(tab)) j++;
		}
		cout << endl;
		cout << j << endl;
	}
	system("pause");
	return 0;
}

