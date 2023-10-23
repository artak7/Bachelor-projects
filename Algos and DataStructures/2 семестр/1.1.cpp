#include <bits/stdc++.h>
using namespace std;

const int N = 100;

int main()
{
	//ifstream cin('input.txt');
	//ofstream cout('output.txt');

	int n;
	cin >> n;
	vector <vector <int> > g(n);
	for (int i = 0; i < n; i++)
	{
		int in, out;
		cin >> in >> out;
		g[--in].push_back(--out);
		g[out].push_back(in);
	}

	for (int i = 0; i < n; i++)
	{ 
		cout << "from " << i + 1 << ": " << endl;
		for (int j = 0; j < g[i].size(); j++)
			cout << g[i][j] + 1 << " "; 
		
		cout << endl;
	}

	return 0;
}