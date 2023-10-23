#include <bits/stdc++.h>
using namespace std;

int g[101][101], u[101], n;

void dfs(int v)
{
	u[v] = true;
	for (int i = 0; i < n; i++)
		if (!u[i] && g[v][i])
			dfs(i);
}

int main()
{
	//ifstream cin("input.txt");
	//ofstream cout("output.txt");

	int cnt = 0;
	cin >> n;
	u[0] = true;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
		{
			cin >> g[i][j];
			cnt += g[i][j];
		}

	dfs(0);
	for (int i = 1; i < n; i++)
		if (!u[i])
		{
			cout << "NO";
			return 0;
		} 

	if (n - 1 == cnt / 2)
		cout << "YES";
	else
		cout << "NO";

	return 0;
}