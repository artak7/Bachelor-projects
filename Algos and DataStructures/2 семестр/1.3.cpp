// Artak 1.3
#include <bits/stdc++.h>
using namespace std;

vector <vector <pair<int, int> > > g;
vector <int> x, ans;

/*
void dfs(int v)
{
	time_in[v] = dfs_timer++;
	u[v] = true;
	for (int i = 0; i < g[v].size(); i++)
	{
		int to = g[v][i];
		st[to].val++;
		if (!u[to])
			dfs(to);
	}

	time_out[v] = dfs_timer++;
}
*/

int main()
{
	//ifstream cin("input.txt");
	//ofstream cout("output.txt");

	int n, m;
	cin >> n >> m;

	g.resize(n);
	x.resize(n);
	ans.resize(n);
	
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
		{
			cin >> a;
			if (a) g[i].push_back(make_pair(a, j));

			//if (a) g[j].push_back(make_pair(a, i));
		}

	for (int i = 0; i < n; i++)
		cin >> x[i];

	for (int i = 0; i < n; i++)
	{	
		for (int j = 0; j < g[i].size(); j++)
			ans[i] += g[i][j].first * x[g[i][j].second];
	}

	for (int i = 0; i < n; i++)
	{
		cout << ans[i] << " ";
	}
	
	return 0;
}