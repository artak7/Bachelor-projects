// Artak 4
#include <bits/stdc++.h>
using namespace std;

vector <vector <int> > g;
vector <bool> u, c;
vector <int> time_in, fup; // time_out;
int dfs_timer = 0;

void dfs(int v, int p = -1)
{
	time_in[v] = fup[v] = dfs_timer++;
	u[v] = true;
	int children = 0;
	for (int i = 0; i < g[v].size(); i++)
	{
		int to = g[v][i];
		if (to != p)
		{
			if (!u[to])
			{
				dfs(to, v);
				fup[v] = min(fup[v], fup[to]);
				if (fup[to] >= time_in[v] && p != -1)
					c[v] = true;
				children++;
			} 
			else
			{
				fup[v] = min(fup[v], time_in[to]);
			}

		}
	}

	if (p == -1 && children > 1)
		c[v] = true;

	//time_out[v] = dfs_timer++;
}

//vector <int> p; вместо p используется fup для экономии памяти
queue <int> q;
void bfs(int s)
{
	q.push(s);
	u[s] = true;
	fup[s] = -1;
	while (!q.empty())
	{
		int v = q.front(); q.pop();
		for (auto to : g[v])
			if (!u[to])
			{
				u[to] = true;
				q.push(to);
				fup[to] = v;
			}
	}
}

int main()
{
	//ifstream cin("input.txt");
	//ofstream cout("output.txt");

	int n, m;
	cin >> n >> m;

	g.resize(n);
	u.resize(n);
	c.resize(n);
	time_in.resize(n);
	fup.resize(n);

	for (int i = 0; i < m; i++)
	{
		int x, y;
		cin >> x >> y;
		g[--x].push_back(--y);
		g[y].push_back(x);
	}

	for (int i = 0; i < n; i++)
		if (!u[i])
			dfs(i);

	//for (int i = 0; i < n; i++)
	//	cerr << c[i] << " ";

	int q, a, b, ans;
	cin >> q;
	//fup.clear();
	for (int i = 0; i < q; i++)
	{
		cin >> a >> b; 
		--a;--b;
		ans = 0;
		u.assign(n, false);
		fup.assign(n, 0);
		bfs(a);
		if (u[b])
		{
			for (int v = fup[b]; v != a; v = fup[v])
				 ans += c[v];
		}

		cout << ans << endl;
	}

	//cerr << endl;
	return 0;
}