// Artak 6.3
#include <bits/stdc++.h>
using namespace std;

#define to first 
#define id first
#define len second
//#define mp make_pair
const int INF = 1e9;

int main()
{
	ifstream cin("input.txt");
	ofstream cout("output.txt");

	int n, m, s;
	cin >> n >> m >> s;
	vector <vector <pair <int, int> > > g(n);
	for (int i = 0; i < m; i++)
	{
		int x, y, l;
		cin >> x >> y >> l;
		g[--x].push_back({--y, l});
		//g[y].push_back({x, l});
	}

	vector <int> d(n, INF), p(n), u(n);
	d[--s] = 0;
	/*set <pair<int, int> > q;
	q.insert({s, d[s]});
	while (!q.empty()) 
	{
		int v = q.begin()->to;
		q.erase (q.begin());
 
		for (size_t j = 0; j < g[v].size(); j++) 
		{
			int to = g[v][j].to,
				len = g[v][j].len;
			if (d[v] + len < d[to]) 
			{
				q.erase({d[to], to});
				d[to] = d[v] + len;
				p[to] = v;
				q.insert({d[to], to});
			} 
			else if (d[v] + len == d[to])
				u[to] = true;
		}
	}*/

	for (int i = 0; i < n; i++) 
	{
		int v = -1;
		for (int j = 0; j < n; j++)
			if (!u[j] && (v == -1 || d[j] < d[v]))
				v = j;

		if (d[v] == INF) break;
		u[v] = true;
 
		for (size_t j = 0; j < g[v].size(); j++) 
		{
			int to = g[v][j].id,
				len = g[v][j].len;
			if (d[v] + len < d[to]) 
			{
				d[to] = d[v] + len;
				//p[to] = v;
			}
		}
	}

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			if (i != s && j != s && d[i] < INF && d[j] < INF)
				cout << i << " " << j << " = " << d[i] + d[j] << endl;

	//cerr << endl;
	return 0;
}