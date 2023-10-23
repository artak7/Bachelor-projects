// Artak 3.2
#include <bits/stdc++.h>
using namespace std;

vector <vector <int> > g;
vector <bool> u;

int dfs(int v, int d)
{
	u[v] = true; 
	int maxx = d;
	for (int i = 0; i < g[v].size(); i++)
	{
		int to = g[v][i];
		if (!u[to])
			maxx = max(maxx, dfs(to, d+1));
	}

	return maxx;
}

int main()
{
	ifstream cin("input.txt");
	ofstream cout("output.txt");

	int n, m, ans = 0;
	cin >> n >> m;

	g.resize(n);
	u.resize(n);
	for (int i = 0; i < m; i++)
	{
		int a, b;
		cin >> a >> b;
		g[--a].push_back(--b);
		//g[b].push_back(a);
	}

	for (int i = 0; i < n; i++)
		if (!u[i])
			ans = max(ans, dfs(i, 1));
			
	cout << ans << endl;
	return 0;
}