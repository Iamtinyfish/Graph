#include <iostream>
#include <queue>
#include <fstream>
#include <stack>

#define MAX 100

using namespace std;

int n,u,v;          //Find the path from u to v
int A[MAX][MAX];    
int checked[MAX];
stack <int> st;
queue <int> q;
int previousVertexOf[MAX];

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
                previousVertexOf[j] = i;
                if (j == v) return;
            }
        }
    }
}

void dfs(int i) {
    st.push(i);
    checked[i] = true;
    while (!st.empty()) {
        i = st.top();
        st.pop();
        for (int j = 1; j <= n; j++) {
            if (A[i][j] != 0 && checked[j] == false) {
                st.push(i);
                st.push(j);
                checked[j] = true;
                previousVertexOf[j] = i;
                if (j == v) return; 
                break;
            }
        }
    }
}

void findPath() {
    //bfs(u);             //the shortest path

    dfs(u);

    if (previousVertexOf[v] == 0) cout << "The path from u to v doesn't exist!";
    else {
        //Record path
        int i = v;
        stack <int> path;
        path.push(i);
        while (i != u) {
            i = previousVertexOf[i];
            path.push(i);
        }

        //Print path
        cout << "The path from u to v: ";
        cout << path.top();
        path.pop();
        i = path.size();
        while (i--) {
            cout << " -> " << path.top();
            path.pop();
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
        InputFile >> u >> v;
        InputFile.close();
        findPath();
    }
    system("pause");
    return 0;
}
