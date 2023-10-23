#include <iostream>
#include <vector>
#include <stack>
#include <fstream>
using namespace std;

struct Node 
{
	int x; 
	Node *Next, *Prev;
};

class Massiv   
{
	
	Node *HeadList, *TailList, *HeadStack;
public:
	Massiv() :HeadList(NULL), TailList(NULL) {
		for (int i = 0; i < 3; i++) {
			Node *temp = new Node;
			temp->Prev = NULL;
			temp->Next = HeadStack;
			HeadStack = temp;
		}
	};
	~Massiv();
	void Show();
	void Add(int x, int el); 
	void Remove(int x);
	int Size();
	int Capacity();
private:
	void InsertInStack(Node *&el);
	Node *ExtractFromStack();
	void Reallocate(int x);
};

Massiv::~Massiv() //Деструктор
{
	while (HeadList)
	{
		TailList = HeadList->Next;
		delete HeadList;
		HeadList = TailList;
	}
}

void Massiv::Add(int x, int ind)
{
	if (Size() == Capacity()) {
		Reallocate(1);
	}
	Node *temp = ExtractFromStack();  
	temp->x = x;

	if (HeadList != NULL) 
	{
		int counter = 0;
		Node *el = HeadList;
		while (el != NULL) {
			if (counter == ind) {
				if (el == HeadList) {
					temp->Next = el;
					el->Prev = temp;
					HeadList = temp;
					return;
				}
				else {
						temp->Next = el;
						temp->Prev = el->Prev;
						el->Prev->Next = temp;
						el->Prev = temp;
						return;
				}
			}
			else {
				el = el->Next;
				counter++;
			}
		}
	}
	else 
	{
		temp->Prev = NULL;
		HeadList = TailList = temp;
	}
}

void Massiv::Remove(int x)
{
	if (Size() == (Capacity() / 4) - 1) {
		Reallocate(0);
	}
	if (HeadList != NULL)
	{
		int counter = 0;
		Node *el = HeadList;
		while (el != NULL) {
			if (el->x == x) {
				if (el == HeadList) {
					Node *temp = HeadList;
					HeadList = HeadList->Next;
					HeadList->Prev = NULL;
					InsertInStack(temp);
					return;
				}
				else {
					if (el == TailList) {
						Node *temp = TailList;
						TailList = TailList->Prev;
						TailList->Next = NULL;
						InsertInStack(temp);
						return;
					}
					else {
						Node *temp = el;
						el->Prev->Next = el->Next;
						el->Next->Prev = el->Prev;
						InsertInStack(temp);
						return;
					}
				}
			}
			else {
				el = el->Next;
				counter++;
			}
		}
	}
}

void Massiv::InsertInStack(Node * &el)
{
	el->Next = HeadStack;
	el->Prev = NULL;
	el->x = NULL;
	HeadStack = el;
}

Node *Massiv::ExtractFromStack()
{
	Node *temp = HeadStack;
	HeadStack = HeadStack->Next;
	temp->Next = NULL;

	return temp;
}

void Massiv::Show()
{
	//ВЫВОДИМ СПИСОК С КОНЦА
	Node *temp = TailList;
	//Временный указатель на адрес последнего элемента
	while (temp != NULL) //Пока не встретится пустое значение
	{
		cout << temp->x << " "; //Выводить значение на экран
		temp = temp->Prev; //Указываем, что нужен адрес предыдущего элемента
	}
	cout << "\n";

	//ВЫВОДИМ СПИСОК С НАЧАЛА
	temp = HeadList;
	while (temp != NULL)
	{
		cout << temp->x << " ";
		temp = temp->Next;
	}
	cout << "\n";
}

void Massiv::Reallocate(int x)
{
	int capacity = Capacity();
	if (x == 1) {//увеличение памяти
		for (int i = 0; i < capacity; i++) {
			Node *temp = new Node;
			temp->Prev = NULL;
			temp->Next = HeadStack;
			HeadStack = temp;
		}
	}
	if (x == 0) {
		for (int i = 0; i < (capacity) / 2; i++) {
			Node *temp = HeadStack;
			HeadStack = HeadStack->Next;
			delete temp;
		}
	}
}

int Massiv::Size()
{
	int size = 0;
	Node *temp = TailList;
	while (temp != NULL)
	{
		size++;
		temp = temp->Prev; 
	}
	return size;
}

int Massiv::Capacity()
{
	int capacity =0;
	Node *temp = HeadStack;
	while (temp != NULL)
	{
		capacity++;
		temp = temp->Next;
	}
	capacity += Size();
	return capacity;
}

void selection_sort(int *vec, int len) {
	stack<int> st;
	stack<int> new_stack;
	for (int j = 0; j < len; ++j) {
		st.push(vec[j]);
	}
	int num;
	int garb;
	int max = st.top();
	while (!st.empty()) {
		num = st.top();//отщепляется верхушка
		st.pop();
		while (!new_stack.empty() && num > max) {//num меньше чем крайний в стеке, добавляем в отсортированные, если нет, продавливаем дальше
			garb = new_stack.top();
			st.push(garb);
			new_stack.pop();
		}
		max = num;// num кладется в отсортированный стек
		new_stack.push(num);
	}
	int size = new_stack.size();
	for (int i = 0; i < size; ++i) {
		cout << new_stack.top() << " ";
		new_stack.pop();
	}
}

void min_com() {
	vector<int> numbers;
	ifstream file("../1.txt");
	if (file.is_open()) {
		int num;
		while (file >> num) {
			numbers.push_back(num);
		}
		file.close();

		int len_numbers = numbers.size();
		stack<pair<int, int>> myStack;
		vector<int> indices(len_numbers, -1);

		for (int i = 0; i < len_numbers; ++i) {
			while (!myStack.empty() && numbers[i] > myStack.top().first) {
				indices[myStack.top().second] = i;
				myStack.pop();
			}
			myStack.push({ numbers[i], i });
		}
		for (auto i : indices) {
			cout << i << " ";
		}

	}
	else {
		cout << "not open";
	}
}

int main()
{
	//Задача 1
	system("CLS");
	Massiv lst;
	lst.Add(1, 0);
	lst.Add(2, 0);
	lst.Add(3, 1);
	lst.Add(4, 2);
	//lst.Show();

	lst.Add(5, 0);
	lst.Add(5, 0);
	lst.Add(5, 0);
	lst.Remove(5);
	lst.Remove(5);
	lst.Remove(5);
	lst.Remove(3);
	lst.Remove(4);
	lst.Remove(2);
	lst.Show();

	//Задача 2

	int vec[7] = { 12, 17, 0, 17, 15, 17, 19 };
	int len = sizeof(vec) / 4;
	selection_sort(vec, len);
	cout << "\n";

	//Задача 3

	min_com();
	system("PAUSE");
}