#include <iostream>
#include <fstream>
#include <stack>
#include <queue>

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

bool Connected() {                  //check ? (BFS(i) or DFS(i) == V (Vertice)) true : false
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
    checked[i];
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

bool StronglyConnected() {
    for (int i = 1; i <= n; i++) {
        init();
        bfs(i); 
        //dfs(i);
        if (!Connected()) return false;
    }
    return true;
}

int main()
{
    ifstream InputFile("input.txt");
    if (!InputFile.is_open()) cout << "Can not open file  or file exists";
    else {
        InputFile >> n;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                InputFile >> A[i][j];
            }
        }
        InputFile.close();

        if (StronglyConnected()) 
            cout << "Graph is strongly connected.";
        else 
            cout << "Graph is not strongly connected.";
    }
    system("pause");
    return 0;
}