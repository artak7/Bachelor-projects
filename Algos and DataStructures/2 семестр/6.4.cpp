// Artak 6.4
#include <bits/stdc++.h>
using namespace std;

#define id first 
#define time second.first
#define weight second.second

//#define mp make_pair
const int INF = 1e9;
vector <vector <pair <int, pair<int, int> > > > g;
int n, m;

bool f(int w)
{
	vector <int> TL(n, INF), u(n);
	TL[0] = 0; 
	set <pair <int, int> > q;
	q.insert({0, TL[0]});
	while (!q.empty()) 
	{
		int v = q.begin()->id;
		q.erase(q.begin());
 
		for (size_t j = 0; j < g[v].size(); j++) 
		{
			int to = g[v][j].id,
				toTL = g[v][j].time,
				toWL = g[v][j].weight; 
			if (TL[v] + toTL < TL[to] && w <= toWL)
			{
				q.erase({to, TL[to]});
				TL[to] = TL[v] + toTL;
				q.insert({to, TL[to]});
			} 
			else if (TL[v] + toTL == TL[to])
				u[to] = true;
		}
	}

	return (TL[n - 1] <= 1440);
}

int main()
{
	ifstream cin("input.txt");
	ofstream cout("output.txt");

	cin >> n >> m;
	if (n == 1 && m == 0)
	{
		cout << 10000000;
		return 0;
	}

	g.resize(n);
	for (int i = 0; i < m; i++)
	{
		int x, y, t, w;
		cin >> x >> y >> t >> w;
		w = (w - 3000000) / 100;
		g[--x].push_back({--y, {t, w}});
		g[y].push_back({x, {t, w}});
	}

	int l = 0, r = 1e7;
	while (l < r)
	{
		//cerr << l << " " << r << endl;
		int x = (l+r) / 2;
		if (f(x) && l != x)
			l = x;
		else if (r != x)
			r = x;
		else
			l = x;
	}

	cout << l;
	//cerr << WL[f] << endl;
	return 0;
}