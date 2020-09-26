//
// Created by Only Blue on 2020/5/31.
//

#include "Graph.h"
#include <iostream>
#include <queue>
using namespace std;

// 有向无环图 Kahn
template <typename T>
bool topologicalSort(AMGraph<T> G) {
	int size = G.getNumOfVertex();
	vector<vector<int>> arcs = G.getArcs();
	auto *inDegree = new unsigned int[size];
	queue<int> q;
	vector<int> ans;

	int i, j;
	for (i = 0; i < size; i++) {
		inDegree[i] = 0;
		for (j = 0; j < size; j++) {
			if (arcs[i][j])
				inDegree[i]++;
		}
		if (inDegree[i] == 0) {
			q.push(i);
		}
	}

	while (!q.empty()) {
		int temp = q.front();
		q.pop();
		ans.push_back(temp);

		for (i = 0; i < size; i++) {
			if (arcs[temp][i]) {
				inDegree[i]--;
				if (inDegree[i] == 0)
					q.push(i);
			}
		}
	}

	if (ans.size() == size) {
		for (const auto &index: ans)
			cout << index << " ";
		cout << endl;
		return true;
	} else return false;
}

template <typename T>
void visit(AMGraph<T> G, int index, bool*& visited, vector<int>& ans) {
	if(!visited[index]) {
		visited[index] = true;
	}
	int size = G.getNumOfVertex();
	vector<vector<int>> arcs = G.getArcs();

	for(int i = 0; i < size; i++) {
		if(arcs[index][i] && !visited[i]) {
			visit(G, i, visited);
		}
	}
	ans.push_back(index);
}

template <typename T>
bool topologicalSort_dfs(AMGraph<T> G) {
	int size = G.getNumOfVertex();
	bool *visited = new bool [size];
	vector<vector<int>> arcs = G.getArcs();
	auto *inDegree = new unsigned int[size];
	vector<int> ans;
	stack<int> s;

	int i, j;
	for (i = 0; i < size; i++) {
		inDegree[i] = 0;
		for (j = 0; j < size; j++) {
			if (arcs[i][j])
				inDegree[i]++;
		}
		if (inDegree[i] == 0) {
			s.push(i);
		}
	}

	while(!s.empty()) {
		int temp = s.top();
		s.pop();
		visit(G,temp,visited, ans);
	}
	if (ans.size() == size) {
		for (const auto &index: ans)
			cout << index << " ";
		cout << endl;
		return true;
	} else return false;
}
int main() {
    AMGraph<int> g;
    g.create();
    topologicalSort(g);
}
