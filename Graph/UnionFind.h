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
