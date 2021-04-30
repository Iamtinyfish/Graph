#include <queue>
#include <fstream>
#include <iostream>

#define MAX 100

using namespace std;

int n;
int A[MAX][MAX];
int checked[MAX];
queue <int> q;

void init() {
	for (int i = 1; i <= n; i++) {
		checked[i] = false;
	}
}

bool connected() {
	for (int i = 1; i <= n; i++) {
		if (!checked[i]) return false;
	}
	return true;
}

void dfs(int i) {
	checked[i] = true;
	for (int j = 1; j <= n; j++) {
		if (A[i][j] != 0 && checked[j] == false) {
			dfs(j);
		}
	}
}

void bfs(int i) {
	q.push(i);
	checked[i] = true;
	while (!q.empty()) {
		i = q.front();
		q.pop();
		for (int j = 1; j <= n; j++) {
			if (A[i][j] != 0 && checked[j] == false) {
				q.push(j);
				checked[j] = true;
			}
		}
	}
}

void findingArticulationPoint() {
	cout << "Articulation points: ";
	for (int i = 1; i <= n; i++) {
		init();
		checked[i] = true;
		if (i == 1) dfs(2);
		else dfs(1);
		if (!connected()) cout << i << " ";
	}
}


int main()
{
	ifstream InputFile("input.txt");
	if (!InputFile.is_open()) cout << "Can not open file or file exists!";
	else {
		InputFile >> n;
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				InputFile >> A[i][j];
			}
		}
		InputFile.close();
		findingArticulationPoint();
	}
	return 0;
}