// Artak 5.3
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
	set <pair<int, int> > q;
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
				q.erase({to, d[to]});
				d[to] = d[v] + len;
				p[to] = v;
				q.insert({to, d[to]});
			} 
			else if (d[v] + len == d[to])
				u[to] = true;
		}
	}

	for (int i = 0; i < n; i++)
		if (!u[i])
			cout << i+1 << " ";

	//cerr << endl;
	return 0;
}