// Artak 3.1
#include <bits/stdc++.h>
using namespace std;

vector <vector <int> > g;
vector <int> u, s, time_in, time_out, v;
//int dfs_timer = 0;

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
	u.resize(n);
	s.resize(n);
	
	for (int i = 0; i < m; i++)
	{
		int a, b;
		cin >> a >> b;
		g[--a].push_back(--b);
		s[b]++;
		//g[b].push_back(a);
	}

	queue <int> q;

	for (int i = 0; i < n; i++)
		if (!s[i]) {
			q.push(i);
			s[i]--;
		}

	while (!q.empty())
	{
		int i = q.front(); q.pop();
		v.push_back(i);
		for (int j = 0; j < g[i].size(); j++)
		{
			int to = g[i][j];
			if (s[to] > -1) s[to]--;
			if (s[to] == 0)
				q.push(to);
			
		}
	}

	for (int i = 0; i < n; i++)
	{
		cout << v[i]+1 << " ";
	}
	
	return 0;
}