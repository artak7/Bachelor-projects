#include <bits/stdc++.h>
using namespace std;
const int N = 1e4;

int a[N];

int main()
{
    ifstream cin("input.txt");
    ofstream cout("output.txt");

    int n, x; 
    cin >> n >> x;
    for (int i = 0; i < n; i++)
        cin >> a[i];

    int l = 0, r = n - 1, mid;
    while (r - l > 1)
    {
        mid = (l+r) >> 1;
        if (a[mid] < x)
            l = mid;
        else 
            r = mid;
    }

    cout << l;
    return 0;
}