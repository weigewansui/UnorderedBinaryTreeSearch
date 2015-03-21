#ifndef TREE_H
#define TREE_H

#include <iostream>
#include <string>
using namespace std;

struct Node {

	int v;
	Node *left;
	Node *right;
};

class BinaryTree {
private:
	Node* findPointer(int, Node*&); // return the pointer that points to the name; search the pointers sub tree
	Node* findPointer(int); //Return the pointer that points to the name, searching for the whole tree;
	int available_position(int); // find which position of a node is available
	// Node * findFather(int NodeName, Node *start); // find the father node start searching from a node
	// Node * findFather(int NodeName); //find the father node start searching from root
	
	Node * findFather(int NodeName, Node *start); // find the father node start searching from a node
	Node * findFather(int NodeName); //find the father node start searching from root

public:

	BinaryTree(); // constructor;
	BinaryTree(int); // construct with fist node;
	// BinaryTree(const BinaryTree&);//copy constructor
	~BinaryTree(); //Destructor
	Node *root;

	void print(ostream &);
	Node* insert(int); // insert when first time;
	void insert(Node* &, int); //insert when know the pointer
	void insert(int, int, char); //insert to a named node right or left;
	void SuperInsert(int,int); // Amazing Insert Function, just try it!!

	void erase(Node *&);
	void erase(void);
	void erase(int);// erase by nodename
	void SuperErase(int);

	void print(ostream &, Node *&);	//print a tree from certain node with pointer
	void print(ostream &, int); //print a tree from certain node with node value
	void AttachChild(int, Node*,char); // Attach a tree to one of the father in another tree;
	void SmartAttach(int Father, Node* obj);

	bool is_element(int); //find if a node is element of the tree;

	//void findPointer(int, Node*&); // return the pointer  that points to the node with this

	//void locatePointer(int, Node*&) ;	



};

#endif
