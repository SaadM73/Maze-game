#pragma once


#pragma once

#include<iostream>
using namespace std;
#include"reward.h"

struct AVLNode
{
	reward* r;
	AVLNode* right;
	AVLNode* left;
	int height;
	int count;

	AVLNode() : r(NULL), right(NULL), left(NULL), height(1), count(-1)
	{}
};

class AVLTree
{
public:

	AVLNode* root;

	AVLTree() : root(NULL)
	{}

	void insert(reward* r)
	{
		root = insertnode(r, root);
	}

	AVLNode* insertnode(reward* r2, AVLNode* root)
	{
		if (root == NULL)
		{
			root = new AVLNode;
			root->r = r2;
			root->left = root->right = NULL;
			root->count++;
		}
		else if (r2->ID < root->r->ID)
		{
			root->left = insertnode(r2, root->left);

			if (balancefactor(root) == 2)
			{
				if (r2->ID < root->left->r->ID)
				{
					root = rrrotation(root);
				}
				else
				{
					root = rlrotation(root);
				}
			}
		}
		else if (r2->ID > root->r->ID)
		{
			root->right = insertnode(r2, root->right);

			if (balancefactor(root) == -2)
			{
				if (r2->ID > root->right->r->ID)
				{
					root = llrotation(root);
				}
				else
				{
					root = lrrotation(root);
				}
			}
		}

		else if (r2->ID == root->r->ID)
		{
			root->count++;

		}

		root->height = 1 + max(height(root->left), height(root->right));

		return root;
	}

	int height(AVLNode* root)
	{
		if (root == NULL)
		{
			return 1;
		}

		return root->height;
	}

	int balancefactor(AVLNode* root)
	{
		return height(root->left) - height(root->right);
	}

	int findmin()
	{
		AVLNode* temp = root;

		while (temp->left != NULL)
		{
			temp = temp->left;
		}

		return temp->r->ID;
	}

	int findmax()
	{
		AVLNode* temp = root;

		while (temp->right != NULL)
		{
			temp = temp->right;
		}

		return temp->r->ID;
	}

	void display()
	{
		inordertraversal();
	}

	bool checkforavl()
	{
		if (balancefactor(root) >= -1 && balancefactor(root) <= -1)
		{
			return true;
		}

		return false;
	}

	void inorder(AVLNode* root)
	{
		if (root != NULL)
		{
			inorder(root->left);
			cout << root->r->ID << " " << root->r->name << endl;
			inorder(root->right);

		}
	}

	void postorder(AVLNode* root)
	{
		if (root != NULL)
		{
			postorder(root->left);
			postorder(root->right);
			cout << root->r->ID << " " << root->r->name << endl;
		}
	}

	void preorder(AVLNode* root)
	{
		if (root != NULL)
		{
			cout << root->r->ID << " " << root->r->name << endl;
			preorder(root->left);
			preorder(root->right);
		}
	}

	void inordertraversal()
	{
		cout << "---- IN ORDER TRAVERSAL ----- \n\n ";
		inorder(root);
		cout << "\n";
	}

	void preordertraversal()
	{
		preorder(root);
	}

	void postordertraversal()
	{
		postorder(root);
	}


	AVLNode* minValueNode(AVLNode* node) {
		AVLNode* current = node;
		while (current->left != nullptr)
			current = current->left;
		return current;
	}

	AVLNode* rrrotation(AVLNode* root) {
		AVLNode* rp = root->left;
		root->left = rp->right;
		rp->right = root;

		root->height = 1 + max(height(root->left), height(root->right));
		rp->height = 1 + max(height(rp->left), height(rp->right));

		return rp;
	}

	AVLNode* llrotation(AVLNode* root) {
		AVLNode* rp = root->right;
		root->right = rp->left;
		rp->left = root;

		root->height = 1 + max(height(root->left), height(root->right));
		rp->height = 1 + max(height(rp->left), height(rp->right));

		return rp;
	}

	AVLNode* rlrotation(AVLNode* root) {
		root->left = llrotation(root->left);

		return rrrotation(root);
	}

	AVLNode* lrrotation(AVLNode* root) {
		root->right = rrrotation(root->right);

		return llrotation(root);
	}

	AVLNode* removeNode(AVLNode* root, int value) {  // THIS WILL BE ID in our game case
		if (root == nullptr)
			return root;

		// Recursive case to find the node to delete
		if (value < root->r->ID)
			root->left = removeNode(root->left, value);
		else if (value > root->r->ID)
			root->right = removeNode(root->right, value);
		else {
			// Node with only one child or no child
			if (root->left == nullptr || root->right == nullptr) {
				AVLNode* temp = root->left ? root->left : root->right;
				if (temp == nullptr) {
					temp = root;
					root = nullptr;
				}
				else {
					*root = *temp;  // Copy contents of non-empty child
				}
				delete temp;
			}
			else {
				// Node with two children, get the inorder successor
				AVLNode* temp = minValueNode(root->right);
				root->r->ID = temp->r->ID;
				root->right = removeNode(root->right, temp->r->ID);
			}
		}

		if (root == nullptr)
			return root;

		// Update height of this node
		root->height = 1 + max(height(root->left), height(root->right));

		// Rebalance the tree
		int balance = balancefactor(root);
		if (balance > 1 && balancefactor(root->left) >= 0)  // Left Left Case
			return rrrotation(root);
		if (balance > 1 && balancefactor(root->left) < 0) {  // Left Right Case
			root->left = llrotation(root->left);
			return rrrotation(root);
		}
		if (balance < -1 && balancefactor(root->right) <= 0)  // Right Right Case
			return llrotation(root);
		if (balance < -1 && balancefactor(root->right) > 0) {  // Right Left Case
			root->right = rrrotation(root->right);
			return llrotation(root);
		}

		return root;
	}

	void remove(int value) {
		root = removeNode(root, value);
	}


	void checkBalanceRoot() {
		cout << "The Balance Factor of root is : " << root->left->height - root->right->height << endl;
	}

};

