#include"saolei.h"

aassert::aassert() {
	this->possible = vector<int *>();
}
aassert::~aassert() {
	vector<int *> voidswap;
	possible.swap(voidswap);
}

void autosaolei::restart() {
	warns = 0;
	survival = true;
	vector<int*> voidforswap;
	known.swap(voidforswap);
}

void autosaolei::getknown(mineta &mi) {
	vector<int *> newknown;
	int x, y;
	for (int i = 0; i < mi.tablesize; i++) {
		x = i % mi.len;
		y = i / mi.len;
		if (mi.worktable[i][2] < 1) continue;
		if (((x - 1) >= 0) && ((y - 1) >= 0) && (mi.worktable[(y - 1) * mi.len + x - 1][2] == -1)) {
			newknown.push_back(mi.worktable[i]);
			continue;
		}
		if (((y - 1) >= 0) && (mi.worktable[(y - 1) * mi.len + x][2] == -1)) {
			newknown.push_back(mi.worktable[i]);
			continue;
		}
		if (((x + 1) < mi.len) && ((y - 1) >= 0) && (mi.worktable[(y - 1) * mi.len + x + 1][2] == -1)) {
			newknown.push_back(mi.worktable[i]);
			continue;
		}
		if (((x - 1) >= 0) && (mi.worktable[y * mi.len + x - 1][2] == -1)) {
			newknown.push_back(mi.worktable[i]);
			continue;
		}
		if (((x + 1) < mi.len) && (mi.worktable[y * mi.len + x + 1][2] == -1)) {
			newknown.push_back(mi.worktable[i]);
			continue;
		}
		if (((x - 1) >= 0) && ((y + 1) < mi.heigth) && (mi.worktable[(y + 1) * mi.len + x - 1][2] == -1)) {
			newknown.push_back(mi.worktable[i]);
			continue;
		}
		if (((y + 1) < mi.heigth) && (mi.worktable[(y + 1) * mi.len + x][2] == -1)) {
			newknown.push_back(mi.worktable[i]);
			continue;
		}
		if (((x + 1) < mi.len) && ((y + 1) < mi.heigth) && (mi.worktable[(y + 1) * mi.len + x + 1][2] == -1)) {
			newknown.push_back(mi.worktable[i]);
			continue;
		}
	}
	known.swap(newknown);
}

void autosaolei::getasserts(mineta &mi) {
	vector<aassert> newasserts(known.size());
	int x, y;
	for (unsigned int i = 0; i < known.size(); i++) {
		x = known[i][0];
		y = known[i][1];
		newasserts[i].x = x;
		newasserts[i].y = y;
		newasserts[i].nums = known[i][2];
		if ((x - 1 >= 0) && (y - 1 >= 0) && (mi.worktable[(y - 1) * mi.len + x - 1][2] == -2)) newasserts[i].nums -= 1; // 统计一圈周围未被预警雷数
		if ((y - 1 >= 0) && (mi.worktable[(y - 1) * mi.len + x][2] == -2)) newasserts[i].nums -= 1;
		if ((x + 1 < mi.len) && (y - 1 >= 0) && (mi.worktable[(y - 1) * mi.len + x + 1][2] == -2)) newasserts[i].nums -= 1;
		if (((x - 1) >= 0) && (mi.worktable[y * mi.len + x - 1][2] == -2)) newasserts[i].nums -= 1;
		if (((x + 1) < mi.len) && (mi.worktable[y * mi.len + x + 1][2] == -2)) newasserts[i].nums -= 1;
		if ((x - 1 >= 0) && (y + 1 < mi.heigth) && (mi.worktable[(y + 1) * mi.len + x - 1][2] == -2)) newasserts[i].nums -= 1;
		if ((y + 1 < mi.heigth) && (mi.worktable[(y + 1) * mi.len + x][2] == -2)) newasserts[i].nums -= 1;
		if ((x + 1 < mi.len) && (y + 1 < mi.heigth) && (mi.worktable[(y + 1) * mi.len + x + 1][2] == -2)) newasserts[i].nums -= 1;
		if (((x - 1) >= 0) && ((y - 1) >= 0) && (mi.worktable[(y - 1) * mi.len + x - 1][2] == -1)) {
			newasserts[i].possible.push_back(mi.worktable[(y - 1) * mi.len + x - 1]);
		}
		if (((y - 1) >= 0) && (mi.worktable[(y - 1) * mi.len + x][2] == -1)) {
			newasserts[i].possible.push_back(mi.worktable[(y - 1) * mi.len + x]);
		}
		if (((x + 1) < mi.len) && ((y - 1) >= 0) && (mi.worktable[(y - 1) * mi.len + x + 1][2] == -1)) {
			newasserts[i].possible.push_back(mi.worktable[(y - 1) * mi.len + x + 1]);
		}
		if (((x - 1) >= 0) && (mi.worktable[y * mi.len + x - 1][2] == -1)) {
			newasserts[i].possible.push_back(mi.worktable[y * mi.len + x - 1]);
		}
		if (((x + 1) < mi.len) && (mi.worktable[y * mi.len + x + 1][2] == -1)) {
			newasserts[i].possible.push_back(mi.worktable[y * mi.len + x + 1]);
		}
		if (((x - 1) >= 0) && ((y + 1) < mi.heigth) && (mi.worktable[(y + 1) * mi.len + x - 1][2] == -1)) {
			newasserts[i].possible.push_back(mi.worktable[(y + 1) * mi.len + x - 1]);
		}
		if (((y + 1) < mi.heigth) && (mi.worktable[(y + 1) * mi.len + x][2] == -1)) {
			newasserts[i].possible.push_back(mi.worktable[(y + 1) * mi.len + x]);
		}
		if (((x + 1) < mi.len) && ((y + 1) < mi.heigth) && (mi.worktable[(y + 1) * mi.len + x + 1][2] == -1)) {
			newasserts[i].possible.push_back(mi.worktable[(y + 1) * mi.len + x + 1]);
		}
	}
	asserts.swap(newasserts);
}

void autosaolei::smartjudge(mineta &mi) {
	vector<int *> thesame;
	vector<int *> forworn; // 存储判断过程中确定为雷的格子在函数结尾统一预警（函数运行中预警可能破坏其他断言的结构）
	vector<int *> forclick;//存储判断过程中确定非雷的格子在函数结尾统一点击（点击可能破坏其他断言的结构）
	int maxpossiblenuminthesame;
	int minpossiblenuminthesame;
	bool ifin, ifexist; //两个用来判断循环体是否已经存在于容器中的值
	for (unsigned int i = 0; i < asserts.size(); i++) { // 任意两断言间进行判断
		for (unsigned int j = i + 1; j < asserts.size(); j++) {
			if ((abs(asserts[i].x - asserts[j].x) <= 1) && (abs(asserts[i].y - asserts[j].y) <= 1)) {// 两断言只有在上下左右间距都不超过一格才有判断的价值
				thesame.clear();
				for (auto a : (asserts[i].possible)) { // 找到未点开部分中相同的部分
					for (auto b : asserts[j].possible) {
						if (a == b) {
							thesame.push_back(a);
							break;
						}
					}
				}
				maxpossiblenuminthesame = (asserts[i].nums < asserts[j].nums) ? asserts[i].nums : asserts[j].nums;// 相同部分最大可能雷数
				minpossiblenuminthesame = max(asserts[i].nums + thesame.size() - asserts[i].possible.size(), asserts[j].nums + thesame.size() - asserts[j].possible.size());// 相同部分最小可能雷数
				if ((asserts[i].nums - maxpossiblenuminthesame) == (asserts[i].possible.size() - thesame.size())) { // 通过两断言间相互作用判断某一个断言非公共部分全为雷
					for (auto a : (asserts[i].possible)) { // c++ 没有in 函数真是糟心
						ifin = false;
						for (auto b : thesame) {
							if (a == b) {
								ifin = true;
								break;
							}
						}
						if (!ifin) {
							ifexist = false;
							for (auto x : forworn) {
								if (x == a) {
									ifexist = true;
									break;
								}
							}
							if (!ifexist) forworn.push_back(a);
						}
					}
				}
				if ((asserts[j].nums - maxpossiblenuminthesame) == (asserts[j].possible.size() - thesame.size())) { 
					for (auto a : asserts[j].possible) { 
						ifin = false;
						for (auto b : thesame) {
							if (a == b) {
								ifin = true;
								break;
							}
						}
						if (!ifin) {
							ifexist = false;
							for (auto x : forworn) {
								if (x == a) {
									ifexist = true;
									break;
								}
							}
							if (!ifexist) forworn.push_back(a);
						}
					}
				}
				if (asserts[i].nums == minpossiblenuminthesame) {
					for (auto a : (asserts[i].possible)) { 
						ifin = false;
						for (auto b : thesame) {
							if (a == b) {
								ifin = true;
								break;
							}
						}
						if (!ifin) { 
							ifexist = false;
							for (auto x : forclick) {
								if (x == a) {
									ifexist = true;
									break;
								}
							}
							if(!ifexist) forclick.push_back(a);
						}
					}
				}
				if (asserts[j].nums == minpossiblenuminthesame) {
					for (auto a : (asserts[j].possible)) {
						ifin = false;
						for (auto b : thesame) {
							if (a == b) {
								ifin = true;
								break;
							}
						}
						if (!ifin) {
							ifexist = false;
							for (auto x : forclick) {
								if (x == a) {
									ifexist = true;
									break;
								}
							}
							if (!ifexist) forclick.push_back(a);
						}
					}
				}
			}
		}
	}
	for (auto a : forworn) {
		warns += forworn.size();
		mi.riclick(a[0], a[1]);
	}
	for (auto a : forclick) {
		mi.leclick(a[0], a[1]);
	}
}


void autosaolei::trywarn(mineta &mi, int x, int y) {
	if (mi.worktable[y * mi.len + x][2] < 0) return; // 仅作用于已经点开位置
	int ad = 0;
	if ((x - 1 >= 0) && (y - 1 >= 0) && (mi.worktable[(y - 1) * mi.len + x - 1][2] < 0)) ad += 1;
	if ((y - 1 >= 0) && (mi.worktable[(y - 1) * mi.len + x][2] < 0)) ad += 1;
	if ((x + 1 < mi.len) && (y - 1 >= 0) && (mi.worktable[(y - 1) * mi.len + x + 1][2] < 0)) ad += 1;
	if (((x - 1) >= 0) && (mi.worktable[y * mi.len + x - 1][2] < 0)) ad += 1;
	if (((x + 1) < mi.len) && (mi.worktable[y * mi.len + x + 1][2] < 0)) ad += 1;
	if ((x - 1 >= 0) && (y + 1 < mi.heigth) && (mi.worktable[(y + 1) * mi.len + x - 1][2] < 0)) ad += 1;
	if ((y + 1 < mi.heigth) && (mi.worktable[(y + 1) * mi.len + x][2] < 0)) ad += 1;
	if ((x + 1 < mi.len) && (y + 1 < mi.heigth) && (mi.worktable[(y + 1) * mi.len + x + 1][2] < 0)) ad += 1;
	if (ad == mi.worktable[y * mi.len + x][2]) {
		if ((x - 1 >= 0) && (y - 1 >= 0) && (mi.worktable[(y - 1) * mi.len + x - 1][2] == -1)) {
			warns += 1;
			mi.riclick(x - 1, y - 1);
		}
		if ((y - 1 >= 0) && (mi.worktable[(y - 1) * mi.len + x][2] == -1)) {
			warns += 1;
			mi.riclick(x, y - 1);
		}
		if (((x + 1) < mi.len) && ((y - 1) >= 0) && (mi.worktable[(y - 1) * mi.len + x + 1][2] == -1)) {
			warns += 1;
			mi.riclick(x + 1, y - 1);
		}
		if (((x - 1) >= 0) && (mi.worktable[y * mi.len + x - 1][2] == -1)) {
			warns += 1;
			mi.riclick(x - 1, y);
		}
		if (((x + 1) < mi.len) && (mi.worktable[y * mi.len + x + 1][2] == -1)) {
			warns += 1;
			mi.riclick(x + 1, y);
		}
		if ((x - 1 >= 0) && (y + 1 < mi.heigth) && (mi.worktable[(y + 1) * mi.len + x - 1][2] == -1)) {
			warns += 1;
			mi.riclick(x - 1, y + 1);
		}
		if ((y + 1 < mi.heigth) && (mi.worktable[(y + 1) * mi.len + x][2] == -1)) {
			warns += 1;
			mi.riclick(x, y + 1);
		}
		if ((x + 1 < mi.len) && (y + 1 < mi.heigth) && (mi.worktable[(y + 1) * mi.len + x + 1][2] == -1)) {
			warns += 1;
			mi.riclick(x + 1, y + 1);
		}
	}
}

void autosaolei::randclick(mineta &mi) {
	vector<int *> unknow;
	for (int i = 0; i < mi.tablesize; i++) {
		if (mi.worktable[i][2] == -1) {
			unknow.push_back(mi.worktable[i]);
		}
	}
	if (unknow.size() == 0) return;
	int randint = rand() % unknow.size();
	if (!mi.leclick(unknow[randint][0], unknow[randint][1])) {
		survival = false;
	}
}

bool autosaolei::working(mineta& mi) {
	int x = rand() % mi.len;
	int y = rand() % mi.heigth;
	do {// 第一次点击不会触雷
		this->restart();
		mi.inil();
	} while (mi.minetable[y * mi.len + x][2] != 0); 
	mi.leclick(x, y);
	known.push_back(mi.minetable[0] + y * mi.len + x);
	int record; //记录一个逻辑循环中是否有有效点击
	while (survival && (mi.hasopen != (mi.tablesize - mi.numofmines))) {// 没死且点开全部非雷格子
		record = -1;
		while (record != mi.hasopen) { // 简单判断逻辑
			record = mi.hasopen;
			getknown(mi);
			for (unsigned int i = 0; i < known.size(); i++) {
				trywarn(mi, known[i][0], known[i][1]);
			}
			for (unsigned int i = 0; i < known.size(); i++) {
				mi.findwarn(known[i][0], known[i][1]);
			}
			if (warns < mi.numofmines) {
				getasserts(mi);
				smartjudge(mi);
			}
			record = mi.hasopen;
			getknown(mi);
			for (unsigned int i = 0; i < known.size(); i++) {
				trywarn(mi, known[i][0], known[i][1]);
			}
			for (unsigned int i = 0; i < known.size(); i++) {
				mi.findwarn(known[i][0], known[i][1]);
			}
		}
		//mi.show();
		randclick(mi);
	}
	if (survival) return true;
	else {
		return false;
	}
}

