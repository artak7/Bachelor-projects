#include <bits/stdc++.h>
using namespace std;
 
int n, m, i, j, h, t, v, k;
bool ok = true;
 
main()
{
    ifstream cin("input.txt");//
    ofstream cout("output.txt");//
 
    cin >> n >> m;
    vector < vector <int> > g(n);
    vector <int> p(n, -1), q(n);
 
    for (; i < m; i++)
    {
        cin >> h >> t;
        g[--h].push_back(--t);
        g[t].push_back(h);
    }
 
    for (i = 0; i < n; i++)
        if (p[i] == -1)
        {
            h = t = 0;
            q[t++] = i;
            p[i] = 0;
            while (h < t)
            {
                v = q[h++];
                for (j = 0; j < g[v].size(); j++)
                {
                    k = g[v][j];
                    if (p[k] == -1)
                    {
                        q[t++] = k;
                        p[k] = !p[v];
                    } 
                    else
                        ok &= p[k] != p[v];
                }
            }
        }
 
    cout << (ok ? "YES" : "NO");
}