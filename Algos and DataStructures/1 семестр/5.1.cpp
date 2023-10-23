// Compiled with: g++ -Wall -std=c++14 -pthread

#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

const int N = 1e7;
#define date first
#define go second

/*#define l first
#define r second*/
#define pii pair <int, int>

/*bool cmp(pii a, pii b)
{
    return a.l < b.l || a.l == b.l && a.r < b.r;
}*/

int main()
{
    int n, k; 
    cin >> n >> k;
    vector <pii> a(n);
    for (int i = 0; i < 2*n; i++)
    {
        cin >> a[i].date;
        if (i % 2) a[i].go = 1;
    }
    
    sort(a.begin(), a.end());
    int b = 0, maxx = 0;
    for (int i = 0; i < 2*n; i++)
    {
        //cout << a[i].l << " " << a[i].r << endl;
        if (a[i].go == 0)
            b++;
        else
            b--;
        
        if (b > maxx) maxx = b;
    }
    
    if (maxx <= k) 
        cout << "OK"; 
    else 
        cout << "You need " << maxx - k << " rooms";
    
    return 0;
}
