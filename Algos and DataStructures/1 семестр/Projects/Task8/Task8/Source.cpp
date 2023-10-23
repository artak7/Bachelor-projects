#include<stdio.h>
#include<stdlib.h>

	struct Node
{
	int key;
	struct Node *left, *right;
};

struct Node* newNode(int key)
{
	struct Node* node = (struct Node*)malloc(sizeof(struct Node));
	node->key = key;
	node->left = node->right = NULL;
	return (node);
}

struct Node *rightRotate(struct Node *x)
{
	struct Node *y = x->left;
	x->left = y->right;
	y->right = x;
	return y;
}

struct Node *leftRotate(struct Node *x)
{
	struct Node *y = x->right;
	x->right = y->left;
	y->left = x;
	return y;
}

struct Node *Splay(struct Node *root, int key)
{
	if (root == NULL || root->key == key)
		return root;

	if (root->key > key)
	{
		if (root->left == NULL) return root;
		if (root->left->key > key)
		{
			root->left->left = Splay(root->left->left, key);
			root = rightRotate(root);
		}
		else if (root->left->key < key)
		{
			root->left->right = Splay(root->left->right, key);
			if (root->left->right != NULL)
				root->left = leftRotate(root->left);
		}
		return (root->left == NULL) ? root : rightRotate(root);
	}
	else
	{
		if (root->right == NULL) return root;
		if (root->right->key > key)
		{
			root->right->left = Splay(root->right->left, key);
			if (root->right->left != NULL)
				root->right = rightRotate(root->right);
		}
		else if (root->right->key < key)
		{
			root->right->right = Splay(root->right->right, key);
			root = leftRotate(root);
		}

		return (root->right == NULL) ? root : leftRotate(root);
	}
}

struct Node *Search(struct Node *root, int key)
{
	return Splay(root, key);
}

void preOrder(struct Node *root)
{
	if (root != NULL)
	{
		printf("%d ", root->key);
		preOrder(root->left);
		preOrder(root->right);
	}
}

struct Node *Insert(struct Node *root, int k)
{
	if (root == NULL) return newNode(k);
	root = Splay(root, k);
	if (root->key == k) return root;

	struct Node *newnode = newNode(k);
	if (root->key > k)
	{
		newnode->right = root;
		newnode->left = root->left;
		root->left = NULL;
	}
	else
	{
		newnode->left = root;
		newnode->right = root->right;
		root->right = NULL;
	}
	return newnode;
}

struct Node* Remove(struct Node *root, int key)
{
	struct Node *temp;
	if (!root)
		return NULL;
	root = Splay(root, key);

	if (key != root->key)
		return root;
	if (!root->left)
	{
		temp = root;
		root = root->right;
	}
	else
	{
		temp = root;
		root = Splay(root->left, key);
		root->right = temp->right;
	}
	free(temp);
	return root;

}

int main()
{
	struct Node *root = newNode(9);
	root->left = newNode(6);
	root->right = newNode(10);
	root->left->left = newNode(4);
	root->left->left->right = newNode(5);
	root->left->left->left = newNode(3);
	root->left->left->left->left = newNode(2);

	root = Search(root, 2);
	root = Insert(root, 7);
	root = Remove(root, 4);
	preOrder(root);

	system("pause");
	return 0;
}