#include <bits/stdc++.h>
using namespace std;
const int N = 1e4;

int a[N], f[N];
int main()
{
    ifstream cin("input.txt");
    ofstream cout("output.txt");
    int n; 
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> a[i];

    f[0] = 0; f[1] = 1;
    int i = 1;
    while(f[i] <= n)
    {
        i++;
        f[i] = f[i - 1] + f[i - 2];
    }


    while (r - l > 1)
    {
        mid2 = f[i - 1];
        mid1 = f[i - 2];
        if (a[mid1] < x)
            l = mid1;
        else if (a[mid2] > x)
            r = mid2;
        i-=2;
    }

    
    cout << sum;
    return 0;
}