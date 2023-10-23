// Compiled with: g++ -Wall -std=c++14 -pthread

#include <iostream>
#include <ctime>
using namespace std;

const int N = 1e7;
int a[N];
void qs(int l, int r)
{
    while (l != r)
    {
        int x = a[l + rand() % (r - l + 1)];
        int i = l, j = r;
        while (i <= j)
        {
            while (a[i] < x) i++;
            while (a[j] > x) j--;

            if (i <= j)
            {
                swap(a[i], a[j]);
                i++; j--;
            }
        }

        if (j - l < r - i)
        {
            if (l < j)
                qs(l, j);
            l = i;
        }
        else
        {
            if (i < r)
                qs(i, r);
            r = j;
        }
    }
}
    
int main()
{
    int n; 
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> a[i];
    
    qs(0, n - 1);
    for (int i = 0; i < n; i++)
        cout << a[i] << " ";
    
    return 0;
}
