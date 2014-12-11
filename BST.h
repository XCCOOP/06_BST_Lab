//DO NOT CHANGE THIS FILE
//Author: Bo Brinkman
//Date: 2013/10/01

 //Author: Nick Cooperrider
 //Date: 12/10/2014
 //All code written by myself with examples taken from class.

 #include "SSet.h"
 
 template <class Key, class T>
 class Node {
 public:
 	Key k;
 	T data;
 	Node* left;
 	Node* right;
 };
 
 template <class Key, class T>
 class BST : public SSet <Key,T> {
 public:
 	BST();
 	~BST();
 
 	//Return the number of items currently in the SSet
 	virtual unsigned long size();
 
 	//Add a new item, x, with Key k.
 	// If an item with Key k already exists, overwrite it
 	virtual void add(Key k, T x);
 
 	//Remove the item with Key k. If there is no such item, do nothing.
 	virtual void remove(Key k);
 
 	//Return the item with Key k. 
 	// If there is no such item, throw an exception.
 	virtual T find(Key k);
 	//Return true if there is an item with Key k in the table. If not,
 	// return false
 	virtual bool keyExists(Key k);
 
 	//If there is a key in the set that is > k,
 	// return the first such key. If not, return k
 	virtual Key next(Key k);
 	//If there is a key in the set that is < k,
 	// return the first such key. If not, return k
 	virtual Key prev(Key k);
 
 private:
 	Node<Key,T>* root;
 
 	virtual unsigned long size(Node<Key,T>* r);
 	//These are the recursive versions of each of your methods.
 	// You should return the address of the new root node, whether
 	// or not the root node changes.
 	virtual Node<Key,T>* add(Key k, T x, Node<Key,T>* r);
 	virtual Node<Key,T>* remove(Key k, Node<Key,T>* r);
 
 	//This one returns the address of the found node, NULL
 	// if not found
 	virtual Node<Key,T>* find(Key k, Node<Key,T>* r);
 
 	//Find the item in the sub-tree rooted at r which has the smallest key
 	virtual Node<Key,T>* min(Node<Key,T>* r);
 
 	//Find the item in the sub-tree rooted at r which has the largest key
 	virtual Node<Key,T>* max(Node<Key,T>* r);
 
 	//Find the next/prev node, and return its address
 	virtual Node<Key,T>* next(Key k, Node<Key,T>* r);
 	virtual Node<Key,T>* prev(Key k, Node<Key,T>* r);
 
 };
 //Start of .ipp
 


 #define NULL 0
 #include <string>
 
 template <class Key, class T>
 BST<Key,T>::BST(){
 	root = NULL;
 }
 
 template <class Key, class T>
 BST<Key,T>::~BST(){
	 while (root != NULL) {
		 remove(root->k);
	 }
 }
 
 template <class Key, class T>
 unsigned long BST<Key,T>::size(){
 	return size(root);
 }
 
 template <class Key, class T>
 unsigned long BST<Key,T>::size(Node<Key,T>* r){

	 if(r == NULL) {
		 return 0;
	 } else {
		 return 1 + size(r->left) + size(r->right);
	 }
 }
 
 template <class Key, class T>
 void BST<Key,T>::add(Key k, T x){
 	root = add(k, x, root);
 }
 
 template <class Key, class T>
 void BST<Key,T>::remove(Key k){
 	root = remove(k, root);
 }
 
 template <class Key, class T>
 T BST<Key,T>::find(Key k){
 	Node<Key,T>* n = find(k, root);

 	if(n == NULL) {
 		throw std::string("That is not an item!");
 		return NULL;
 	}

 	return n->data;
 }
 
 template <class Key, class T>
 bool BST<Key,T>::keyExists(Key k){

	 if(find(k, root) == NULL) {
		 return false;
	 } else {
		 return true;
	 }
 }
 
 template <class Key, class T>
 Key BST<Key,T>::next(Key k){

	 Node<Key,T>* n = next(k, root);

	 if(n != NULL) {
		 return n->k;
	 }else {
		 return k;
	 }
 }
 
 template <class Key, class T>
 Node<Key,T>* BST<Key,T>::next(Key k, Node<Key,T>* r){

	 if(r == NULL) {
		 return NULL;
	 }else if(k < r->k) {
		 if(r->left == NULL || max(r->left)->k <= k) {
			 return r;
		 }else {
			 return next(k, r->left);
		 }
	 }else {
		 return next(k, r->right);
	 }
 }
 
 template <class Key, class T>
 Key BST<Key,T>::prev(Key k){
	 
	 Node<Key,T>* n = prev(k, root);

	 if(n != NULL) {
		 return n->k;
	 }else {
		 return k;
	 }
 }
 
 template <class Key, class T>
 Node<Key,T>* BST<Key,T>::prev(Key k, Node<Key,T>* r){
	 
	 if(r == NULL) {
		 return NULL;
	 }else if(k > r->k) {
		 if(r->right == NULL || r->right->k >= k) {
			 return r;
		 }else {
			 return prev(k, r->right);
		 }
	 }else {
		 return prev(k, r->left);
	 }
 }
 
 template <class Key, class T>
 Node<Key,T>* BST<Key,T>::add(Key k, T x, Node<Key,T>* r){
	 
	 if(r == NULL) {
		 Node<Key, T>* n = new Node<Key, T>();
 		 n->k = k;
 		 n->data = x;
 		 n->left = NULL;
 		 n->right = NULL;
 		 return n;
	 }else if(k == r->k) {
		 r->data = x;
	 }else if(k > r->k) {
		 r->right = add(k,x,r->right);
	 }else {
		 r->left = add(k,x,r->left);
	 }
 	 return r;
 }
 
 template <class Key, class T>
 Node<Key,T>* BST<Key,T>::remove(Key k, Node<Key,T>* r){
	 
	 if(k == r->k) {
		 if(r->right == NULL && r->left == NULL) {
			 delete r;
 			 return NULL;
		 }else if(r->right == NULL && r->left != NULL) {
 			 Node<Key, T>* n = r->left;
 			 delete r;
 			 return n;
 		 }else if(r->right != NULL && r->left == NULL) {
 			 Node<Key, T>* n = r->right;
 			 delete r;
 			 return n;
 		 }else {
 			 Node<Key, T>* n = min(r->right);
 			 r->k = n->k;
 			 r->data = n->data;
 			 remove(n->k, n);
 			 return r;
 		 }
 	 }else if(r->k > k) {
 		 r->left = remove(k, r->left);
 		 return r;
 	 }else {
 		 r->right = remove(k, r->right);
 		 return r;
 	 }
 }
 
 template <class Key, class T>
 Node<Key,T>* BST<Key,T>::find(Key k, Node<Key,T>* r){
 	
	 if(r == NULL) {
		 return NULL;
	 }else if(k == r->k) { 
 		 return r;
	 }else if(k > r->k) {
		 return find(k, r->right);
	 }else {
 		 return find(k, r->left);
	 }
 }
 
 template <class Key, class T>
 Node<Key,T>* BST<Key,T>::max(Node<Key,T>* r){

	 if(r->right == NULL) {
		 return r;
	 }else {
		 return max(r->right);
	 }
 }
 
 template <class Key, class T>
 Node<Key,T>* BST<Key,T>::min(Node<Key,T>* r){

	 if(r->left == NULL) {
		 return r;
	 }else {
		 return min(r->left);
	 }
}