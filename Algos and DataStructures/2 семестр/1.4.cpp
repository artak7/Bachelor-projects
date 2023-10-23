// Artak 1.4
#include <bits/stdc++.h>
using namespace std;

vector <vector <int> > g, s;
vector <int> u;

/*
int dfs(int v)
{
	u[v] = true;
	for (int i = 0; i < g[v].size(); i++)
	{
		int to = g[v][i];
		s[to].push_back(v);
		if (!u[to])
			dfs(to);
	}
}*/

int main()
{
	ifstream cin("input.txt");
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
		//g[b].push_back(a);
	}

	/*for (int i = 0; i < n; i++)
		if (!u[i])
			dfs(i);
	*/

	for (int i = 0; i < n; i++)
		for (int j = 0; j < g[i].size(); j++)
			{
				int to = g[i][j];
				s[to].push_back(i);
			}

	for (int i = 0; i < n; i++)
	{
		cout << "from " << i+1 << ": " << endl;
		for (int j = 0; j < s[i].size(); j++)
			cout << s[i][j] + 1 << " ";

		cout << endl;
	}
	
	return 0;
}