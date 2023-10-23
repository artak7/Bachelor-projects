//#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
#include <map>
#include <list>

using namespace std;
/* OLD TASKS
int find(const vector <string>  & a_vector, const string & target)
{
	size_t i = 0;
	while (i < a_vector.size() && a_vector[i] != target) i++;
	return i;
}

void replace(vector<string>& a_vector, const string& old_item, const string& new_item)
{
	size_t pos = find(a_vector, old_item);
	while (pos < a_vector.size())
	{
		a_vector[pos] = new_item;
		pos = find(a_vector, old_item);
	}
}

template<typename Item_Type> 
void Delete(vector<Item_Type>& a_vector1, const Item_Type& target)
{
	size_t i = 0;
	/*for (auto it : a_vector1)
		if (*it == target)
			break;
	* /
	while (i < a_vector1.size() && a_vector1[i] != target) i++;
	a_vector1.erase(a_vector1.begin() + i, a_vector1.begin() + i + 1);
}*/


template <typename info>
class Myinfo 
{
public:
	info elem;
	bool newlvl, endlvl;	

	Myinfo() { 
		elem = 0;
		newlvl = false;
		endlvl = false;
	}

	Myinfo(info _elem) { 
		elem = _elem;
		newlvl = false;
		endlvl = false;
	}

	Myinfo(bool _newlvl, bool _endlvl) { 
		elem = 0;
		newlvl = _newlvl;
		endlvl = _endlvl;
	}

	Myinfo(info _elem, bool _newlvl, bool _endlvl) { 
		elem = _elem;
		newlvl = _newlvl;
		endlvl = _endlvl;
	}
};

template <typename info>
class GLList
{
public:
	list <Myinfo <info> > Glist;

	GLList() {}
	GLList(list <info> _list) 
	{
		list <Myinfo <info> > tmp;
		for (auto it : _list)
		{	
			Myinfo <info> t = Myinfo <info>(it, false, false);
			tmp.push_front(t);
		}

		tmp.front().newlvl = true;
		tmp.back().endlvl = true;
		Glist.splice(Glist.begin(), tmp);
	}

	GLList(list <list <info> > _list) 
	{
		list <list <Myinfo <info> > > tmp;
		for (auto it : _list)
		{	
			for (auto it2 : it)
			{
				Myinfo <info> t = Myinfo <info>(it2, false, false);
				tmp.push_front(t);
			}
		}

		tmp.front().front().newlvl = true;
		tmp.back().back().endlvl = true;
		Glist.splice(Glist.begin(), tmp);
	}

	GLList(list <Myinfo <info> > _Glist) {Glist = _Glist;}
	
	GLList(const GLList <info> &obj) 
	{
		//if (typeof(info) == typeof(this)){
			Glist = obj.Glist;
		//}else
		// { cout << "ERROR!"; return 0;}
	}

	~GLList() {Glist.clear();}
	/*GLList& operator=(GLList <info> &obj) 
	{	
		//if (typeof(info) == typeof(this))
			Glist = obj.Glist;
			elem = obj.elem;
		//else
		// { cout << "ERROR!"; return 0;}
		return *this;
	}*/

	/*ofstream &operator << (ostream &out, const GLList<info> &a)
	{
		return out << a.elem << endl;
	}*/
	
	//typename GLList::iterator GLList <info>:: begin() {return Glist.begin();}
	//typename GLList::iterator GLList <info>:: end() {return Glist.end();}

	void Push(Myinfo <info> obj)
	{
		obj.newlvl = true;
		obj.endlvl = true;
		Glist.push_front(obj);
	}

	void Push(info obj)
	{
		bool newlvl = true;
		bool endlvl = true;
		Myinfo <info> newobj = Myinfo <info> (obj, newlvl, endlvl);
		Glist.push_front(newobj);
	}

	void Push(list<Myinfo <info> > obj)
	{
		list <Myinfo <info> > tmp = obj;
		tmp.front().newlvl = true;
		tmp.back().endlvl = true;
		Glist.splice(Glist.begin(), tmp);
	}

	void Push(list<info> obj)
	{
		GLList tmp = GLList <info> (obj);
		Glist.splice(Glist.begin(), tmp.Glist);
	}

	void Push(list<list <Myinfo <info> > > obj)
	{
		list<list <Myinfo <info> > > tmp = obj;
		tmp.front().front().newlvl = true;
		tmp.back().back().endlvl = true;
		Glist.splice(Glist.begin(), tmp);
	}

	void Push(list<list <info> > obj)
	{
		GLList <info> tmp = obj;		
		Glist.splice(Glist.begin(), tmp);
	}

	void PrintList()
	{
		for (auto i : Glist) {
			if (i.newlvl)
				cout << "( ";
			
			cout << i.elem << " ";

			if (i.endlvl)
				cout << ")  ";
		}

		cout << endl;
	}
};

int main()
{

	/* ------ INIT ----------- */

	ifstream cin("input.txt");
	int n;
	cin >> n;
	/*vector <string> v(n);
	for (int i = 0; i < n; i++)
		cin >> v[i];
	
	string target;
	cin >> target;
	*/
	/* END INIT */

	
	list <int> stdlist;
	list <int> stdlist2;
	for (int i = 0; i < n; i++)
	{
		int x;
		cin >> x;
		stdlist.push_front(x);
	}
	int m; cin >> m;
	for (int i = 0 ; i < m ; i++)
	{
		int x;
		cin >> x;
		stdlist2.push_front(x);
	}

	GLList <int> glist(stdlist);
	glist.Push(11111);
	glist.Push(stdlist2);
	glist.PrintList();

	system("pause");
	return 0;
}















	/*
	for (auto it: v)
		cout << it << " ";

	cout << endl;
	Delete<string>(v, "str");
	for (auto it: v)
		cout << it << " ";

	cout << endl;
	
	map<pair<int,int>, double> M;
	/*for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			cin >> M[make_pair(i, j)];
			* /
	
	M[make_pair(0, 0)] = 2.2;
	//M[make_pair(0, 1)] = 0;
	M[make_pair(0, 2)] = 7;
	//M[make_pair(1, 0)] = 0;
	//M[make_pair(1, 1)] = 0;
	//M[make_pair(1, 2)] = 0;
	//M[make_pair(2, 0)] = 0;
	M[make_pair(2, 1)] = 2.3;
	//M[make_pair(2, 2)] = 0;
	
	for (int i = 0; i < 3; i++, cout << endl)
		for (int j = 0; j < 3; j++)
			cout << M[make_pair(i, j)] <<  " ";

	system("pause");
	return 0;
}
*/