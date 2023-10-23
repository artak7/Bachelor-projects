#include <bits/stdc++.h>
using namespace std;

const int AIM = 2, N = 3;
//in common case its backtracking
//const int volume[N] = {10, 7, 4};

struct tripple
{
	int bank10, bank7, bank4;
	tripple() {}
	tripple(int a, int b, int c) 
	{
		bank10 = a;
		bank7 = b;
		bank4 = c;	
	}

	/*bool operator<(tripple b)
	{
		return bank10 < b.bank10 || bank10 == b.bank10 && bank7 < b.bank7 || bank10 == b.bank10 && bank7 == b.bank7 && bank4 < b.bank4;
	}*/
};

//map <tripple, bool> u;
int u[12][12][12], depth_ans;
tripple ans;
//return path only if bfs realized
vector <vector <tripple> > tree;

bool dfs(tripple v, int depth)
{
	// push_back по уровню глубины надо сделать 
	//cout << "(" << v.bank10 << ", " << v.bank7 << ", " <<v.bank4 << ")" << endl;
	tree[depth].push_back(v);
	u[v.bank10][v.bank7][v.bank4] = true;
	if (v.bank7 == AIM || v.bank4 == AIM)
	{
		ans = v;
		depth_ans = depth;
		return true;
	}

	tripple to(v);
	int tmp;
	if (v.bank10 < 10)
	{
		tmp = to.bank10 + v.bank7;
		to.bank10 = min(10, tmp);
		to.bank7 = max(0, tmp - 10);
		if (!u[to.bank10][to.bank7][to.bank4])
			if (dfs(to, depth+1)) return true;

		to = v;
		tmp = to.bank10 + v.bank4;
		to.bank10 = min(10, tmp);
		to.bank4 = max(0, tmp - 10);
		if (!u[to.bank10][to.bank7][to.bank4])
			if (dfs(to, depth+1)) return true;
	} 
	
	if (v.bank7 < 7) 
	{
		to = v;
		tmp = to.bank7 + v.bank10;
		to.bank7 = min(7, tmp);
		to.bank10 = max(0, tmp - 7);
		if (!u[to.bank10][to.bank7][to.bank4])
			if (dfs(to, depth+1)) return true;

		to = v;
		tmp = to.bank7 + v.bank4;
		to.bank7 = min(7, tmp);
		to.bank4 = max(0, tmp - 7);
		if (!u[to.bank10][to.bank7][to.bank4])
			if (dfs(to, depth+1)) return true;

	} 
	
	if (v.bank4 < 4)
	{
		to = v;
		tmp = to.bank4 + v.bank7;
		to.bank4 = min(4, tmp);
		to.bank7 = max(0, tmp - 4);
		if (!u[to.bank10][to.bank7][to.bank4])
			if (dfs(to, depth+1)) return true;

		to = v;
		tmp = to.bank4 + v.bank10;
		to.bank4 = min(4, tmp);
		to.bank10 = max(0, tmp - 4);
		if (!u[to.bank10][to.bank7][to.bank4])
			if (dfs(to, depth+1)) return true;
	}
		
	return false;
}

int main()
{
	//ifstream cin("input.txt");
	//ofstream cout("output.txt");

	// for shortest path use bfs

	tree.resize(30); //MAX DEPTH
	if (dfs(tripple(0, 7, 4), 0))
	{
		cout << "YES" << endl << depth_ans << " (" << ans.bank10 << ", " << ans.bank7 << ", " << ans.bank4 << ")" << endl;
		//return 0;
	} 
	else
		cout << "NO";

	for (int i = 0; i < 30; i++)
	{
		cout << "depth: " << i << endl;
		if (tree[i].size())
			cout << endl;
		for (int j = 0; j < tree[i].size(); j++)
			cout << "(" << tree[i][j].bank10 << "," << tree[i][j].bank7 << "," << tree[i][j].bank4 << ") ";
	}

	return 0;
}