//
// Created by Only Blue on 2020/6/5.
//

#ifndef DS_3_GRAPH_GRAPH_H
#define DS_3_GRAPH_GRAPH_H
#include <iostream>
#include <vector>
#include <stack>
#include <iomanip>
#include <string>
#include <queue>
#include <fstream>
#include "UnionFind.h"
const long INF = 0x3fffffff;
using namespace std;

// GraphKind: Undirected Graph, Directed Graph, Undirected Network, Directed Network
typedef enum{UDG = 1, DG, UDN, DN}GraphKind;

template <typename T>
class AMGraph { // Adjacent Matrix Graph
private:
	vector<T> vexs;           // This vector is to store vertex
	int vex_num;              // the amount of vertex, which is equal to vector vexs.size()
	int arc_num;              // the amount of arc
	vector<vector<int>> arcs; // two-dimensional vector, type is integer
	bool *visited{};             // bool array, to judge whether the vertex has been visited
	GraphKind kind;           // type of graph
public:
	// constructor
	AMGraph() : vex_num(0), arc_num(0) {};

	// create graph
	void create(const string &vertex_filename, const string &arc_filename, GraphKind kind);

	// recreate
	void recreate(const string &vertex_filename, const string &arc_filename, GraphKind kind);

	// depth first search
	void dfs(int index);

	// depth first search by stack
	void dfs_by_stack(int index);

	// board first search
	void bfs(int index);

	// reset visited array
	void reset_visited();

	// display Adjacent Matrix
	void displayMatrix();

	// Prim(Traditional Version)
	void Prim(int index);

	// Prim(Heap Version)
	void Prim_by_heap(int index);

	// Kruskal
	void Kruskal();

	// Dijkastra
	void Dijkastra(int index);

	// Floyd
	void Floyd();

	// get vex_num;
	int getVexNum() const { return vex_num; }

	// kind
	GraphKind getKind() const { return kind; }

	// get the number of vertex
	int getNumOfVertex() const { return arcs.size(); }

	// get adjacent Matrix
	vector<vector<int>> getArcs() const { return arcs; }

protected:
	int locateVex(T data);
};

template <typename T>
int AMGraph<T>::locateVex(T data) {
    int i = 0;
    for (; i < vexs.size(); i++) {
        if (vexs[i] == data) {
            return i;
        }
    }
    return -1;
}

template <typename T>
void AMGraph<T>::create(const string& vertex_filename, const string& arc_filename, GraphKind k) {
    kind = k;
    ifstream fp;
    fp.open(vertex_filename, ios::in);
    while (fp.peek() != EOF) {
        T temp;
        fp >> temp;
        vexs.push_back(temp);
        vex_num++;
    }
    fp.close();
    visited = new bool[vex_num];
    vector<int> vTemp(vex_num, 0);
    for (int i = 0; i < vexs.size(); i++) {
        arcs.push_back(vTemp);
        visited[i] = false;
    }

    fp.open(arc_filename, ios::in);
    while (fp.peek() != EOF) {
        T tail, head;
        int tail_index, head_index;

        fp >> tail >> head;
        tail_index = locateVex(tail);
        head_index = locateVex(head);
        if (tail_index == -1 || head_index == -1) {
            return;
        }

        if (kind == UDG) {
            arcs[tail_index][head_index] = 1;
            arcs[head_index][tail_index] = 1;

        } else if (kind == DG) {
            arcs[tail_index][head_index] = 1;

        }
        else if(kind == UDN) {
            int weight;
            fp >> weight;

            arcs[head_index][tail_index] = weight;
            arcs[tail_index][head_index] = weight;
        }
        else if(kind == DN) {
            int weight;
            fp >> weight;
            arcs[tail_index][head_index] = weight;
        }
        arc_num++;
    }
    fp.close();
}


template <typename T>
void AMGraph<T>::recreate(const string& vertex_filename, const string& arc_filename, GraphKind kind) {
	vex_num = 0;arc_num = 0;
	vexs.clear();
	arcs.clear();
	create(vertex_filename, arc_filename,kind);
}

template <typename T>
void AMGraph<T>::dfs(int index) {
    visited[index] = true;
    cout << vexs[index] << " ";

    for(int i = 0; i < vex_num; i++) {
        if(arcs[index][i] && !visited[i]) {
            dfs(i);
        }
    }
}

template <typename T>
void AMGraph<T>::dfs_by_stack(int index) {
	cout << "dfs(stack version): " << endl;
	reset_visited();
    stack<int> s;
    visited[index] = true;
    s.push(index);

    cout << vexs[index] << " ";

    while(!s.empty()) {
        int top = s.top();
        s.pop();
        if(!visited[top]) {
            cout << vexs[top] << " ";
            visited[top] = true;
        }

        for(int i = 0; i < vex_num; i++) {
            if(arcs[top][i] != 0 && !visited[i])
                s.push(i);
        }
    }
    cout << endl;
}

template <typename T>
void AMGraph<T>::bfs(int index) {
	cout << "bfs: " << endl;
    queue<int> q;
    visited[index] = true;
    cout << vexs[index] <<" ";
    q.push(index);

    while(!q.empty()) {
        int front = q.front();
        q.pop();
        if(!visited[front]) {
            cout << vexs[front] << " ";
            visited[front] = true;
        }

        for(int i = 0; i < vex_num; i++) {
            if(arcs[front][i] != 0 && !visited[i])
                q.push(i);
        }
    }
    cout << endl;
}

template <typename T>
void AMGraph<T>::reset_visited() {
    for(int i = 0; i < vex_num; i++)
        visited[i] = false;
}

template <typename T>
void AMGraph<T>::displayMatrix() {
    if (arcs.empty()) // 判断是否为空矩阵
        return;
    cout << "Adjacent Matrix:" << endl;
    cout << endl << "      ";
    for (int i = 0; i < vexs.size(); i++)
        cout << setw(6) << setiosflags(ios::left) << vexs[i];
    cout << endl;

    for (int i = 0; i < arcs.size(); i++) {
        cout << setw(6) << setiosflags(ios::left) << vexs[i];
        for (const auto &j:arcs[i]) {
            cout << setw(6) << setiosflags(ios::left) << j;
        }
        cout << endl;
    }
    cout << endl;
}

template <typename T>
void AMGraph<T>::Prim(int index) {
    cout << "Prim" << endl;
    reset_visited();
    int *lowcost = new int[vex_num];
    int *closest = new int[vex_num];

    for (int i = 0; i < vex_num; i++) {
	    if (arcs[index][i] == 0)
		    lowcost[i] = INF;
	    else
		    lowcost[i] = arcs[index][i];

	    closest[i] = index;
    }

    int k = -1;
    for (int i = 1; i < vex_num; i++) {
        int min = INT_MAX;
        for (int j = 0; j < vex_num; j++) {
            if (lowcost[j] != 0 && lowcost[j] < min) {
                min = lowcost[j];
                k = j;
            }
        }
        cout << vexs[closest[k]] << "->" << vexs[k] << " weight: " << arcs[closest[k]][k] << endl;
        lowcost[k] = 0;

        for (int j = 0; j < vex_num; j++) {
            if (lowcost[j] != 0 && arcs[k][j] < lowcost[j] && arcs[k][j] != 0) {
                lowcost[j] = arcs[k][j];
                closest[j] = k;
            }
        }
    }
}

struct Edge {
    int from;
    int to;
    int weight;

    explicit Edge(int f = 0, int t = 0, int w = 0) : from(f), to(t), weight(w) {}
};

struct Compare {
    bool operator()(const Edge* arg1, const Edge* arg2) {
        return arg1->weight > arg2->weight;
    }
};

template <typename T>
void AMGraph<T>::Prim_by_heap(int index) {
    cout << "Prim_By_Heap" << endl;
    reset_visited();
    visited[index] = true;
    priority_queue<Edge*, vector<Edge*>, Compare> PQ;
    for(int i = 0; i < vex_num; i++) {
        if(arcs[index][i] != 0) {
            PQ.push(new Edge(index, i, arcs[index][i]));
        }
    }

    int visited_num = 1;
    while(visited_num < vex_num) {
        auto temp = PQ.top();
        PQ.pop();
        if(!visited[temp->to]) {
            cout << "arc: " <<vexs[temp->from] << "->" << vexs[temp->to] << ", weight: " << temp->weight << endl;
            visited[temp->to] = true;
            visited_num++;
        }

        for(int i = 0; i < vex_num; i++) {
            if (arcs[temp->to][i]!=0 && !visited[i]) {
                PQ.push(new Edge(temp->to, i, arcs[temp->to][i]));
            }
        }
    }
}

template <typename T>
void AMGraph<T>::Kruskal() {
	cout << "Kruskal" << endl;
    priority_queue<Edge *, vector<Edge *>, Compare> PQ;
    auto *UF = new UnionFind(vex_num);

    for (int i = 0; i < arcs.size(); i++) {
        int j;
        if (kind == UDN || kind == UDG) j = i;
        else j = 0;
        for (; j < arcs[i].size(); j++) {
            if (arcs[i][j] != 0) {
                PQ.push(new Edge(i, j, arcs[i][j]));
            }
        }
    }

    int count = 0;
    while (count < vex_num - 1) {
        Edge *temp = PQ.top();
        PQ.pop();

        if(!UF->connected(temp->from, temp->to)) {
            if (kind == DN || kind == UDN)
                cout << "arc: " << vexs[temp->from] << "->" << vexs[temp->to] << ", weight: " << temp->weight << endl;
            else
                cout << "arc: " << vexs[temp->from] << "->" << vexs[temp->to] << endl;
            UF->Union(temp->from, temp->to);
        }
        visited[temp->from] = true;
        visited[temp->to] = true;
        count++;
    }
}

template <typename T>
void AMGraph<T>::Dijkastra(int index) {
	cout << "Dijkastra" << endl;
    int *distance = new int[vex_num];
    reset_visited();

    vector<vector<int>> paths;
    vector<int> path(1, 0);
    // The first element of vector path is to store the length of shortest path
    path.push_back(index);
    for (int i = 0; i < vex_num; i++) {
        paths.push_back(path);
        if(arcs[index][i] != 0)
            distance[i] = arcs[index][i];
        else
            distance[i] = INF;
    }
    distance[index] = 0;
    visited[index] = true;
    int k = -1;
    for(int i = 1; i < vex_num; i++) {
        int min = INF;
        k = -1;

        for (int j = 0; j < vex_num; j++) {
            if (!visited[j] && distance[j] < min) {
                min = distance[j];
                k = j;
            }
        }

        visited[k] = true;

        paths[k].push_back(k);
        paths[k][0] = min;

        for (int j = 0; j < vex_num; j++) {
            if (distance[j] > distance[k] + arcs[k][j] && arcs[k][j] != 0 && arcs[k][j] != 0) {
                distance[j] = distance[k] + arcs[k][j];
                paths[j][0] += distance[j];
                for(int z = 2; z < paths[k].size();z++ )
                paths[j].push_back(paths[k][z]);
            }
        }
        distance[k] = 0;
    }

    for(int i = 0; i < vex_num; i++) {
        cout << vexs[index] << "->" << vexs[i] <<": path: " ;
        for(int j = 1; j < paths[i].size(); j++) {
            cout << vexs[paths[i][j]];
            if(j < paths[i].size()-1)
                cout << "->";
        }
        cout << ", weight: " << paths[i][0];
        cout << endl;
    }
}

template <typename T>
void AMGraph<T>::Floyd() {
	cout << "Floyd" << endl;
    vector<vector<int>> Matrix;
    vector<vector<int>> path;
    vector<int> p(vex_num, 0);
    for (int i = 0; i < vex_num; i++) {
        vector<int> temp;
        for (int j = 0; j < vexs.size(); j++) {
            if (i != j && arcs[i][j] == 0)
                temp.push_back(INF);
            else
                temp.push_back(arcs[i][j]);
        }
        Matrix.push_back(temp);
        path.push_back(p);
    }

    for (int k = 0; k < vex_num; k++)
        for (int i = 0; i < vex_num; i++)
            for (int j = 0; j < vex_num; j++) {
                if (Matrix[i][j] > Matrix[i][k] + Matrix[k][j]) {
                    Matrix[i][j] = Matrix[i][k] + Matrix[k][j];
                    path[i][j] = k;
                }
            }

    // Print Path
    for (int i = 0; i < vex_num; i++) {
        cout << vexs[i] << endl;
        for (int j = 0; j < vex_num; j++) {
            cout << vexs[i] << "->" << vexs[j] << "  path: ";
            if (path[i][j] == 0 && Matrix[i][j] == INF)
                cout << "None, weight: inf";
            else if (path[i][j] == i && i == j)
                cout << vexs[i] << "->" << vexs[i] << ", weight: 0";
            else if (path[i][j] == 0 && Matrix[i][j] != INF)
                cout << vexs[i] << "->" << vexs[j] << ", weight: " << Matrix[i][j];
            else {
                stack<int> s;
                int temp = path[i][j];
                while(true) {
                    if(temp == 0) {
                        break;
                    }
                    s.push(temp);
                    temp = path[i][temp];
                }
                cout << vexs[i] << "->";
                while(!s.empty()) {
                    cout << vexs[s.top()];
                    s.pop();
                    if(!s.empty())
                        cout << "->";
                }
                cout << "->" << vexs[j] << ", weight: " << Matrix[i][j];
            }
            cout << endl;
        }
        cout << endl;
    }
}

//====================ALGraph=====================//

struct ArcNode {
    int weight;
    int index;     // index in vexs
    ArcNode *next; // next pointer
    explicit ArcNode(int in = -1, int w = 0): index(in), weight(w) ,next(nullptr) {};
};

template <typename T>
struct VexNode {
    T data;
    ArcNode *first_arc;

    // constructor
    explicit VexNode(T d = 0): data(d), first_arc(new ArcNode(d)) {};
};

template <typename T>
class ALGraph { // Adjacent Matrix Graph
private :
	vector<VexNode<T> *> vertex; // This vector is to store vertex
	int vex_num;                 // the amount of vertex
	int arc_num;                 // the amount of arc
	GraphKind kind;              // type of graph
public:
	// Constructor
	ALGraph() : vex_num(0), arc_num(0) {}

	// Destroyer
	~ALGraph();

	// Create ALGraph
	void create(const string &vertex_filename, const string &arc_filename, GraphKind k);

	// Print Adjacent List
	void displayList();

protected:
	int locateVex(T data);

	void destroyList(ArcNode *List);
};

template <typename T>
int ALGraph<T>::locateVex(T data) {
    int i = 0;
    for (; i < vertex.size(); i++) {
        if (vertex[i]->data == data) {
            return i;
        }
    }
    return -1;
}

template <typename T>
void ALGraph<T>::destroyList(ArcNode *List) {
    ArcNode *pNode = nullptr;
    while(List) {
        pNode = List->next;
        delete List;
        List = pNode;
    }
}

template <typename T>
void ALGraph<T>::create(const string &vertex_filename, const string &arc_filename, GraphKind k) {
    kind = k;
    ifstream fp;
    fp.open(vertex_filename, ios::in);
    while (fp.peek() != EOF) {
        T temp;
        fp >> temp;
        vertex.push_back(new VexNode<T>(temp));
        vex_num++;
    }
    fp.close();
    fp.open(arc_filename, ios::in);
    while(fp.peek() != EOF) {
        T tail, head;
        int tail_index, head_index;

        fp >> tail >> head;
        tail_index = locateVex(tail);
        head_index = locateVex(head);
        if (tail_index == -1 || head_index == -1) {
            return;
        }

        if (kind == UDG) {
            auto* temp1 = new ArcNode(head_index);
            auto* temp2 = new ArcNode(tail_index);

            temp1->next = vertex[tail_index]->first_arc->next;
            vertex[tail_index]->first_arc->next = temp1;

            temp2->next = vertex[head_index]->first_arc->next;
            vertex[head_index]->first_arc->next = temp2;


        } else if (kind == DG) {
            auto* temp1 = new ArcNode(head_index);
            temp1->next = vertex[tail_index]->first_arc->next;
            vertex[tail_index]->first_arc->next = temp1;
        }
        else if(kind == UDN) {
            int weight;
            fp >> weight;

            auto* temp1 = new ArcNode(head_index, weight);
            auto* temp2 = new ArcNode(tail_index, weight);

            temp1->next = vertex[tail_index]->first_arc->next;
            vertex[tail_index]->first_arc->next = temp1;

            temp2->next = vertex[head_index]->first_arc->next;
            vertex[head_index]->first_arc->next = temp2;
        }
        else if(kind == DN) {
            int weight;
            fp >> weight;
            auto* temp1 = new ArcNode(head_index, weight);
            temp1->next = vertex[tail_index]->first_arc->next;
            vertex[tail_index]->first_arc->next = temp1;
        }
        arc_num++;
    }
    fp.close();
}

template <typename T>
void ALGraph<T>::displayList() {
	cout << "Adjacent List table of vertex:" << endl;
    for(int i = 0; i < vex_num; i++) {
        cout << "Adjacent List of vertex " << vertex[i]->data << ": ";
        if(vertex[i]->first_arc->next == nullptr)
            cout << "null" << endl;
        ArcNode* pNode = vertex[i]->first_arc->next;
        while(pNode) {
            cout << vertex[pNode->index]->data;
            if(pNode->next != nullptr) cout << "--";
            else {
                cout << endl;
                break;
            }
            pNode = pNode->next;
        }
    }
}

template <typename T>
ALGraph<T>::~ALGraph() {
    for(int i = 0; i < vex_num; i++) {
        destroyList(vertex[i]->first_arc);
    }
}

#endif //DS_3_GRAPH_GRAPH_H

#include <iostream>
//#include "AdjMatrix.h"
#include "AdjList.h"

int main() {
    return 0;
}

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

//
// Created by Only Blue on 2020/6/10.
//

#ifndef DS_3_GRAPH_UNIONFIND_H
#define DS_3_GRAPH_UNIONFIND_H
#include <vector>

class UnionFind {
private:
	std::vector<int> id;
	std::vector<int> size;
	int count; // the amount of connected component
public:
	// constructor
	explicit UnionFind(int N);

	// return count;
	int getCount() const { return count; }

	// search for id, Makes the tree flatter
	int find(int p);

	// weighted Quick-Union
	void Union(int p, int q);

	// connection
	bool connected(int arg1, int arg2);
};

UnionFind::UnionFind(int N) {
    count = N;
    id.resize(N);
    size.resize(N);
    for (int i = 0; i < N; i++) {
        id[i] = i;
        size[i] = i;
    }
}

int UnionFind::find(int p) {
    while(p != id[p]) {
        id[p] = id[id[p]];
        p = id[p];
    }
    return p;
}

void UnionFind::Union(int p, int q) {
	int pID = find(p);
	int qID = find(q);

	if (pID == qID) // in the same group
		return;

	else {        // in different group
		if (size[pID] < size[qID]) {
			id[pID] = qID;
			size[qID] += size[pID];
		} else {
			id[qID] = pID;
			size[pID] += size[qID];
		}
		count--;
	}
}

bool UnionFind::connected(int arg1, int arg2) {
    return find(arg1) == find(arg2);
}

#endif //DS_3_GRAPH_UNIONFIND_H
