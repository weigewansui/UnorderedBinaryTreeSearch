#include "BinaryTree.h"
#include "stdlib.h"
#include <string>

BinaryTree::BinaryTree() {
	
	root    = NULL;
}

BinaryTree::BinaryTree(int key) {
	root=new Node;
	root->v = key;
	root->left = NULL;
	root->right = NULL;
}

BinaryTree::~BinaryTree() {

	erase(root);

}

/**
 * insert node for the first time;
 * return the key of the root;
 */

Node* BinaryTree::insert(int key) {

	// root = new Node;

	//when there is no root = new Node, 
	insert(root, key);

	return root;
}

/**
 * insert a node attached to certain position of a existing node
 * @param NodeName Node that the new node would like to attach to
 * @param Key      name for the newly inserted node
 * @param position l for left, 'r' for left
 */
void BinaryTree::insert(int NodeName, int key, char position){
	if (is_element(key))
	{
		cerr<<key<<" is already a node in the tree!!!\n";
		return;
	}

	//search Node pointer start from root;
	Node *nodePosition = findPointer(NodeName, root);

	switch(position){
		case 'r': insert(nodePosition->right,key); break;
		case 'l': insert(nodePosition->left,key); break;
		default: cerr <<"Insert position wrong! Enter 'l' or 'r'!";
	}

}

void BinaryTree::insert(Node * &obj, int key) {
	if (is_element(key))
	{
		cerr<<key<<" is already a node in the tree!!!\n";
		return;
	}

	if (obj == NULL)
	{
		obj        = new Node;
		obj->v     = key;
		//cout <<obj->v<<endl;
		obj->left  = NULL;
		obj->right = NULL;
	} else {
		cerr<<"This position is already taken by node "<<obj->v<<"!\n";
	}

}

void BinaryTree::SuperInsert(int NodeName, int key){
	if (available_position(NodeName) == 0) {

		cout<<"Node "<<NodeName<<" does not exists, do you want to insert node "<< NodeName<<" first?"<<endl;
		int Choice;
		cout<<"1. Yes\t 0.No\n";
		cin>>Choice;
		if(Choice) {
			cout<<"Input the node name (i.e. 1,2,3....) that you want to attach "<<NodeName<<" to :\n";
			int n;
			cin >> n;

			cout<<"Now inserting node "<<key<<"\n";
			SuperInsert(n, NodeName);

		}else return;

	}

	if (available_position(NodeName) == 1){
		cout << "Both left and right position of node "<<NodeName <<" are available,\nplease input left or right of "<<NodeName<<" that you want to insert node "<<key<<" l. left, r. right\n";
		char n;
		cin >> n;

		cout<< "Continue to insert? 1. Yes, 0. No\n";
		int nn;
		cin >>nn;
		if (nn) {
			insert(NodeName, key, n);
			cout <<"Successfully insert "<< key <<endl;
			return;
		} else return;
	}

	if (available_position(NodeName) == 2){
		cout<< "Only left child of "<<NodeName<<" is available, insert node "<< key <<" to left? 1. Yes, 0. No\n";
		int n;
		cin >>n;

		if (n) {
			insert(NodeName, key, 'l');
			cout <<"Successfully inserted "<< key <<"!"<<endl;
			return;
		} else return;
	}

	if (available_position(NodeName) == 3)
	{
		//The node have right child position available
		cout<< "Only right child of "<<NodeName<<" is available, insert node "<< key <<" to right? 1. Yes, 0. No\n";
		int n;
		cin >>n;

		if (n) {
			//cout<<1111111111111<<endl;
			insert(NodeName, key, 'r');
			cout <<"Successfully inserted!"<< key <<endl;
			return;
		} else return;
	}

	if (available_position(NodeName) == 4){
		// The node already have two children
		cout <<"Node "<<NodeName<<" already have two children, if you still want to insert, you must abandon one or give it to other fathers. Continue?\n 1. Yes, 0. No\n";
		int n;
		cin >>n;

		if (n==1) {
			cout <<"Do you want to insert node "<< key<<" into "<<NodeName<<"'s left or right?\n l.left, r.right\n";
			char Pos;
			cin >> Pos;
			string decision;
			Node* PoorChild, *father;
			Node** HH;
			father = findPointer(NodeName);
			if (Pos == 'l') {
				decision  = "left";
				PoorChild = father->left;
				HH = &father->left;
				//cout<<"PoorChild is the node "<<PoorChild->v<<endl;
			}

			if (Pos == 'r') {
				decision  = "right";
				PoorChild = father->right;		
				HH = &father->right;	
			}

			cout <<"Do you want to abandon node " <<NodeName<<"'s "<<decision<<" child (node "<<PoorChild->v<<") or want it to be adopted by another father?\n 1. Abandon, 2.Give to another father\n";

			int nnn;
			cin>>nnn;

			if (nnn == 1){
				//abandon
				erase(PoorChild); // delete the abandoned child
				cout<<"You have just abandoned his "<<decision<<" child\n!";
				insert(PoorChild, key);// insert the new child to the father;
				cout<<"Successfully insert node "<<key<<"!\n";
				return;
			} else if (nnn == 2) {
				
				*HH = NULL;
				insert(*HH, key);
				cout<<"Successfully insert node "<<key<<", you can also attach the poor child to node "<<key<<endl;
				cout<<"Which father do you want the poor child to be adopted by? Input name of the father (i.e. 1,2,3,4....) including node "<< key<<"?\n";
				int NewFather;
				cin>>NewFather;
				SmartAttach(NewFather, PoorChild);
				return;
			}

		} else return;
	}

	else {
		cout<<"Failed to insert!\n";
		return;
	}
	
}

void BinaryTree::SmartAttach(int Father, Node* obj){
	// find Father's avalible position;
	if (available_position(Father) == 0) {
		cout<<"Node "<<Father<<" does not exists!\n";
		return;
	} 
	if (available_position(Father) == 1) {

		cout<<"Both left and right of node " <<Father<<" are avalible, which one do you want?\nl.left, r.right\n";
		char n;
		cin>>n;
		AttachChild(Father,obj,n);
		cout<<"Successfully attached!\n";
		return;
	}
	if (available_position(Father) == 2) {

		cout<<"The left of node " <<Father<<" is avalible, Continue to insert?\n1.Yes, 0.No\n";
		char n;
		cin>>n;
		if(n) AttachChild(Father,obj,'l');
		cout<<"Successfully attached!\n";
		return;

	}
	if (available_position(Father) == 3) {
		//right 
		cout<<"The right of node " <<Father<<" is avalible, Continue to insert?\n1.Yes, 0.No\n";
		char n;
		cin>>n;

		if(n) {
			AttachChild(Father,obj,'r');
			cout<<"Successfully attached!\n";
			return;
		}
		else return;
	}
	if (available_position(Father) == 4) {
		// Neither 
		cout<<"Unable to attach, both left and right child of node"<<Father<<" are not avalible!\n";
		return;
	}
}

/**
 * attach a tree to another tree's node, it is not copy, just link two tree together
 * @param Father   the node that the tree want to attach to
 * @param obj      the tree that is to be attached
 * @param position left of Father or right of Father, 'l' for left, 'r' for right
 */

void BinaryTree::AttachChild(int Father, Node* obj, char position){
	Node *p = findPointer(Father);

	if (position == 'l'){
		p->left = obj;
		return;
	}

	if (position == 'r'){ 
		p->right = obj;
		return;
	}

}


/**
 * @param  k   [description]
 * @param  obj [description]
 * @return     [description]
 */
Node* BinaryTree::findPointer(int k, Node *&obj){

	if (obj == NULL) { 
		//cout <<"NULL argument\n";
		return NULL;
	} else {
		// cout<<"finding "<<obj->v<<endl;
		if (obj->v == k) {
		//cout<<"find!"<<endl;
		// cout<<"findde address value is "<< obj<<endl;
		return obj;
			//return obj;
		} 
		if (findPointer(k, obj->left) == NULL)
		{
			if (findPointer(k, obj->right) == NULL)
		{
			return NULL;
		} else return findPointer(k, obj->right);
		} else return findPointer(k, obj->left);

		} 
	}

Node* BinaryTree::findPointer(int k){
	return findPointer(k,root);
}
	
void BinaryTree::erase(Node* &obj) {
	if (obj != NULL)
	{

		//if (lp != NULL) {

			erase(obj->left);
		//}

		//if (lp != NULL) {
			erase(obj->right);
			delete obj;	
			obj = NULL;
	}
}

void BinaryTree::erase(int NodeName){

	if (!is_element(NodeName))
	{
		cerr<<NodeName<<" is Not a node of the tree!\n";
		return;
	}

	if (root->v == NodeName) {
		erase();
	} else {

		Node *p = findFather(NodeName);
		cout<<"father is :" <<p->v<<endl;

		if (p->left != NULL && p->left->v == NodeName) {
			cout<<"erasing left\n";
			erase(p->left); 
		} else if(p->right != NULL && p->right->v == NodeName){
			cout<<"erasing right\n";
			erase(p->right); 
		} else {
			cout<<"something wrong!\n";
		}
	}
}

void BinaryTree::erase(void){
	erase(root->left);
	erase(root->right);
	//let root NULL
	delete root;
	root = NULL;
}

/**
 * print subtrees from a certain node;
 * @param os stream
 * @param p  pointer that points to the node
 */

void BinaryTree::print(ostream &os, Node *&p) {
	if(p != NULL){
		os << p->v;
		if (p->left!=NULL) os<<": "<<p->left->v;
		else	os<<": NULL";
		if (p->right!=NULL) os<<", "<<p->right->v;
		else 	os<<", NULL";

		os<<endl;
		print(os,p->left);
		print(os,p->right);
	}
}

/**
 * print the whole tree;
 * @param os [description]
 */
void BinaryTree::print(ostream &os) {
	//print subtrees from root;
	if (root == NULL) {
		os<<"NULL tree!\n";
	} else {
	 print(os, root);
	}
}

bool BinaryTree::is_element(int NodeName) {
	if (findPointer(NodeName, root)!=NULL) {
		return true;
	} else {
		return false;
	}
}

/**
 * Determine whether there is avalible position in the node
 * @param  NodeName the Node that waiting for check
 * @return     return 0 if there's no node with name NodeName in the tree
 *                    1 if both the right and left of the node is avalible
 *                    2 if left is available but right is not avalible
 *                    3 if right is available but left is not
 *                    4 if both sides are unavailable;
 *                    5 something is wrong;
 */
int BinaryTree::available_position(int NodeName){
	Node* tmp = findPointer(NodeName, root);
	if(tmp == NULL) {
		return 0;
	} else if (tmp->left == NULL && tmp->right == NULL) {
		return 1;
	} else if (tmp->left == NULL && tmp->right != NULL) {
		return 2;
	} else if (tmp->left != NULL && tmp->right ==NULL) {
		return 3;
	} else if (tmp->left != NULL && tmp->right != NULL) {
		return 4;
	} else {
		return 5;
	}
}


Node * BinaryTree::findFather(int NodeName, Node *start){
	//cout <<"searching "<<start->v<<endl;

	if (start->left == NULL && start->right==NULL)
	{
			return NULL;
	}


	if (start->left != NULL) {
		//cout <<"Justify "<<start->left->v<<endl;
		if (start->left->v == NodeName) {
			//cout<<"find!\n";
			return start;
		}
	}

	if (start->right != NULL) {
		//cout <<"Justify "<<start->right->v<<endl;
		if (start->right->v == NodeName) {
			//cout<<"find!\n";
			return start;
		}
	} 
		
	if (start->right == NULL || findFather(NodeName,start->right) == NULL) {
		if(start->left == NULL || findFather(NodeName,start->left) == NULL){
			return NULL;
		} else {
			//cout<<"--";
			return findFather(NodeName,start->left);
		} 
	} else {
		//cout<<"--";
		return findFather(NodeName, start->right);
	} 

}

/**
 * findFather of a node start from the root
 * @param  NodeName [description]
 * @return          [description]
 */
Node * BinaryTree::findFather(int NodeName) {

	return findFather(NodeName, root);

}

void BinaryTree::SuperErase(int NodeName) {
	bool result = true;

	if (!is_element(NodeName))
	{
		cout<<NodeName<<" is not a element of the tree!\n";
		return;
	}

	if (root->v == NodeName)
	{
		cout<<"Unable to delete the root of the tree! Please try erase()!\n";
		return;
	}

	Node *pos    = findPointer(NodeName);
	int choice, NewFather;
	if (pos->right == NULL && pos->left == NULL) {
		erase(NodeName);
		return;
	}


	Node *father = findFather(NodeName);

	// Delete its father's left or right
	// But this node still exist and was pointed by pos
	if (father->left->v == NodeName)
	{
		//cout<<"Left"<<endl;
		father->left = NULL;
	} else if (father->right->v == NodeName) {
		//cout<<"right"<<endl;
		father->right = NULL;
	}



	if (pos->right != NULL) {
		cout<<"Node "<<NodeName<<" is the father of node "<<pos->right->v<<", do you want to erase all the subtree "<<pos->right->v<<" or give it to another father?\n";
		cout<<"1. delete, 2.give to another father\n";
 
		while(result){
			cin>>choice;
			if (choice == 1) {

				//cout<<"hello!!\n";
				erase(pos->right);
				//cout<<"hello!!\n";
				result = false;
			} else if(choice == 2) {

				cout<<"Which father do you want to give the right child of "<<NodeName<<" to?\n";
				cout<<"Input node name (1,2,3.....)\n";

				cin>>NewFather;

				SmartAttach(NewFather, pos->right);
				pos->right == NULL;
				result = false;
			} else {
				cout<<"Wrong choice!Please re-enter!\n";
				cin.clear();
				cin.ignore();
			}
		}
	}

	result = true;

	if (pos->left != NULL) {
		cout<<"Node "<<NodeName<<" is the father of node "<<pos->left->v<<", do you want to erase all the subtree  "<<pos->left->v<<" or give it to another father?\n";
		cout<<"1. delete, 2.give to another father\n";

		while(result){
			cin>>choice;
			if (choice == 1) {
				erase(pos->left);
				result = false;
			} else if(choice == 2) {

				cout<<"Which father do you want to give the left child of "<<NodeName<<" to?\n";
				cout<<"Input node name (1,2,3.....)\n";

				cin>>NewFather;

				SmartAttach(NewFather, pos->left);
				pos->left == NULL;
				result = false;

			} else {
				cout<<"Wrong choice! Please re-enter!\n";
				cin.clear();
				cin.ignore();
			}
		}
	}


	delete(pos);
	cout<<"Node "<<NodeName<<" deleted!\n";
	return;


}