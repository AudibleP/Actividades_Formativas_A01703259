#ifndef BST_H_
#define BST_H_

#include <string>
#include <sstream>
#include <iostream>

template <class T> class BST;

template <class T>
class Node {
	private:
		T value;
		Node *left, *right;
		Node<T>* succesor();

	public:
		Node(T);
		Node(T, Node<T>*, Node<T>*);
		void add(T);
		bool find(T);
		void remove(T);
		void removeChilds();

		int whatlevelamI(T);
		bool ancestors(T, std::stringstream&) const;
		int height() const;

		void preorder(std::stringstream&) const;
		void inorder(std::stringstream&) const;
		void postorder(std::stringstream&) const;
		void showlevel(std::stringstream&, int) const;
		void levelbylevel(std::stringstream&) const;

		friend class BST<T>;
};

//////////////////////////////NODE//////////////////////////////////////////

template <class T>
Node<T>::Node(T val): value(val), left(0), right(0) {}

template <class T>
Node<T>::Node(T val, Node<T> *le, Node<T> *ri): value(val), left(le), right(ri) {}

/////////////////////////////////////////////////////////////////////////

template <class T>
Node<T>* Node<T>::succesor(){
	Node<T> *l, *r;
	l = left;
	r = right;
	if (left == 0) {
		if (right != 0) {
			right = 0;
		}
		return r;
	}
	if (left->right == 0) {
		left = left->left;
		l->left = 0;
		return l;
	}
	Node<T> *parent, *child;
	parent = left;
	child = left->right;
	while (child->right != 0) {
		parent = child;
		child = child->right;
	}
	parent->right = child->left;
	child->left = 0;
	return child;
}

/////////////////////////////////////////////////////////////////////////////

template <class T>
void Node<T>::add(T val){
	if (val < value){
		if (left != 0){
			left->add(val);
		}
		else {
			left = new Node<T>(val);
		}
	}
	else {
		if (right != 0){
			right->add(val);
		}
		else {
			right = new Node<T>(val);
		}
	}
}

////////////////////////////////////////////////////////////////////////////

template <class T>
bool Node<T>::find(T val){
	if (val == value){
		return true;
	}
	else if (val < value){
		return (left != 0 && left->find(val));
	}
	else if (val > value){
		return (right != 0 && right->find(val));
	}
}

////////////////////////////////////////////////////////////////////////////

template <class T>
void Node<T>::remove(T val){
	Node<T> * pred, *old;
	if (val < value) {
		if (left != 0) {
			if (left->value == val) {
				old = left;
				pred = left->succesor();
				if (pred != 0) {
					pred->left = old->left;
					pred->right = old->right;
				}
				left = pred;
				delete old;
			}
			else {
				left->remove(val);
			}
		}
	}
	else if (val > value) {
		if (right != 0) {
			if (right->value == val) {
				old = right;
				pred = right->succesor();
				if (pred != 0) {
					pred->left = old->left;
					pred->right = old->right;
				}
				right = pred;
				delete old;
			}
			else {
				right->remove(val);
			}
		}
	}
}

/////////////////////////////////////////////////////////////////

template <class T>
void Node<T>::removeChilds(){
	if (left != 0) {
		left->removeChilds();
		delete left;
		left = 0;
	}
	if (right != 0) {
		right->removeChilds();
		delete right;
		right = 0;
	}
}

////////////////////////////////////////////////////////////////////

template <class T>
int Node<T>::height() const {
	int lef = 0;
	int rig = 0;
	if (left != 0){
		lef = left->height() + 1;
	}
	if (right != 0) {
		rig = right->height() +1;
	}
	if (lef == 0 && rig == 0){
		return 1;
	}
	return (rig > lef) ? rig : lef;
}

//////////////////////////////////////////////////////////////////

template <class T>
bool Node<T>::ancestors(T val, std::stringstream &aux) const{
	if (val == value) {
	  return true;
	}
	else if (val < value) {
		if (aux.tellp() != 1){
			aux << " ";
		}
		aux << value;
		return (left != 0 && left->ancestors(val,aux));
	}
	else if (val > value) {
		if (aux.tellp() != 1) {
			aux << " ";
		}
		aux << value;
		return (right != 0 && right->ancestors(val,aux));
	}
	return false;
}

//////////////////////////////////////////////////////////////////

template <class T>
int Node<T>::whatlevelamI(T val) {
	if (val == value) {
		return 1;
	} else if (val < value) {
		if(left != 0)
			return left->whatlevelamI(val) + 1;
	} else if (val > value) {
		if (right != 0)
		return right->whatlevelamI(val) + 1;
	}
	return -1;
}

//////////////////////////////////////////////////////////////////////////

template <class T>
void Node<T>::preorder(std::stringstream &aux) const{
	aux << value;
	if (left != 0) {
		aux << " ";
		left->preorder(aux);
	}
	if (right != 0) {
		aux << " ";
		right->preorder(aux);
	}
}

////////////////////////////////////////////////////////////////////////////

template <class T>
void Node<T>::inorder(std::stringstream &aux) const{
	if (left != 0) {
		left->inorder(aux);
	}
	if (aux.tellp() != 1) {
		aux << " ";
	}
	aux << value;
	if (right != 0) {
		right->inorder(aux);
	}
}

///////////////////////////////////////////////////////////////////////////////////

template <class T>
void Node<T>::postorder(std::stringstream &aux) const{
	if (left != 0) {
		left->postorder(aux);
	}
	if (right != 0) {
		right->postorder(aux);
	}
	if (aux.tellp() != 1) {
			aux << " ";
	}
	aux << value;
}

////////////////////////////////////////////////////////////////////////////////////

template <class T>
void Node<T>::showlevel(std::stringstream &aux, int level) const {
	if(level == 0){
		if (aux.tellp() != 1) {
				aux << " ";
		}
		aux << value;
	}
  if (left != 0) {
		left->showlevel(aux, level -1);
	}
  if (right != 0) {
		right->showlevel(aux, level -1);
	}
}

////////////////////////////////////////////////////////////////////////////////////

template <class T>
void Node<T>::levelbylevel(std::stringstream &aux) const {
	int level = height();
  for(int i = 0; i < level; i++){
			showlevel(aux, i);
	}
}

///////////////////////////////////////BST//////////////////////////////////////////////

template <class T>
class BST{
	private:
		Node<T> *root;

	public:
		BST();
		~BST();
		bool empty() const;
		void add(T);
		bool find(T) const;
		void remove(T);
		void removeAll();

		int whatlevelamI(T);
		std::string ancestors(T) const;
		int height() const;

		std::string inorder() const;
		std::string preorder() const;
		std::string postorder() const;
		std::string levelbylevel() const;
		std::string visit();
};

///////////////////////////////////////////////////////////////////////////////////

template <class T>
BST<T>::BST(): root(0) {}


template <class T>
BST<T>::~BST(){
	removeAll();
}


template <class T>
bool BST<T>::empty() const{
	return (root == 0);
}

/////////////////////////////////////////////////////////////////////////////////////

template<class T>
void BST<T>::add(T val){
	if (root != 0){
		if (!root->find(val)){
			root->add(val);
		}
	}
	else {
		root = new Node<T>(val);
	}
}

///////////////////////////////////////////////////////////////////////////////////////

template <class T>
bool BST<T>::find(T val) const{
	if (root != 0){
		return root->find(val);
	}
	else {
		return false;
	}
}

//////////////////////////////////////////////////////////////////////////////////////

template <class T>
void BST<T>::remove(T val){
	if (root != 0) {
		if (val == root->value) {
			Node<T> *pred = root->succesor();
			if (pred != 0) {
				pred->left = root->left;
				pred->right = root->right;
			}
			delete root;
			root = pred;
		}
		else {
			root->remove(val);
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////

template <class T>
void BST<T>::removeAll(){
	if (root != 0){
		root->removeChilds();
	}
	delete root;
	root = 0;
}

///////////////////////////////////////////////////////////////////////////////////////////

template <class T>
int BST<T>::whatlevelamI(T val){
	if (root != 0) {
	 	int num = root->whatlevelamI(val);
		if(num < 0) return -1;
		return num;
	}
	else {
		return -1;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////

template <class T>
std::string BST<T>::ancestors(T val) const {
	std::stringstream aux;
	aux << "[";
	if (!empty()) {
		if(!root->ancestors(val, aux))
			return "[]";
	}
	aux << "]";
	return aux.str();
}

////////////////////////////////////////////////////////////////////////////////////////

template <class T>
int BST<T>::height() const {
	return root->height();
}

////////////////////////////////////////////////////////////////////////////////////

template <class T>
std::string BST<T>::preorder() const{
	std::stringstream aux;
	aux << "[";
	if (!empty()) {
		root->preorder(aux);
	}
	aux << "]";
	return aux.str();
}


template <class T>
std::string BST<T>::inorder() const{
	std::stringstream aux;
	aux << "[";
	if (!empty()) {
		root->inorder(aux);
	}
	aux << "]";
	return aux.str();
}


template <class T>
std::string BST<T>::postorder() const{
	std::stringstream aux;
	aux << "[";
	if (!empty()) {
		root->postorder(aux);
	}
	aux << "]";
	return aux.str();
}


template <class T>
std::string BST<T>::levelbylevel() const {
	std::stringstream aux;
	aux << "[";
	if (!empty()) {
		root->levelbylevel(aux);
	}
	aux << "]";
	return aux.str();
}

//////////////////////////////////////////////////////////////////////////////

template <class T>
std::string BST<T>::visit() {
	std::stringstream aux;
	aux << preorder() << "\n";
	aux << inorder() << "\n";
	aux << postorder() << "\n";
	aux << levelbylevel();
	return aux.str();
}

#endif
