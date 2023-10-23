#include <bits/stdc++.h>
using namespace std;

const int N = 1e6
int a[N];

void swap_blocks(int j1, int j2, int size)
{
    for (int i = 0; i < size; i++)
        swap(i + (j1-1) * size + 1, i + (j2-1) * size + 1); //bad
}

void sqsort(int size, int block_size)
{
    for (int i = 1; i < size; i++)
    {
        min = i;
        for (int j = i + 1; j <= size; j++)
            if (a[j*block_size] < a[min*block_size] || 
                a[j*block_size] == a[min*block_size] && a[(j+1)*block_size-1] < a[(min+1)*block_size-1])
                min = j;

        swap_blocks(min, i);
    }
}

void merge_blocks(int block1, int block2, int size, int block_size)
{
    swap_blocks(block1, size);
    int i = 0; 
    int j = 0;
    int k = 0;
    while (i < block_size && j < block_size)
    {
        if (a[i + (block2-1) * block_size + 1] < a[j + (size-1) * block_size + 1])
        {
            swap(a[k], a[i + (block2-1) * block_size + 1]);
            i++;
        }
        else
        {
            swap(a[k], a[j + (size-1) * block_size + 1]);
            j++;
        }

        k++;
    }
}

void merge_sort(int l, int r)
{
    int mid = (l + r) / 2;
	int len = sqrt(n);
	int cnt = n / len;
    int last1 = mid / cnt + mid % cnt;
    swap_blocks(last1, cnt, cnt); //1 indexing blocks //bad
    sqsort(cnt, len);
    for (int i = 0; i < cnt; i++)
        merge_blocks(i+1, i+2, cnt, len);

    int s = n % len + cnt;
    for (int i = 0; i < 2*s-1; i++)
    {
        min = i;
        for (int j = i + 1; j < 2*s; j++)
            if (a[j+size*(block_size-1)+1] < a[min+size*(block_size-1)+1])
                min = j;
    }
}

int main()
{
	ifstream cin("input.txt");
    ofstream cout("output.txt");
    int n; 
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> a[i];

    cout << "not yet";
    return 0;
}