// Artak 5.1
#include <bits/stdc++.h>
using namespace std;

const int N = 1e5;
bool u[N];
int p[N];
queue <int> q;

void bfs(int s)
{
	q.push(s);
	u[s] = true;
	p[s] = -1;
	while (!q.empty())
	{
		int v = q.front(); q.pop();
		if (v < 9000)
		{
			int to = v+1000;
			if (!u[to])
			{
				u[to] = true;
				q.push(to);
				p[to] = v;
			}
		}

		if (v % 10 > 1)
		{
			int to = v-1;
			if (!u[to])
			{
				u[to] = true;
				q.push(to);
				p[to] = v;
			}
		}

		int to = (v % 10) * 1000 + v / 10;
		if (!u[to])
		{
			u[to] = true;
			q.push(to);
			p[to] = v;
		}
		
		to = v / 1000 + v % 1000 * 10;
		if (!u[to])
		{
			u[to] = true;
			q.push(to);
			p[to] = v;
		}
	}
}

int main()
{
	//ifstream cin("input.txt");
	//ofstream cout("output.txt");

	int s, f;
	cin >> s >> f;
	bfs(s);
	vector <int> ans;
	if (u[f])
	{
		for (int v = f; v != -1; v = p[v])
			 ans.push_back(v);
	}

	reverse(ans.begin(), ans.end());
	for (auto v : ans)
		cout << v << endl;

	//cerr << endl;
	return 0;
}