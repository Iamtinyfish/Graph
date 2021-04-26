#include <iostream>
#include <fstream>

#define MAX 100

int A[MAX][MAX];
bool checked[MAX];
int n;
int cycle[MAX];
int CountCycleAndPath = 0;

void init() {
    for (int i = 0; i <= n; i++) {
        checked[i] = false;
        cycle[i] = 0;
    }
}

void print() {
    CountCycleAndPath++;
    int length = n - 1;
    //check Hamilton Cycle
    int temp1 = cycle[n - 1];
    int temp2 = cycle[0];
    if (A[temp1][temp2] != 0) {     
        cycle[n] = temp2;
        length = n;
    }
    //print
    for (int i = 0; i <= length; i++) {
        std::cout << cycle[i] << " ";
    }
    std::cout << "\n";
}

void Hamilton(int k) {
    int i = cycle[k - 1];
    for (int j = 1; j <= n; j++) {
        if (A[i][j] != 0 && checked[j] == false) {
            cycle[k] = j;
            checked[j] = true;
            if (k == n-1) print();
            else Hamilton(k + 1);
            checked[j] = false;
        }
    }
}

void findHamiltonianCycle(int i) {
    init();
    cycle[0] = i;
    checked[i] = true;
    Hamilton(1);
    if (CountCycleAndPath == 0)
        std::cout << "There is no Hamiltonian path or Hamiltonian cycle";
}

int main()
{
    int HeadVetex;
    std::ifstream InputFile("input.txt");
    if (InputFile.fail()) std::cout << "Can not open file!";
    else {
        InputFile >> n;
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                InputFile >> A[i][j];
            }
        }
        InputFile >> HeadVetex;
        findHamiltonianCycle(HeadVetex);
    }
    return 0;
}