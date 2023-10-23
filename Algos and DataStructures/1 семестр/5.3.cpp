// Compiled with: g++ -Wall -std=c++14 -pthread

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    int s, n, k = 0; 
    cin >> n >> s;
    vector <int> v(n);
    for (int i = 0; i < n; i++)
        cin >> v[i];

    sort(v.begin(), v.end());
    int i = 0, j = n - 1;   
    while (i < j)
    {
    	if (v[i] + v[j] > s)
	    	j--;
		else if (v[i] + v[j] < s)
	    	i++;
		else 
		{
		    k++;
		    i++;
		    j--;
		}
    }

    cout << k << endl;
    return 0;
}
