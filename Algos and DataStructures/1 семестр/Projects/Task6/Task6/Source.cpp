#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <algorithm>

using namespace std;

int binarySearch(int x[], int searchValue, int left, int right)
{
	if (right < left)
	{
		return -1;
	}
	int mid = (left + right) >> 1;
	if (searchValue > x[mid])
	{
		return binarySearch(x, searchValue, mid + 1, right);
	}
	else if (searchValue < x[mid])
	{
		return binarySearch(x, searchValue, left, mid - 1);
	}
	else
	{
		return mid;
	}
}


int FibonachySearch(int array[], int x, int n)
{
	int fn_2 = 1;
	int fn_1 = 1;
	int fn = fn_2 + fn_1;

	while (fn < n)
	{
		fn_2 = fn_1;
		fn_1 = fn;
		fn = fn_2 + fn_1;
	}

	int sdvig = -1;

	while (fn > 1)
	{
		int i = min(sdvig + fn_2, n - 1);
		if (array[i] < x)
		{
			fn = fn_1;
			fn_1 = fn_2;
			fn_2 = fn - fn_1;
			sdvig = i;
		}
		else if (array[i] > x)
		{
			fn = fn_2;
			fn_1 = fn_1 - fn_2;
			fn_2 = fn - fn_1;
		}
		else return i;
	}
	if (fn_1 && array[sdvig + 1] == x)return sdvig + 1;
	return -1;
}

int Finger_search(int mass[], int x, int n)
{
	int val = 0;
	int index = 0;
	int left_border = 0;
	while (mass[left_border] <= mass[index] && left_border<n - 1)
	{
		index = min(left_border + val, n - 1);
		if (x > mass[index])
		{
			left_border = index;
			if (val == 0)
				val = 2;
			else
				val *= 2;
		}
		else if (x < mass[index])
		{
			val = 0;
			left_border += 1;
		}
		else
			return index;
	}
	return -1;
}


int searchLastNull(int x[], int left, int right)
{
	if (right < left)
	{
		return -1;
	}
	int mid = (left + right) >> 1;
	if (x[mid] == 0)
	{
		return searchLastNull(x,  mid + 1, right);
	}
	else if (x[mid] == 1 && x[mid-1]==0)
	{
		return mid;
		
	}
	else
	{
		return searchLastNull(x, left, mid - 1);
	}
}

int main()
{

	//Задача 1
	int array[10] = { -9, -5, -3, -2, 0, 1, 3, 18, 32, 101 };
	for (int i = 0; i < 10; i++)
	{
		cout << array[i] << " "; 
	}
	int	search_value = 15;
	int result = binarySearch(array, search_value, 0, 9);
	if (result == -1)
		cout << "\nЗначение не найдено" << endl;
	else
		cout << "\nЗначение находится под индексом " << result << endl;

	//Задача 2
	cout<<"\nFound at index: "<< FibonachySearch(array, search_value, 10);

	//Задача 3

	cout<< "Found at index: "<< Finger_search(array, search_value, 10);


	//Задача 4

	int array2[10] = { 0, 0, 0, 0, 0, 0, 1, 1, 1, 1 };
	for (int i = 0; i < 10; i++)
	{
		cout << array2[i] << " ";
	}
	result = searchLastNull(array2, 0, 9);
	if (result == -1)
		cout << "\nЗначение не найдено" << endl;
	else
		cout << "\nЗначение находится под индексом " << result << endl;

	system("pause");
	return 0;
}