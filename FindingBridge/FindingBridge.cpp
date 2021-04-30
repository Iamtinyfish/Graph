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

int numberOfConnectedComponents() {
    int NumberOfConnectedComponents = 0;
    for (int i = 1; i <= n; i++) {
        if (checked[i] == false) {
            NumberOfConnectedComponents++;
            bfs(i);
        }
    }
    return NumberOfConnectedComponents;
}

// directed graph
void findingBridge() {
    int NumberOfConnectedComponents = numberOfConnectedComponents();
    int temp_edge;
    int temp_NumberOfConnectedComponents;
    cout << "Bridge edges: ";
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (A[i][j] != 0) {
                temp_edge = A[i][j];
                A[i][j] = 0;    //pop 1 edge
                //Is this edge bridge?
                temp_NumberOfConnectedComponents = numberOfConnectedComponents();
                if (temp_NumberOfConnectedComponents > NumberOfConnectedComponents) 
                    cout << "\n(" << i << "," << j << ") ; "; // ? yes -> print it
                
                init();
                A[i][j] = temp_edge; // return edge
            }
        }
    }
    cout << endl;
}

//undirected graph
/*
void findingBridge() {
    int NumberOfConnectedComponents = numberOfConnectedComponents();
    int temp_edge;
    int temp_NumberOfConnectedComponents;
    cout << "Bridge edges: ";
    for (int i = 1; i <= n; i++) {
        for (int j = i+1; j <= n; j++) {
            if (A[i][j] != 0) {
                temp_edge = A[i][j];
                A[i][j] = 0; A[j][i] = 0; //pop 1 edge
                //Is this edge bridge?
                temp_NumberOfConnectedComponents = numberOfConnectedComponents();
                if (temp_NumberOfConnectedComponents > NumberOfConnectedComponents) 
                    cout << "\n(" << i << "," << j << ") ; "; // ? yes -> print it
                
                init();
                A[i][j] = temp_edge; A[j][i] = temp_edge;// return edge
            }
        }
    }
    cout << endl;
}
*/

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
        findingBridge();
    }
    system("pause");
    return 0;
}