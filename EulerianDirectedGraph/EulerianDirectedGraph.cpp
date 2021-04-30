#include <iostream>
#include <fstream>
#include <stack>
#include <vector>

#define MAX 100

int A[MAX][MAX];
int UndrectedGraphOf_A[MAX][MAX];           
bool checked[MAX];
int n;

int HeadEulerianPath = 0;
int TailEulerianPath = 0;
int indegree[MAX];                          //array of deg-(u)
int outdegree[MAX];                         //array of deg+(u)
int DifferenceOfDegree_1 = 0;               //number of vetex u ~ deg+(u) - deg-(u) = 1
int DifferenceOfDegree_0 = 0;               //number of vetex u ~ deg+(u) - deg-(u) = 0
int DifferenceOfDegree_negative_1 = 0;      //number of vetex u ~ deg+(u) - deg-(u) = -1

void init() {
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            UndrectedGraphOf_A[i][j] = 0;
        }
        checked[i] = false;
        indegree[i] = 0;
        outdegree[i] = 0;
    }
    HeadEulerianPath = 0;
    TailEulerianPath = 0;
    DifferenceOfDegree_1 = 0;
    DifferenceOfDegree_0 = 0;
    DifferenceOfDegree_negative_1 = 0;
}

void DFS(int i) {               //with Undrected Graph Of A
    checked[i] = true;
    for (int j = 1; j <= n; ++j) {
        if (UndrectedGraphOf_A[i][j] != 0 && checked[j] == false) {
            DFS(j);
        }
    }
}

void createUndrectedGraphOf_A() {
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (A[i][j] != 0) {
                UndrectedGraphOf_A[i][j] = A[i][j];
                UndrectedGraphOf_A[j][i] = A[i][j];
            }
        }
    }
}

bool isWeaklyConnectedGraph() {
    createUndrectedGraphOf_A();
    DFS(1);
    for (int i = 1; i <= n; ++i) {
        if (checked[i] == false) return false;
    }
    return true;
}

void countDegreeOfVetex() {
    //count degree of vetex
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (A[i][j] != 0) {
                outdegree[i]++;
                indegree[j]++;
            }
        }
    }
}
void countDifferenceOfDegree() {
    //count difference of degree
    int difference;
    for (int i = 1; i <= n; ++i) {
        difference = outdegree[i] - indegree[i];        //difference = deg+(u) - deg-(u)
        if (difference == 0) DifferenceOfDegree_0++;
        else {
            if (difference == 1) {
                DifferenceOfDegree_1++;
                HeadEulerianPath = i;
            }
            if (difference == -1) {
                DifferenceOfDegree_negative_1++;
                TailEulerianPath = i;
            }
        }
    }
}

void eulerianPath(int u) {      //find eulerian path or eulerian cycle
    std::stack <int> st;
    std::stack <int> EP;
    int i, j;
    st.push(u);
    while (!st.empty()) {
        i = st.top();
        if (outdegree[i] > 0) {
            j = 1;
            while (A[i][j] == 0) j++;
            st.push(j);
            A[i][j] = 0;
            outdegree[i]--;

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

void eulerianGraph() {                  //Check the graph 
    if (isWeaklyConnectedGraph()) {
        countDegreeOfVetex();
        countDifferenceOfDegree();
        if (DifferenceOfDegree_0 == n) {
            std::cout << "This directed graph is an Eulerian Graph.\nEuleria Cycle: ";
            eulerianPath(1);
            return;
        }
        if (DifferenceOfDegree_0 == n-2 
            && DifferenceOfDegree_1 == 1 
            && DifferenceOfDegree_negative_1 ==1) {
            std::cout << "This directed graph is a Semi-Eulerian Graph.\nEuleria Path: ";
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
    return 0;
}