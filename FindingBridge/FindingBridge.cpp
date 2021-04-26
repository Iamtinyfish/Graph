#include <iostream>
#include <fstream>
#include <queue>

#define MAX 100

using namespace std;

int n;
int A[MAX][MAX];
bool checked[MAX];
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

// directed graph
void findingBridge() {
    int temp;
    cout << "Bridge edges: ";
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (A[i][j] != 0) {
                temp = A[i][j];
                A[i][j] = 0;    //pop 1 edge
                //Is this edge bridge?
                bfs(1);
                if (!connected()) cout << "(" << i << "," << j << ") ; "; // ? yes -> print it
                //
                init();
                A[i][j] = temp; // return edge
            }
        }
    }
}

//undirected graph
/*
void findingBridge() {
    int temp;
    cout << "Bridge edges: ";
    for (int i = 1; i <= n; i++) {
        for (int j = i+1; j <= n; j++) {
            if (A[i][j] != 0) {
                temp = A[i][j];
                A[i][j] = 0; A[j][i] = 0; //pop 1 edge
                //Is this edge bridge?
                bfs(1);
                if (!connected()) cout << "(" << i << "," << j << ") ; "; // ? yes -> print it
                //
                init();
                A[i][j] = temp; A[j][i] = temp;// return edge
            }
        }
    }
}
*/

int main()
{
    ifstream InputFile("input.txt");
    if (InputFile.fail()) cout << "Can not open file or file exists!";
    else {
        InputFile >> n;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                InputFile >> A[i][j];
            }
        }
        findingBridge();
    }
    return 0;
}