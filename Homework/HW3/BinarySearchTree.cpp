#include <iostream>
#include <cstdlib>
using namespace std;

class BinarySearchTree
{
private:
	class node
	{
	public:
		node* left;
		node* right;
		int key;
		string data;
		node* parent;
	};

	
public:
	node* root;
	BinarySearchTree()
	{
		root = NULL;
	}
	bool isEmpty() const { return root == NULL; }
	void INORDER_TREE_WALK(node*);
	void PREORDER_TREE_WALK(node*);
	void POSTORDER_TREE_WALK(node*);
	void FIND_MAX(node*);
	node* FIND_MIN(node*);
	void REMOVE_MAX(node*);
	node* FIND_SUCCESSOR(int);
	void TREE_DELETE(int);
	void TREE_INSERT(int );
	node* FIND_NODE(node*,int);
	void PRINT_SUCCESSOR(int);

};

void BinarySearchTree::TREE_INSERT(int d)
{
	// This implements the algorithm in page 261 of the textbook
	node* z = new node();
	z->key = d;
	z->left = NULL;
	z->right = NULL;

	node* y = NULL;
	node* x = root;
	//node* parent = NULL;

	while (x != NULL)
	{
		y = x;
		if (z->key < x->key)
			x = x->left;
		else
			x = x->right;
	}

	z->parent = y;
	if (y == NULL)
		root = z;
	else if (z->key < y->key)
		y->left = z;
	else
		y->right = z;
		
}
//INORDER: left->root->right
void BinarySearchTree::INORDER_TREE_WALK(node* x)
{
	if (x != NULL)
	{
		if (x->left) INORDER_TREE_WALK(x->left);
		cout << " " << x->key << " ";
		if (x->right) INORDER_TREE_WALK(x->right);
	}
	

}
//PREORDER: root->left->right
void BinarySearchTree::PREORDER_TREE_WALK(node* x)
{
	if (x != NULL)
	{
		cout << " " << x->key << " ";
		if (x->left) PREORDER_TREE_WALK(x->left);
		if (x->right) PREORDER_TREE_WALK(x->right);
	}
}
//POSTORDER: left->right->root
void BinarySearchTree::POSTORDER_TREE_WALK(node* x)
{
	if (x->left) POSTORDER_TREE_WALK(x->left);
	if (x->right) POSTORDER_TREE_WALK(x->right);
	cout << " " << x->key << " ";
}
//Find the maximum value of the Binary Search Tree
void BinarySearchTree::FIND_MAX(node* x)
{
	while(x->right != NULL)
	{
		x = x->right;
	}
	cout<<"The maximum value of the BST is: " << x->key <<endl;
}
BinarySearchTree::node* BinarySearchTree::FIND_MIN(node* x)
{
	while(x->left != NULL)
	{
		x = x->left;
	}
	return x;
}

BinarySearchTree::node* BinarySearchTree::FIND_NODE(node* x, int k)
{
	if(x->key == k)
	{
		return x;
	}
	if(x != NULL)
	{
		if (x->left) FIND_NODE(x->left,k);
		if (x->right) FIND_NODE(x->right,k);
	}
}
//Remove the maximum value from the tree
void BinarySearchTree::REMOVE_MAX(node* x)
{
	if(x->right == NULL)
	{
		cout<<"The maximum value "<<x->key << " was removed"<<endl;
		root = NULL;
		return;
	}
	while(x->right->right != NULL)
	{
		x = x->right;
	}
	cout<<"The maximum value "<< x->right->key << " was removed"<<endl;
	x->right = NULL;
}
BinarySearchTree::node* BinarySearchTree::FIND_SUCCESSOR(int k)
{
	node* x = FIND_NODE(root,k);
	node* y;
	node* ans;
	if(x->right != NULL)
	{
		return FIND_MIN(x->right);
	}
	else
	{
		y = x->parent;
		while(y != NULL && x == y->right)
		{
			x = y;
			y = y->parent;
		}
		return y;
	}
}
void BinarySearchTree::PRINT_SUCCESSOR(int k)
{
	node* x = FIND_NODE(root,k);
	node* y;
	node* ans;
	if(x->right != NULL)
	{
		ans = FIND_MIN(x->right);
		cout<<" The successor of the node is: "<<ans->key<<endl;
	}
	else
	{
		y = x->parent;
		while(y != NULL && x == y->right)
		{
			x = y;
			y = y->parent;
		}
		cout<<" The successor of the node is: "<<y->key<<endl;
	}
}

void BinarySearchTree::TREE_DELETE(int k)
{
	node* x;
	node* y;
	node* z = FIND_NODE(root,k);
	if(z->left == NULL || z->right == NULL)
	{
		y = z;
	}
	else
	{
		y = FIND_SUCCESSOR(k);
	}
	if(y->left != NULL)
	{
		x = y->left;
	}
	else
	{
		x = y->right;
	}
	if(x != NULL)
	{
		x->parent = y->parent;
	}
	if(y->parent == NULL)
	{
		root = x;
	}
	else
	{
		if(y == y->parent->left)
		{
			y->parent->left = x;
		}
		else
		{
			y->parent->right = x;
		}
	}
	if(y != z)
	{
		z->key = y->key;
	}
}
int main()
{
	BinarySearchTree bst;
	int choice, key;
	int temp,successor;
	while (true)
	{
		cout << endl << endl;
		cout << " Binary Search Tree Example " << endl;
		cout << " ----------------------------- " << endl;
		cout << " 1. Insertion " << endl;
		cout << " 2. Pre-Order Traversal " << endl;
		cout << " 3. Post-Order Traversal " << endl;
		cout << " 4. In-Order Traversal " << endl;
		cout << " 5. Find Max "<< endl;
		cout << " 6. Remove Max "<<endl;
		cout << " 7. Successor "<<endl;
		cout << " 8. Delete Node"<<endl;
		cout << " 9. Exit " << endl;
		cout << " Enter your choice : ";
		cin >> choice;
		switch (choice)
		{
		case 1: cout << " Enter key (int value) to be inserted : ";
			cin >> key;
			bst.TREE_INSERT(key);
			break;
		case 2: cout<< endl;
			cout << "Pre-Order Traversal " << endl;
			cout << " -------------------" << endl;
			bst.PREORDER_TREE_WALK(bst.root);
			break;
		case 3: cout<< endl;
			cout << "Post-Order Traversal " << endl;
			cout << " -------------------" << endl;
			bst.POSTORDER_TREE_WALK(bst.root);
			break;
		case 4: cout << endl;
			cout << " In-Order Traversal " << endl;
			cout << " -------------------" << endl;
			bst.INORDER_TREE_WALK(bst.root);
			break;
		case 5: cout << endl;
			cout << " Find Max " << endl;
			cout << " -------------------" << endl;
			bst.FIND_MAX(bst.root);
			break;
		case 6: cout << endl;
			cout << " Remove Max " << endl;
			cout << " -------------------" << endl;
			bst.REMOVE_MAX(bst.root);
			break;
		case 7: cout << endl;
			cout << " Find Successor " << endl;
			cout << " -------------------" << endl;
			cout << " Find the successor of node: ";
			cin >> temp;
			bst.PRINT_SUCCESSOR(temp);
			break;
		case 8: cout << endl;
			cout << " Delete a Node " << endl;
			cout << " -------------------" << endl;
			cout << " What node would you like to delete?: ";
			cin >> temp;
			bst.TREE_DELETE(temp);
			break;	
		case 9: system("pause");
			return 0;
			break;
		default:
			cout << "Invalid choice";
		}
	}
}
