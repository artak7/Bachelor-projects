#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

struct Node
{
	int data;
	struct Node* left;
	struct Node* right;
};

void preOrder(Node *node) {
	if (node == nullptr) return;
	cout << node->data<< " ";
	preOrder(node->left);
	preOrder(node->right);
}

void postOrder(Node *node) {
	if (node == nullptr) return;
	postOrder(node->left);
	postOrder(node->right);
	cout << node->data<<" ";
}

int height(Node* node)
{
	if (node == NULL)
		return 0;
	else
	{
		int lheight = height(node->left);
		int rheight = height(node->right);

		if (lheight > rheight)
			return(lheight + 1);
		else return(rheight + 1);
	}
}

int countOfTops(Node &node) {
	if (&node == NULL) return 0;
	return countOfTops(*node.left) + countOfTops(*node.right)+1;
}

bool bin(Node *node, int rodForRight, int rodForLeft)
{
	if (node == NULL) return true;
	if (node->data <= rodForRight || node->data >= rodForLeft) return false;
	return bin(node->left, rodForRight, node->data) && bin(node->right, node->data, rodForLeft);
}

struct Node* addNode(int data)
{
	struct Node* node = (struct Node*) malloc(sizeof(struct Node));
	node->data = data;
	node->left = NULL;
	node->right = NULL;

	return(node);
}

int main()
{
	setlocale(LC_CTYPE, "rus");

	struct Node *root = addNode(4);
	root->left = addNode(2);
	root->left->left = addNode(1);
	root->left->right = addNode(3);
	root->right = addNode(8);
	root->right->left = addNode(6);
	root->right->right = addNode(9);
	root->right->left->right = addNode(7);

	preOrder(root);
	cout << "\n";
	postOrder(root);
	cout << "\n";
	cout << "Высота дерева: " << height(root);
	cout << "\n";
	cout << "Количество вершин: " << countOfTops(*root);
	cout << "\n";
	cout << bin(root, INT_MIN, INT_MAX);
	/* выполнение операций над деревом */
	//printLevelOrder(root);

	//printf("\nвысота: %d\n", height(root));
	//printf("\nширина %d\n", getMaxWidth(root));

	//printf("\n%d\n", lookup(root, 100));
	//printf("\n%d\n", lookup(root, 33));
	system("PAUSE");
	return 0;
}