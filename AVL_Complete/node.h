#pragma once
template<class T>
class node {
	T val;
	node* left;
	node* right;
	node* parent;
	int count;
	int height;
	int balance;
public:
	node();
	node(T);
	~node();
	node* getLeft();
	node* getRight();
	node* getParent();
	int getHeight();
	int getBalance();
	int getCount();
	T getValue();
	void setCount(int);
	void setHeight(int);
	void setBalance(int);
	void setValue(T);
	void setParent(node*);
	void setLeft(node*);
	void setRight(node*);
};
template<class T>
node<T>::node() {
	val = 0;
	left = nullptr;
	right = nullptr;
	parent = nullptr;
	height = 1;
	balance = 0;
	count = 1;
}
template <class T>
node<T>::node(T value) {
	val = value;
	left = nullptr;
	right = nullptr;
	parent = nullptr;
	height = 1;
	balance = 0;
	count = 1;
}
template <class T>
void node<T>::setValue(T value) {
	val = value;
}
template <class T>
int node<T>::getCount() {
	if (!this)
		return 0;
	return count;
}
template <class T>
void node<T>::setCount(int x) {
	count = x;
}
template <class T>
int node<T>::getBalance() {
	return balance;
}
template <class T>
int node<T>::getHeight() {
	if (this != nullptr) {
		return height;
	}
	else return 0;
}
template <class T>
T node<T>::getValue() {
	return val;
}
template <class T>
node<T>* node<T>::getLeft() {
	return left;
}
template <class T>
node<T>* node<T>::getRight() {
	return right;
}
template <class T>
void node<T>::setBalance(int bal) {
	balance = bal;
}
template <class T>
void node<T>::setHeight(int h) {
	height = h;
}
template <class T>
void node<T>::setLeft(node<T>* x) {
	left = x;
	if (x != nullptr)
		x->setParent(this);
}
template <class T>
void node<T>::setRight(node<T>* x) {
	right = x;
	if (x != nullptr)
		x->setParent(this);
}
template <class T>
node<T>* node<T>::getParent() {
	return parent;
}
template <class T>
void node<T>::setParent(node* p) {
	parent = p;
}
template <class T>
node<T>::~node() {
	delete left;
	delete right;
}