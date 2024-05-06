#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;

class BinarySearchTree
{
private:
	class node
	{
	public:
		node* left;
		node* right;
        node* parent;
		double key;
        string teamName;
        string playerName;

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
    void REVERSE_TREE_WALK(node*);
	node* FIND_MAX(node*);
	node* FIND_MIN(node*);
    void PRINT_MIN();
    void PRINT_MAX();
    node* FIND_NODE(node*,string);
    node* FIND_SUCCESSOR(string);
	void REMOVE_MAX(node*);
	void TREE_DELETE(string);
	void TREE_INSERT(double,string,string);
    int TRIPLE_DOUBLE(string);
};

//This will insert a node into the tree
void BinarySearchTree::TREE_INSERT(double stat,string name, string team)
{
	// This implements the algorithm in page 261 of the textbook
	node* z = new node();
	z->key = stat;
    z->playerName = name;
    z->teamName = team;
	z->left = NULL;
	z->right = NULL;

	node* y = NULL;
	node* x = root;
	node* parent = NULL;

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

BinarySearchTree::node* BinarySearchTree::FIND_MIN(node* x)
{
	while(x->left != NULL)
	{
		x = x->left;
	}
	return x;
}

BinarySearchTree::node* BinarySearchTree::FIND_MAX(node* x)
{
	while(x->right != NULL)
	{
		x = x->right;
	}
	return x;
}

void BinarySearchTree::PRINT_MAX()
{
    node* maxi = FIND_MAX(root);
    cout<< " " << maxi->key<< " " << maxi->playerName << " (" << maxi->teamName<< ")"<<endl;
}

void BinarySearchTree::PRINT_MIN()
{
    node* mini = FIND_MIN(root);
    cout<< " " << mini->key<< " " << mini->playerName << " (" << mini->teamName<< ")"<<endl;
}

BinarySearchTree::node* BinarySearchTree::FIND_NODE(node* x, string name)
{
	if(x->playerName == name)
	{
		return x;
	}
	if(x != NULL)
	{
		if (x->left) FIND_NODE(x->left,name);
		if (x->right) FIND_NODE(x->right,name);
	}
}

BinarySearchTree::node* BinarySearchTree::FIND_SUCCESSOR(string name)
{
	node* x = FIND_NODE(root,name);
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
int BinarySearchTree::TRIPLE_DOUBLE(string name)
{
    node* x = FIND_NODE(root,name);
    if(x->key >= 10)
    {
        return 1;
    }
    return 0;
}

void BinarySearchTree::REVERSE_TREE_WALK(node* x)
{
    if(x != NULL)
    {
        if(x->right) REVERSE_TREE_WALK(x->right);
        cout<< " " << x->key << " " << x->playerName << " (" << x->teamName <<")"<<endl;
        if(x->left) REVERSE_TREE_WALK(x->left); 
    }
}

void BinarySearchTree::TREE_DELETE(string name)
{
    node* x;
	node* y;
	node* z = FIND_NODE(root,name);
    if(z == NULL)
    {
        cout<< "This player does not exist.";
        return;
    }
	if(z->left == NULL || z->right == NULL)
	{
		y = z;
	}
	else
	{
		y = FIND_SUCCESSOR(name);
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


class Points : public BinarySearchTree
{
    public:
    Points()
    {
        root = NULL;
    }
};

int main(){
    BinarySearchTree pointsBST,assistsBST,reboundsBST;
	int choice,i;
    double points,assists,rebounds;
    string name;
    string team;
    string names[256];
    int count = 0;

	while (true)
	{
		cout << endl << endl;
		cout << " Binary Search Tree Example " << endl;
		cout << " ----------------------------- " << endl;
		cout << " 1. Add Player " << endl;
		cout << " 2. Delete Player " << endl;
		cout << " 3. Display Highest Player " << endl;
		cout << " 4. Display Lowest Player " << endl;
		cout << " 5. List Players w/ Triple Doubles "<< endl;
		cout << " 6. Display All Ranks "<<endl;
		cout << " ?. Exit " << endl;
		cout << " Enter your choice : ";
		cin >> choice;
		switch (choice)
		{
		case 1: cout<<" Insertion "<<endl;
            cout<<" -------------------"<<endl;
            cout<<"Please enter the player's name: ";
            cin.ignore();
            getline(cin,name);
            cout<<"Please enter the player's team: ";
            getline(cin,team);
            cout<<"Enter points per game: ";
            cin >> points;
            cout<<"Enter assists per game: ";
            cin >> assists;
            cout<<"Enter rebounds per game: ";
            cin >> rebounds;
            names[count] = name;
            count++;
			pointsBST.TREE_INSERT(points,name,team);
            assistsBST.TREE_INSERT(assists,name,team);
            reboundsBST.TREE_INSERT(rebounds,name,team);
			break;
        case 2:
        cout << " Delete a Player "<<endl;
        cout<<" -------------------"<<endl;
        cout<<" Enter the player's name you want to remove: ";
        cin.ignore();
        getline(cin,name);
        pointsBST.TREE_DELETE(name);
        assistsBST.TREE_DELETE(name);
        reboundsBST.TREE_DELETE(name);
        case 3:
        cout<< " Display Highest Player "<<endl;
        cout<<" -------------------"<<endl;
        cout<< " Highest Points Per Game: "<<endl;
        pointsBST.PRINT_MAX();
        cout<<" Highest Assists Per Game: "<<endl;
        assistsBST.PRINT_MAX();
        cout<<" Highest Rebounds Per Game: "<<endl;
        reboundsBST.PRINT_MAX();
        break;
        case 4:
        cout<< " Display Lowest Player "<<endl;
        cout<<" -------------------"<<endl;
        cout<< " Lowest Points Per Game: "<<endl;
        pointsBST.PRINT_MIN();
        cout<< " Lowest Assists Per Game: "<<endl;
        assistsBST.PRINT_MIN();
        cout<<" Lowest Rebounds Per Game: "<<endl;
        reboundsBST.PRINT_MIN();
        break;
        case 5:
        cout<< " List Triple Doubles "<<endl;
        cout<<" -------------------"<<endl;
        cout<<"Players w/ Triple Doubles: "<<endl;
        for(i = 0; i <= count; i++)
        {
            cout<<names[i];
            if(pointsBST.TRIPLE_DOUBLE(names[i]) && assistsBST.TRIPLE_DOUBLE(names[i]) && reboundsBST.TRIPLE_DOUBLE(names[i]))
            {
                cout<<names[i]<<endl;
            }
            }
        break;
        case 6:
            cout << " Display Rankings "<<endl;
            cout<<" -------------------"<<endl;
            cout<<" Points Per Game"<<endl;
            pointsBST.REVERSE_TREE_WALK(pointsBST.root);
            cout<<" Assists Per Game"<<endl;;
            assistsBST.REVERSE_TREE_WALK(assistsBST.root);
            cout<<" Rebounds Per Game"<<endl;;
            reboundsBST.REVERSE_TREE_WALK(reboundsBST.root);
            break;
		default:
			cout << "Invalid choice";
		}
	}

}
//For the triple doubles, there are two ways I think of doing this, when we add a player we need to add their points, rebounds, and assists
//Therefore, we know there that for every player in points/rebounds/assists, they will exist in the other trees too. Therefore,
//We can do a DFS search and then using that player name we can search them in the other lists to see if they have rebounds/assists
//greater than 10, if they do then we can add them to the triple double list.
//So for every player in points BST we will check if they have more than 10 points if they dont we move on, if they do then we check
//For their rebounds and assists.