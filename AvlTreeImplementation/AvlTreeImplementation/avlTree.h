#pragma once
#include <string>
#include <iostream>
using namespace std;

enum bf {
	RH,
	LH,
	EH
};

struct Node {
	string data;
	bf bf;
	struct Node* left;
	struct Node* right;
};
class avlTree {

public:
	avlTree();
	void InsertItem(string value);
	void printTree();
	Node* Search(string value);
	void DeleteItem(string value);
private:
	Node* root;
	void Insert(struct Node*& tree, string item, bool& taller);
	void Print(Node* leaf);
	void RightBalance(Node*& tree, bool& taller);
	void LeftBalance(Node*& tree, bool& taller);
	void RotateLeft(Node*& tree);
	void RotateRight(Node*& tree);
	Node* SearchItem(Node*& tree, string value);
	void Delete(Node*& tree, string value, bool& shorter);
	void DeleteNode(Node*& tree, bool& shorter);
	void GetPredecessor(Node* tree, string& data);
	void DelRightBalance(Node*& tree, bool& shorter);
	void DelLeftBalance(Node*& tree, bool& shorter);

};

void avlTree::Insert(Node*& tree, string item, bool& taller)
{
	if (tree == NULL)
	{	// Insertion place found.
		tree = new Node;
		tree->left = NULL;
		tree->right = NULL;
		tree->data = item;
		tree->bf = EH;
		taller = true;
	}
	else if (item == tree->data)
	{
		cout << "Duplicate key is not allowed in AVL tree." << endl;
	}
	else if (item < tree->data)
	{
		Insert(tree->left, item, taller);
		if (taller)					 		   
		switch (tree->bf) 
		{
		case LH: LeftBalance(tree, taller); break;
		case EH: tree->bf = LH; break;
		case RH: tree->bf = EH; 					   
		taller = false; break;
		}
	}
	else if (item > tree->data)
	{
		Insert (tree->right, item, taller);
		if (taller)
			switch (tree->bf)
			{
				case RH: RightBalance (tree, taller); break;
				case EH: tree->bf = RH; break;
				case LH: tree->bf = EH; taller = false;break;
			}
	}
 }
void avlTree::Print(Node* leaf)
 {
	 if (leaf != NULL)
	 {
		 Print(leaf->left);
		 cout << leaf->data;
		 cout << "\t ";
		 if (leaf->left == NULL)
		 {
			 cout << "Null";
		 }
		 else
		 {
			 cout << leaf->left->data;
		 }
		 cout << "\t ";
		 if (leaf->right == NULL)
		 {
			 cout << "Null";
		 }
		 else
		 {
			 cout << leaf->right->data;
		 }
		 cout << "\t";
		 switch (leaf->bf)
		 {
			case RH: cout << "RH";
				break;
			case LH: cout << "LH";
				break;
			case EH: cout << "EH";
				break;
		 }
		 cout << "\n";
		 Print(leaf->right);
	 }
 }
void avlTree::RightBalance(Node*& tree, bool& taller)
    {
		Node* rs = tree->right;
		Node* ls;
		switch (rs->bf)
		{
		case RH: tree->bf = rs->bf = EH;
			RotateLeft(tree);
			taller = false;
			break;
			case EH: cerr << "Tree already balanced " << endl;
			break;
			case LH: ls = rs->left;
				switch (ls->bf)
				{
					case RH: tree->bf = LH;
					rs->bf = EH;
					break;
					case EH: tree->bf = rs->bf = EH;
					break;
					case LH:
					{
					tree->bf = EH;
					rs->bf = RH;
					break;
					}
				}
			ls->bf = EH;
			RotateRight(tree->right);
			RotateLeft(tree);
			taller = false;
		}
	}
void avlTree::LeftBalance(Node*& tree, bool& taller)
	{
		Node* ls = tree->left;
		Node* rs;

		switch (ls->bf)
		{
		case LH:	tree->bf = ls->bf = EH;
			RotateRight(tree);
			taller = false;
			break;
		case EH: cerr << "Tree already balanced " << endl;
			break;
		case RH: rs = ls->right;
			switch (rs->bf)
			{
			case LH:
			{
				tree->bf = RH;
				ls->bf = EH;
				break;
			}
			case EH:
			{
				tree->bf = ls->bf = EH;
				break;
			}
			case RH: 
			{
				tree->bf = EH;
				ls->bf = LH;
				break;
			}
			}
			rs->bf = EH;
			RotateLeft(tree->left);
			RotateRight(tree);
			taller = false;
		}

	}
void avlTree::RotateLeft(Node*& tree)
	{
		Node* rs;
		if (tree == NULL)
			cerr << "It is impossible to rotate an empty tree in RotateLeft" << endl;
		else if (tree->right == NULL)
			cerr << "It is impossible to make an empty subtree the root in RotateLeft" << endl;
		else
		{
			rs = tree->right;
			tree->right = rs->left;
			rs->left = tree;
			tree = rs;
		}
	}
void avlTree::RotateRight(Node*& tree)
	{
		Node* ls;
		if (tree == NULL)
			cerr << "It is impossible to rotate an empty tree in RotateRight" << endl;
		else if (tree->left == NULL)
			cerr << "It is impossible to make an empty subtree the root in RotateRight" << endl;
		else
		{
			ls = tree->left;
			tree->left = ls->right;
			ls->right = tree;
			tree = ls;
		}
	}
 avlTree::avlTree()
 {
	 root = NULL;
 }
 void avlTree::InsertItem(string value)
{
	bool taller = false;
	Insert(root,value, taller);
}
 Node* avlTree::Search(string value)
 {
	 return SearchItem(this->root, value);
 }
 Node* avlTree::SearchItem(Node*& tree,string value)
 {
	 if (tree == nullptr || tree->data == value)
	 {
		 return tree;
	 }
	 if (tree->data < value)
		 return SearchItem(tree->right, value);
	 // Key is smaller than root's key
	 return SearchItem(root->left,value);
 }
 void avlTree::printTree()
 {
	 cout << "Current\tLeft\tRight\tBF\n";
	 Print(root);
	 cout << "\n";
 }
 void avlTree::DeleteItem(string value){
	 bool shorter;
	 Delete(root, value, shorter);
 }
 void avlTree::Delete(Node*& tree, string value, bool& shorter)
 {
	 if (tree != NULL)
	 {
		 if (value < tree->data)
		 {
			 Delete(tree->left, value, shorter);
			 if (shorter)
			 {
				 switch (tree->bf)
				 {
				 case LH: tree->bf = EH; break;
				 case EH: tree->bf = RH; shorter = false; break;
				 case RH: DelRightBalance(tree, shorter); break;
				 }
			 }
		 }
		 else if (value > tree->data)
		 {
				Delete(tree->right, value, shorter);
				if(shorter)
				switch (tree->bf)
				{
				case LH: DelLeftBalance(tree, shorter); break;
				case EH: tree->bf = LH; shorter = false; break;
				case RH: tree->bf = EH; break;
				}
		 }
		else 
		{
		 DeleteNode(tree, shorter);
		}
	 }
	 else 
	 {
		 cout << "\n\n" << value << "Node could not be found and deleted\n\n";
	 }
 }
 void avlTree::DeleteNode(Node*& tree, bool& shorter)
 {
	 string data;
	 Node* tempPtr;
	 tempPtr = tree;
	 if (tree->left == NULL)
	 {
		 tree = tree->right;
		 delete tempPtr;
		 shorter = true;
	 }
	 else if (tree->right == NULL)
	 {
		 tree = tree->left;
		 delete tempPtr;
		 shorter = true;
	 }
	 else
	 {
		 GetPredecessor(tree, data);
		 tree->data = data;
		 Delete(tree->left, data, shorter);
		 if (shorter)
			 switch (tree->bf)
			 {
			 case LH: tree->bf = EH; break;
			 case EH: tree->bf = RH; shorter = false; break;
			 case RH: DelRightBalance(tree, shorter);
			 }
	 }
 }
 void avlTree::GetPredecessor(Node* tree, string& data)
 {
	 tree = tree->left;
	 while (tree->right != NULL)
	 {
		 tree = tree->right;
	 }
	 data = tree->data;
 }
 void avlTree::DelRightBalance(Node*& tree, bool& shorter)
 {
	 Node* rs = tree->right;
	 Node* ls;

	 switch (rs->bf)
	 {
	 case RH: tree->bf = rs->bf = EH;
		 RotateLeft(tree);
		 shorter = true; break;
	 case EH: tree->bf = RH;
		 rs->bf = LH;
		 RotateLeft(tree);
		 shorter = false; break;
	 case LH: ls = rs->left;
		 switch (ls->bf)
		 {
		 case RH: tree->bf = LH;
			 rs->bf = EH; break;
		 case EH: tree->bf = rs->bf = EH;
			 break;
		 case LH: tree->bf = EH;
			 rs->bf = RH; break;
		 }
		 ls->bf = EH;
		 RotateRight(tree->right);
		 RotateLeft(tree);
		 shorter = true;
	 }
 }
 void avlTree::DelLeftBalance(Node*& tree, bool& shorter)
 {
	 Node* ls = tree->left;
	 Node* rs;
	 switch (ls->bf)
	 {
	 case LH:  tree->bf = ls->bf = EH;
		 RotateRight(tree);
		 shorter = true; break;
	 case EH: tree->bf = LH;
		 ls->bf = RH;
		 RotateRight(tree);
		 shorter = false; break;
	 case RH: rs = ls->right;
		 switch (rs->bf)
		 {
		 case LH: tree->bf = RH;
			 ls->bf = EH; break;
		 case EH: tree->bf = ls->bf = EH;
			 break;
		 case RH: tree->bf = EH;
			 ls->bf = LH; break;
		 }
		 rs->bf = EH;
		 RotateLeft(tree->left);
		 RotateRight(tree);
		 shorter = true;
	 }
	

 }