#include <bits/stdc++.h>
using namespace std;

vector <vector <int> > g;
vector <int> u, ans;

bool dfs(int v, int color)
{
	u[v] = color;
	if (color == 1)
		ans.push_back(v);

	for (int i = 0; i < g[v].size(); i++)
	{
		int to = g[v][i];
		if (!u[to])
		{
			if (dfs(to, -color)) return true;
		}
		else 
		{
			if (color == u[to])
				return true;
		}
	}

	return false;
}

int main()
{
	ifstream cin("input.txt");
	//ofstream cout("output.txt");

	int n, m;
	cin >> n >> m;

	g.resize(n);
	u.resize(n);
	for (int i = 0; i < m; i++)
	{
		int a, b;
		cin >> a >> b;
		g[--a].push_back(--b);
		g[b].push_back(a);
	}

	for (int i = 0; i < n; i++)
		if (!u[i])
			if (dfs(i, 1))
			{
				cout << "NO";
				return 0;
			}

	cout << "YES" << endl;
	for (int i = 0; i < ans.size(); i++)
		cout << ans[i]+1 << " ";

	return 0;
}