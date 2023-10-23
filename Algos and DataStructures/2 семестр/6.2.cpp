// Artak 6.2
#include <bits/stdc++.h>
using namespace std;

const int N = 1e4;
const int INF = 1e9;

int d[N][N];

int main()
{
	ifstream cin("input.txt");
	ofstream cout("output.txt");

	int n, m;
	cin >> n >> m;

	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			d[i][j] = INF;

	for (int i = 0; i < m; i++)
	{
		int x, y, l;
		cin >> x >> y >> l;
		d[x][y] = l;
		//d[y][x] = l;
	}

	int m = 0;
	for (int k = 0; k <= n; k++)
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				if (k < n)
				{
					if (d[i][k] < INF && d[k][j] < INF)
						d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
				}
				else
				{
					m = max(m, d[i][j]);
				}

	cout << m;
	//cerr << endl;
	return 0;	
}