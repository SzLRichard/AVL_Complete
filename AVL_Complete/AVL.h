#pragma once
#include "node.h"
#include <iostream>
using namespace std;
template <class T>
class AVL {
	node<T>* root;
	int nodeCount;
	node<T>* ror(node<T>*);
	node<T>* rol(node<T>*);
	node<T>* insert(node<T>*, T);
	void inorder(node<T>* subtree);
	void update(node<T>* subtree);
	node<T>* search(node<T>* subtree, T x);
	node<T>* minimum(node<T>* subtree);
	node<T>* maximum(node<T>* subtree);
	node<T>* remove(node<T>* subtree, T val);
	node<T>* ith(node<T>* subtree, int i);
	T rank(node<T>* subtree, int i);
public:
	T rank(int i);
	node<T>* getRoot();
	node<T>* search(T);
	node<T>* minimum();
	node<T>* maximum();
	node<T>* previous(T x);
	node<T>* next(T x);
	node<T>* ith(int i);
	AVL();
	~AVL();
	void insert(T);
	void remove(T);
	void print();
};
template <class T>
AVL<T>::AVL() {
	root = nullptr;
	nodeCount = 0;
}
template <class T>
AVL<T>::~AVL() {
	delete root;
}
template <class T>
node<T>* AVL<T>::getRoot() {
	return root;
}
template <class T>
void AVL<T>::update(node<T>* subtree) {
	subtree->setHeight(1 + max(subtree->getLeft()->getHeight(), subtree->getRight()->getHeight()));
	subtree->setBalance(subtree->getLeft()->getHeight() - subtree->getRight()->getHeight());
	subtree->setCount(1 + subtree->getLeft()->getCount() + subtree->getRight()->getCount());
}
template <class T>
node<T>* AVL<T>::rol(node<T>* x) {
	node<T>* y = x->getRight();
	node<T>* p = x->getParent();
	x->setRight(y->getLeft());
	y->setLeft(x);
	y->setParent(p);
	update(x);
	update(y);
	return y;
}
template <class T>
node<T>* AVL<T>::ror(node<T>* x) {
	node<T>* y = x->getLeft();
	node<T>* p = x->getParent();
	x->setLeft(y->getRight());
	y->setRight(x);
	y->setParent(p);
	update(x);
	update(y);
	return y;
}

template <class T>
node<T>* AVL<T>::insert(node<T>* x, T value) {
	if (x == nullptr) {
		return new node<T>(value);
	}
	if (value < x->getValue()) {
		x->setLeft(insert(x->getLeft(), value));
	}
	else if (value > x->getValue()) {
		x->setRight(insert(x->getRight(), value));
	}
	else return x;

	update(x);

	//LeftLeft
	if (x->getBalance() > 1 && x->getLeft() != nullptr && value < x->getLeft()->getValue()) {
		return ror(x);
	}
	//RightRight
	if (x->getBalance() < -1 && x->getRight() != nullptr && value > x->getRight()->getValue()) {
		return rol(x);
	}
	//LeftRight
	if (x->getBalance() > 1 && x->getLeft() != nullptr && value > x->getLeft()->getValue()) {
		x->setLeft(rol(x->getLeft()));
		return ror(x);
	}
	//RightLeft
	if (x->getBalance() < -1 && x->getRight() != nullptr && value < x->getRight()->getValue()) {
		x->setRight(ror(x->getRight()));
		return rol(x);
	}
	return x;
}
template <class T>
void AVL<T>::insert(T value) {
	if (search(value) == nullptr) {
		nodeCount++;
		if (root == nullptr) {
			root = new node<T>(value);
		}
		else {
			root = insert(root, value);
		}
	}
}
template <class T>
void AVL<T>::inorder(node<T>* x) {
	if (x != nullptr) {
		inorder(x->getLeft());
		cout << x->getValue() << " ";
		inorder(x->getRight());
	}
}
template <class T>
void AVL<T>::print() {
	inorder(root);
	cout << endl;
}

template <class T>
node<T>* AVL<T>::minimum(node<T>* subtree) {
	node<T>* temp = subtree;
	if (temp == nullptr)
		return nullptr;
	while (temp->getLeft() != nullptr) {
		temp = temp->getLeft();
	}
	return temp;
}
template <class T>
node<T>* AVL<T>::minimum() {
	return minimum(root);
}
template <class T>
node<T>* AVL<T>::maximum(node<T>* subtree) {
	node<T>* temp = subtree;
	if (temp == nullptr)
		return nullptr;
	while (temp->getRight() != nullptr) {
		temp = temp->getRight();
	}
	return temp;
}
template <class T>
node<T>* AVL<T>::maximum() {
	return maximum(root);
}
template <class T>
node<T>* AVL<T>::search(node<T>* subtree, T x) {
	if (subtree == nullptr)
		return subtree;
	else
		if (subtree->getValue() == x) {
			return subtree;
		}
		else if (subtree->getValue() > x) {
			return search(subtree->getLeft(), x);
		}
		else if (subtree->getValue() < x) {
			return search(subtree->getRight(), x);
		}
	return nullptr;
}
template <class T>
node<T>* AVL<T>::search(T x) {
	return search(root, x);
}

template <class T>
node<T>* AVL<T>::next(T x) {
	node<T>* n = search(x);
	if (n == nullptr)
		return nullptr;
	else
		if (n->getRight() != nullptr)
			return minimum(n->getRight());
		else {
			node<T>* p = n->getParent();
			while (p != nullptr && p->getValue() < x) {
				p = p->getParent();
			}
			return p;
		}
}
template <class T>
node<T>* AVL<T>::previous(T x) {
	node<T>* n = search(x);
	if (n == nullptr)
		return nullptr;
	if (n->getLeft() != nullptr) {
		return maximum(n->getLeft());
	}
	else {
		node<T>* p = n->getParent();
		while (p != nullptr && p->getValue() > x) {
			p = p->getParent();
		}
		return p;
	}
}
template <class T>
node<T>* AVL<T>::remove(node<T>* subtree, T val)
{
	if (subtree == nullptr)
		return subtree;
	if (val < subtree->getValue())
		subtree->setLeft(remove(subtree->getLeft(), val));
	else if (val > subtree->getValue())
		subtree->setRight(remove(subtree->getRight(), val));
	else
	{
		if (subtree->getLeft() == nullptr && subtree->getRight() == nullptr)
			return nullptr;
		else
			if (subtree->getLeft() == nullptr) {
				subtree = subtree->getRight();
			}
			else
				if (subtree->getRight() == nullptr)
					subtree = subtree->getLeft();
				else
				{
					node<T>* temp = minimum(subtree->getRight());
					subtree->setValue(temp->getValue());
					subtree->setRight(remove(subtree->getRight(), temp->getValue()));
				}
	}

	if (subtree == nullptr)
		return subtree;
	update(subtree);
	int balance = subtree->getBalance();
	//LeftLeft
	if (balance > 1 && subtree->getLeft()->getBalance() >= 0)
		return ror(subtree);
	// LeftRight 
	if (balance > 1 && subtree->getLeft()->getBalance() < 0)
	{
		subtree->setLeft(rol(subtree->getLeft()));
		return ror(subtree);
	}
	// RightRight
	if (balance < -1 && subtree->getRight()->getBalance() <= 0)
		return rol(subtree);

	// RightLeft
	if (balance < -1 && subtree->getRight()->getBalance() > 0)
	{
		subtree->setRight(ror(subtree->getRight()));
		return rol(subtree);
	}

	return subtree;
}
template <class T>
void AVL<T>::remove(T val) {
	root = remove(root, val);
}
template <class T>
node<T>* AVL<T>::ith(node<T>* subtree, int i) {
	if (subtree->getCount() < i)
		return nullptr;
	else if (subtree->getLeft()->getCount() == i - 1)
		return subtree;
	else if (subtree->getLeft()->getCount() >= i)
		return ith(subtree->getLeft(), i);
	else return ith(subtree->getRight(), i - 1 - subtree->getLeft()->getCount());
}
template <class T>
node<T>* AVL<T>::ith(int i) {
	return ith(root, i);
}
template <class T>
T AVL<T>::rank(node<T>* subtree, int i) {
	if (subtree == nullptr)
		return -1;
	if (subtree->getValue() == i) {
		return 1 + subtree->getLeft()->getCount();
	}
	else
		if (subtree->getValue() > i) {
			return rank(subtree->getLeft(), i);
		}
		else if (subtree->getValue() < i) {
			return 1 + subtree->getLeft()->getCount() + rank(subtree->getRight(), i);
		}
}
template <class T>
T AVL<T>::rank(int i) {
	return rank(root, i);
}
