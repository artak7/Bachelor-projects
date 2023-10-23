#include <iostream>
#include <fstream>
using namespace std;

const int N = 1e6;
int a[N], b[N];
void mergesort(int l, int r)
{
	if (l >= r)
		return;
	int x = (l + r) / 2;
	if (x != l)
		mergesort(l, x);
	if (x != r)
		mergesort(x, r);
	int i = l, j = x, m = l;
	while (i < x && j < r)
	{
		if (a[i] < a[j])
			b[m] = a[i++];
		else
			b[m] = a[j++];
		m++;
	}
	while (i < x)
		b[m++] = a[i++];
	while (j < r)
		b[m++] = a[j++];
}

int main()
{
	ifstream cin("input.txt");
    ofstream cout("output.txt");
	int n;
	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> a[i];
	mergesort(0, n - 1);

	for (int i = 0; i < n; i++)
		cout << a[i] << " ";

	cout << endl;
	for (int i = 0; i < n; i++)
		cout << b[i] << " ";
	//system("pause");
	return 0;
}
