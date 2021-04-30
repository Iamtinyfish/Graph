#include <iostream>
#include <fstream>
#include <stack>
#include <vector>

#define MAX 100

int A[MAX][MAX];
bool checked[MAX];
int n;
int HeadEulerianPath;
int deg[MAX];

void init() {
    for (int i = 1; i <= n; ++i) {
        checked[i] = false;
        deg[i] = 0;
    }
    HeadEulerianPath = 0;
}

void DFS(int i) {
    checked[i] = true;
    for (int j = 1; j <= n; ++j) {
        if (A[i][j] != 0 && checked[j] == false) {
            DFS(j);
        }
    }
}

bool isConnectedGraph() {
    DFS(1);
    for (int i = 1; i <= n; ++i) {
        if (checked[i] == false) return false;
    }
    return true;
}

int numberOfDegreesIsOdd() {
    //count degree
    int x = 1;
    for (int i = 1; i <= n; ++i) {
        for (int j = x; j <= n; ++j) {
            if (A[i][j] != 0) {
                deg[i]++;
                deg[j]++;
            }
        }
        x++;
    }

    //count odd degree
    int count = 0;
    for (int i = 1; i <= n; ++i) {
        if (deg[i] % 2 == 1) {
            count++;
            if (HeadEulerianPath == 0) HeadEulerianPath = i;
        }
    }
    return count;
}

void eulerianPath(int u) {          //find eulerian path or eulerian cycle
    std::stack <int> st;
    std::stack <int> EP;
    int i,j;
    st.push(u);
    while (!st.empty()) {
        i = st.top();
        if (deg[i] > 0)  {
            j = 1;
            while (A[i][j] == 0) j++;
            st.push(j);
            //undirected
            A[i][j] = 0; A[j][i] = 0;
            deg[i]--; deg[j]--;

        }
        else {
            EP.push(st.top());
            st.pop();
        }
    }
    //print path or cycle
    while (!EP.empty()) {
        std::cout << EP.top() << " ";
        EP.pop();
    }
}

void eulerianGraph() {
    if (isConnectedGraph()) {
        int NumberOfDegreesIsOdd = numberOfDegreesIsOdd();
        if (NumberOfDegreesIsOdd == 0) {
            std::cout << "This undirected graph is an Eulerian Graph.\nEuleria Cycle: ";
            eulerianPath(1);
            return;
        }
        if (NumberOfDegreesIsOdd == 2) {
            std::cout << "This undirected graph is a Semi-Eulerian Graph.\nEuleria Path: ";
            eulerianPath(HeadEulerianPath);
            return;
        }
    }
    std::cout << "This graph is not an Eulerian Graph or a Semi-Eulerian Graph";
}

int main()
{   
    std::ifstream InputFile("input.txt");
    if (!InputFile.is_open()) std::cout << "Can not open file!";
    else {
        InputFile >> n;
        init();
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                InputFile >> A[i][j];
            }
        }
        eulerianGraph();
    }
    system("pause");
    return 0;
}