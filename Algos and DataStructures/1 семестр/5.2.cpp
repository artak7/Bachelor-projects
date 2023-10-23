//#include <iostream>
//#include <vector>
//#include <algorithm>
#include <bits/stdc++.h>
using namespace std;
const int N = 1e7;

int main()
{
    ifstream cin("input.txt");
    ofstream cout("output.txt");
    int n; 
    cin >> n;
    vector <int> t(n);
    for (int i = 0; i < n; i++)
        cin >> t[i];
    
    sort(t.begin(), t.end());
    int sum = 0;
    for (int i = 0; i < n - 1; i++)
        sum += t[i] * (n - 1 - i);
    
    cout << sum;
    return 0;
}