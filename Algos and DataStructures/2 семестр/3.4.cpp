// Artak 3.4

// для ациклических графов dfs можно без used
// для общего случая dfs с used и массивом степеней вершин
#include <bits/stdc++.h>
using namespace std;

vector <vector <int> > g;
vector <int> u, cost, s; //, time_in, time_out;
//int dfs_timer = 0;

void dfs(int v)
{
	//time_in[v] = dfs_timer++;
	u[v] = true;
	s[v]--;
	for (int i = 0; i < g[v].size(); i++)
	{
		int to = g[v][i];
		if (s[to] && !u[to])
		{
			dfs(to);
			cost[v] = min(cost[v], cost[to]);	
		}
	}

	for (int i = 0; i < g[v].size(); i++)
	{
		int to = g[v][i];
		if (s[to] && u[to])
		{
			dfs(to);
			cost[v] = min(cost[v], cost[to]);	
		}
	}

	//time_out[v] = dfs_timer++;
}

int main()
{
	ifstream cin("input.txt");
	ofstream cout("output.txt");

	int n, m;
	cin >> n >> m;

	g.resize(n);
	u.resize(n);
	cost.resize(n);
	s.resize(n, 1);

	for (int i = 0; i < m; i++)
	{
		int a, b;
		cin >> a >> b;
		g[--a].push_back(--b);
		s[b]++;
		//g[b].push_back(a);
	}

	for (int i = 0; i < n; i++)
	{
		int price;
		cin >> price;
		cost[i] = price;
	}

	for (int i = 0; i < n; i++)
		cerr << s[i] << " ";

	for (int i = 0; i < n; i++)
		if (!u[i])
			dfs(i);

	for (int i = 0; i < n; i++)
		cout << cost[i] << " ";
	
	cerr << endl;
	return 0;
}