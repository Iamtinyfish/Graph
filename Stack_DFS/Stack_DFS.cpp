#include <iostream>
#include <fstream>
#include <stack>

#define MAX 100

using namespace std;

int n;
int A[MAX][MAX];
int checked[MAX];
stack <int> st;

void dfs(int i) {
	st.push(i);
	checked[i] = true;
	cout << i << " ";
	while (!st.empty()) {
		i = st.top();
		st.pop();
		for (int j = 1; j <= n; j++) {
			if (A[i][j] != 0 && checked[j] == false) {
				st.push(i);
				st.push(j);
				checked[j] = true;
				cout << j << " ";
				break;
			}
		}
	}
}

int main() {
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
		dfs(1);
	}
	system("pause");
	return 0;
}