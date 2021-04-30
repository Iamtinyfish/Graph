#include <iostream>
#include <fstream>
#include <queue>

#define MAX 100

using namespace std;

int n;
int A[MAX][MAX];
int checked[MAX];
queue <int> q;

void bfs(int i) {
    q.push(i);
    checked[i] = true;
    while (!q.empty()) {
        i = q.front();
        q.pop();
        cout << i << " ";
        for (int j = 1; j <= n; j++) {
            if (A[i][j] != 0 && checked[j] == false) {
                q.push(j);
                checked[j] = true;
            }
        }
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
        bfs(1);
    }
    return 0;
}