#include <iostream>
#include <fstream>

#define MAX 100

using namespace std;

int n;
int A[MAX][MAX];
bool checked[MAX];


void dfs(int i) {
	checked[i] = true;
	cout << i << " ";
	for (int j = 1; j <= n; j++) {
		if (A[i][j] != 0 && checked[j] == false) {
			dfs(j);
		}
	}
}

int main() {
	ifstream InputFile("input.txt");

	if (!InputFile.is_open()) cout << "Can't open file or file exists!";
	else {
		InputFile >> n;
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				InputFile >> A[i][j];
			}
		}
		InputFile.close();
		dfs(1);
	}
	system("pause");
	return 0;
}
