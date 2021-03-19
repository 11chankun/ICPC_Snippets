#include <bits/stdc++.h>
using namespace std;

class Articulation {
	int n; // number of nodes
	vector<int> *adj; // adjacency list of graph

	vector<bool> visited;
	vector<int> tin, low, cutpoints;
	int timer;

	Articulation(vector<int> *g, int tn) {
		adj = g, n = tn;
	}

	void IS_CUTPOINT(int v) {
		cutpoints.push_back(v);
	}

	void dfs(int v, int p = -1) {
		visited[v] = true;
		tin[v] = low[v] = timer++;
		int children=0;
		for (int to : adj[v]) {
			if (to == p) continue;
			if (visited[to]) {
				low[v] = min(low[v], tin[to]);
			} else {
				dfs(to, v);
				low[v] = min(low[v], low[to]);
				if (low[to] >= tin[v] && p!=-1)
					IS_CUTPOINT(v);
				++children;
			}
		}
		if(p == -1 && children > 1)
			IS_CUTPOINT(v);
	}

	vector<int> find_cutpoints() {
		timer = 0;
		visited.assign(n, false);
		tin.assign(n, -1);
		low.assign(n, -1);
		for (int i = 0; i < n; ++i) {
			if (!visited[i])
				dfs (i);
		}
		return cutpoints;
	}
};
