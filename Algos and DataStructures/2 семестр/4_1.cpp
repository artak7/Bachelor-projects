// Artak 4
#include <bits/stdc++.h>
using namespace std;

vector <vector <int> > g, jps;
vector <bool> u1;
vector <int> u, time_in, fup; // time_out;
int dfs_timer = 0, cc = 1, jp = 0;  // connectivity components, junction points

void dfs(int v, int p = -1)
{
	time_in[v] = fup[v] = dfs_timer++;
	u[v] = cc;
	int children = 0;
	for (int i = 0; i < g[v].size(); i++)
	{
		int to = g[v][i];
		if (to != p)
		{
			if (u[to] == 0)
			{
				dfs(to, v);
				fup[v] = min(fup[v], fup[to]);
				if (fup[to] >= time_in[v] && p != -1)
				{
					if (u[v] >= 0) 
					{
						jp++;				
						u[v] = -jp; // junction point
						jps[jp].push_back(cc);
						jps[jp].push_back(cc+1);
						cc++;
					} 
					else 
					{
						cc++;
						jps[jp].push_back(cc);
					}
				}

				children++;
				if (p == -1 && children > 1) 
				{
					//jps[jp].push_back(cc);
					cc++;
				}
			} 
			else if (u[to] < 0)
			{
				jps[jp].push_back(cc);
				fup[v] = min(fup[v], time_in[to]);
			}
			else
			{
				fup[v] = min(fup[v], time_in[to]);
			}

		}
	}

	if (p == -1 && children > 1)
	{
		jp++;
		u[v] = -jp; // junction point
		for (int i = children - 1; i >= 0; i--)
			jps[jp].push_back(cc-i);
	}

	//time_out[v] = dfs_timer++;
}

//vector <int> p; вместо p используется fup для экономии памяти
queue <int> q;
void bfs(int s)
{
	q.push(s);
	u1[s] = true;
	fup[s] = -1;
	while (!q.empty())
	{
		int v = q.front(); q.pop();
		for (auto to : g[v])
			if (!u1[to])
			{
				u1[to] = true;
				q.push(to);
				fup[to] = v;
			}
	}
}

int main()
{
	ifstream cin("input.txt");
	ofstream cout("output.txt");

	int n, m;
	cin >> n >> m;

	g.resize(n);
	u.resize(n);
	u1.resize(n);
	jps.resize(n+1);
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

	for (int i = 0; i < n; i++)//
		cerr << u[i] << " ";//

	cerr << endl;//

	for (int i = 0; i <= n; i++)
	{
		if (jps[i].size())
		{
			cerr << i << ": ";
		
			for (int j = 0; j < jps[i].size(); j++)
				cerr << jps[i][j] << " ";

			cerr << endl;
		}
	}

	int q, a, b, ans;
	cin >> q;
	//fup.clear();
	for (int i = 0; i < q; i++)
	{
		cin >> a >> b; 
		--a;--b;
		ans = 0;
		bool ok = true;
		if (u[a] < 0 && u[b] < 0)
		{
			for (int i = 0; i < jps[-u[a]].size() && ok; i++)
				for (int j = 0; j < jps[-u[b]].size() && ok; j++)
					if (jps[-u[a]][i] == jps[-u[b]][j])
						ok = false;					
		} 
		else if (u[a] < 0 && u[b] >= 0)
		{
			for (int i = 0; i < jps[-u[a]].size() && ok; i++)
				if (jps[-u[a]][i] == u[b])
						ok = false;				
		}
		else if (u[a] >= 0 && u[b] < 0)
		{
			for (int i = 0; i < jps[-u[b]].size() && ok; i++)
				if (jps[-u[b]][i] == u[a])
						ok = false;	
		}
		else if (u[a] == u[b])
		{	
			ok = false;
		}

		if (ok)
		{
			u1.assign(n, false);
			fup.assign(n, 0);
			bfs(a);
			if (u1[b] > 0)
			{
				for (int v = fup[b]; v != a; v = fup[v])
					 ans += (u[v] < 0);
			}
		}

		cout << ans << endl;
	}

	//cerr << endl;
	return 0;
}

/*
7 10
1 2
2 3
3 1
1 4
4 5
5 1
1 7
7 6
6 1
5 6
3
2 3
3 4
6 4
*/