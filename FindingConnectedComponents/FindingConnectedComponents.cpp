#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
#include <stack>
#define MAX 100

using namespace std;

int n;
int A[MAX][MAX];
bool checked[MAX];
queue <int> q;
stack <int> st;
vector < vector <int> > Connected_Component;


void bfs(int i) {
	vector <int> Element_of_Connected_Component;
	q.push(i);
	checked[i] = true;
	while (!q.empty()) {
		i = q.front();
		q.pop();
		Element_of_Connected_Component.push_back(i);
		for (int j = 1; j <= n; j++) {
			if (A[i][j] != 0 && checked[j] == false) {
				q.push(j);
				checked[j] = true;
			}
		}
	}
	Connected_Component.push_back(Element_of_Connected_Component);
}

void dfs(int i) {
	vector <int> Element_of_Connected_Component;
	st.push(i);
	checked[i] = true;
	Element_of_Connected_Component.push_back(i);
	while (!st.empty()) {
		i = st.top();
		st.pop();
		for (int j = 1; j <= n; j++) {
			if (A[i][j] != 0 && checked[j] == false) {
				st.push(i);
				st.push(j);
				checked[j] = true;
				Element_of_Connected_Component.push_back(j);
				break;
			}
		}
	}
	Connected_Component.push_back(Element_of_Connected_Component);
}

void findingConnectedComponent() {
	int NumberOfConnectedComponents = 0;
	for (int i = 1; i <= n; i++) {
		if (checked[i] == false) {
			NumberOfConnectedComponents++;
			//bfs(i);
			dfs(i);
		}
	}
	//print result
	cout << "Number of connected components: " << NumberOfConnectedComponents << endl;
	for (int i = 0; i < Connected_Component.size(); i++) {
		cout << "Connected component " << i + 1 << " : ";
		for (int j = 0; j < Connected_Component[i].size(); j++) {
			cout << Connected_Component[i][j] <<" ";
		}
		cout << endl;
	}
	//
}


int main()
{
	ifstream InputFile("input.txt");
	if (!InputFile.is_open()) cout << "Can not open file or file exists! ";
	else {
		InputFile >> n;
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				InputFile >> A[i][j];
			}
		}
		InputFile.close();
		findingConnectedComponent();
	}
	system("pause");
	return 0;
}
