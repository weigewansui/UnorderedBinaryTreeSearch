#include "BinaryTree.cpp"

int main() {

cout<<"++++++++++++++++++++++++++Begin Test ++++++++++++++++++++++++++++++++++++\n";
	/**
	 * Create the binary tree
	 * two ways
	 *
	 * 1. Create with parameter;
	 * 2. Create empty tree and insert(int); insert number to the root, return pointer poiting to the first node;
	 * 
	 */
	
	BinaryTree a(2); // create a tree with root node 2
	BinaryTree b;
	Node* pointer = b.insert(6);

	a.print(cout);

	/**
	 * Insert node
	 * 1 . insert(int FatherName, int NewNodeName,  Char Position) insert a new 
	 * node NewNodeName to FatherName with Position 'l' or 'r' indicating left or right
	 *
	 * 2.  insert(Node* &P, int NodeName) if the pointer P is NULL ,then insert NodeName to that node
	 *
	 * These function will flag error if the position is already been taken or the node already exists
	 *
	 * if need to insert node in between two nodes or insert to what ever you want, try SuperInsert() at the end of main.cpp
	 * 
	 * 
	 */
	cout<<"-----test insert()-----------\n";
	cout<<"The left side of 2 is: ";
	if (a.root->left == NULL ) {
		cout<<"NULL"<<endl;
	} else {
		cout<<a.root->left->v<<endl;
	}

	a.insert (2,7,'l');
	cout<<"After calling a.insert (2,7,'l') , the left side of 2 is: "<<a.root->left->v<<endl;

	// build up the whole tree
	a.insert (2,5,'r');

	a.insert (7,3,'l');
	a.insert (7,6,'r');
	a.insert (6,11,'r');
	a.insert (5,9,'r');
	a.insert (9,4,'l');

	//a.print(cout);


	/**
	 * Print the tree
	 * print(ostream&c) print the whole tree
	 *
	 * print(ostream&c, Node* p) print the subtrees of the node pointer p pointing to
	 */
	cout<<"----------test print() whole tree-------\n";
	a.print(cout);
	cout<<"-----------test print() from a node------\n";
	a.print(cout,a.root->left);

	/**
 	* erase(*p) will erase all the subtrees from the node that
 	* p is pointing to
 	* erase(int NodeName); will erase all the subtree of node NodeName
 	* erase(void) will erase the whole tree;
 	* If need to erase a tree and keep it's children, try SuperErase() at the end of main.cpp
 	*/
 	
 	// a.erase();
 	// a.print(cout);

 	cout<<"---------Test erase() erase a subtree 6-----\n";
 	cout<<"Now test erase with erase(int NodeName):\n";
 	cout<<"Erased tree is:\n";
 	a.erase(6);
 	a.print(cout);


 	cout<<"---------Test erase() erase a leaf 4-----\n";
 	cout<<"Erased tree is:\n";
 	a.erase(4);
 	a.print(cout);

 	cout<<"++++++++++++++++++++++++++ End of Test ++++++++++++++++++++++++++++++++++++\n";
 




	return 0; // remove me!!!!!!!!!!!!!!!!!!!!!!


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Some other functions;
 	cout<<"---------restore the tree and test other functions----------\n\n";

 	
	// Here is some other functions
	// 
	

 	/**
 	 * AttachChild (int FatherNode, Node* p, char Position)
 	 *
 	 * Attach a subtree pointing by pointer p to a node FatherNode, with Position 'l' indicating left,
 	 * 'r' indicating right;
 	 *
 	 * It is only attach, NOT copy the node. if b is attached to a, then delete b, the attached node in a will also disappear!!
 	 * 
 	 */
 	

	cout<<"----------test attach a subtree to a node AttachChild()-------------------\n";

 	b.insert(6,11,'r');
 	cout<<"Now tree b is :\n";
 	b.print(cout);

 	cout<<"Now tree a is :\n";
 	a.print(cout);
 	
 	cout<<"Attach b to a's 7 node: \n";
 	a.AttachChild(7,b.root,'r');

 	cout<<"After attaching b to a's 7 node, tree a is: \n";
 	a.print(cout);
 	a.insert(9,4,'l');
	

 	/**
 	 * is_element(int NodeName) test a whether node NodeName is in the tree
 	 * @return bool true or false
 	 */
	cout<<"---------Test is_element(int NodeName)---------------------------------\n";
	if (a.is_element(5))
	{
		cout<<"5 is the is the element of the tree a!\n";
	}
	


	/**
	 * SuperInsert(int FatherNode, int NewNode) can insert any NewNode to any FatherNode, 
	 * no matter it's inside the tree or it's a leaf. No matter fathernode exist or not
	 * @param  FatherNode Insert a new node to the father, father can either exist in the tree or not
	 * @param  NewNode    name of the new node
	 *
	 * it can 1. insert node to a node with two child, attach the abandon child to another node
	 *
	 * 		  2. automatically know which child position of the father is available for insert
	 * 		  3. insert a new node to a non-exit father, first create that father and insert the node
	 */
	
	cout<<"--------Test SuperInsert(int FatherNode, int NewNode)--------\n";
	
	cout<<"Original tree a is: \n";
	a.print(cout);

	cout<<"Trying to insert a new node 20 to a not existing node 30\n";
	a.SuperInsert(30,20);

	cout<<"Now the new tree is: \n";
	a.print(cout);

	/**
	 * It will take care of all kinds of nodes that you want to delete;
	 * @param  NodeName the name of the node that you want to delete;
	 */
	cout<<"---------Test SuperErase(int NodeName)------------------------------\n";

	cout<<"Original tree a is: \n";
	a.print(cout);
	a.SuperErase(7);

	cout<<"After erase 7, now the tree is: \n";
	a.print(cout);


}