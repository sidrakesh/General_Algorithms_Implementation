#include <iostream>
using namespace std;
 
// Structure to represent an interval
struct Interval
{
    int low, high;
};
 
// Structure to represent a node in Interval Search Tree
struct ITNode
{
    Interval *i;  // 'i' could also be a normal variable
    int max;
    ITNode *left, *right, *parent;
};
 
// A utility function to create a new Interval Search Tree Node
ITNode * newNode(Interval i, ITNode* parent)
{
    ITNode *temp = new ITNode;
    temp->i = new Interval(i);
    temp->max = i.high;
    temp->parent = parent;
    temp->left = temp->right = NULL;
};

ITNode *deleteNode(ITNode* root, ITNode* itNode);
bool doOVerlap(Interval i1, Interval i2);
ITNode *intervalNodeSearch(ITNode *root, Interval i);
ITNode *maxNode(ITNode* root);

ITNode *deleteInterval(ITNode* root, Interval i)
{
	ITNode* itNode = intervalNodeSearch(root,i);

	return deleteNode(root, itNode);
}

ITNode *deleteNode(ITNode* root, ITNode* itNode)
{
	if(itNode==NULL)
		return NULL;
	
	if(itNode->left == NULL && itNode->right == NULL) {
		if(itNode->parent->i->low > itNode->i->low) {
			itNode->parent->left = NULL;
		}
		else {
			itNode->parent->right = NULL;
		}
	}
	
	else if(itNode->left == NULL) {
		if(itNode->parent->i->low > itNode->i->low) {
			itNode->parent->left = itNode->right;
			itNode->right->parent = itNode->parent;
		}
		else {
			itNode->parent->right = itNode->right;
			itNode->right->parent = itNode->parent;
		}
	}
	
	else if(itNode->right == NULL) {
		if(itNode->parent->i->low > itNode->i->low) {
			itNode->parent->left = itNode->left;
			itNode->left->parent = itNode->parent;
		}
		else {
			itNode->parent->right = itNode->left;
			itNode->left->parent = itNode->parent;
		}
	}
	
	else {
		itNode->i = itNode->left->i;
		itNode->left = deleteNode(itNode->left, maxNode(itNode->left));
	}
	
	return root;
}

ITNode *maxNode(ITNode* root)
{
	if(root==NULL)
		return NULL;
	
	else if(root->right==NULL)
		return root;
	
	else
		return maxNode(root->right);
}

// A utility function to insert a new Interval Search Tree Node
// This is similar to BST Insert.  Here the low value of interval
// is used tomaintain BST property
ITNode *insert(ITNode *root, Interval i, ITNode* parent)
{
    // Base case: Tree is empty, new node becomes root
    if (root == NULL)
        return newNode(i, parent);
 
    // Get low value of interval at root
    int l = root->i->low;
 
    // If root's low value is smaller, then new interval goes to
    // left subtree
    if (i.low < l)
        root->left = insert(root->left, i, root);
 
    // Else, new node goes to right subtree.
    else
        root->right = insert(root->right, i, root);
 
    // Update the max value of this ancestor if needed
    if (root->max < i.high)
        root->max = i.high;
 
    return root;
}
 
// A utility function to check if given two intervals overlap
bool doOVerlap(Interval i1, Interval i2)
{
    if (i1.low <= i2.high && i2.low <= i1.high)
        return true;
    return false;
}

// The main function that searches a given interval i in a given
// Interval Tree.
ITNode *intervalNodeSearch(ITNode *root, Interval i)
{
	ITNode* itNode;
    // Base Case, tree is empty
    if (root == NULL) return NULL;
 
    // If given interval overlaps with root
    if ((*(root->i)).low == i.low && (*(root->i)).high == i.high)
        return root;
 
    // If left child of root is present and max of left child is
    // greater than or equal to given interval, then i may
    // overlap with an interval is left subtree
    if ((*(root->i)).low > i.low)
        return intervalNodeSearch(root->left, i);
 
    // Else interval can only overlap with right subtree
    return intervalNodeSearch(root->right, i);
}
 
// The main function that searches a given interval i in a given
// Interval Tree.
Interval *intervalSearch(ITNode *root, Interval i)
{
    // Base Case, tree is empty
    if (root == NULL) return NULL;
 
    // If given interval overlaps with root
    if (doOVerlap(*(root->i), i))
        return root->i;
 
    // If left child of root is present and max of left child is
    // greater than or equal to given interval, then i may
    // overlap with an interval is left subtree
    if (root->left != NULL && root->left->max >= i.low)
        return intervalSearch(root->left, i);
 
    // Else interval can only overlap with right subtree
    return intervalSearch(root->right, i);
}
 
void inorder(ITNode *root)
{
    if (root == NULL) return;
 
    inorder(root->left);
 
    cout << "[" << root->i->low << ", " << root->i->high << "]"
         << " max = " << root->max << endl;
 
    inorder(root->right);
}
 
// Driver program to test above functions
int main()
{
    // Let us create interval tree shown in above figure
    Interval ints[] = {{15, 20}, {10, 30}, {17, 19},
        {5, 20}, {12, 15}, {30, 40}
    };
    int n = sizeof(ints)/sizeof(ints[0]);
    ITNode *root = NULL;
    for (int i = 0; i < n; i++)
        root = insert(root, ints[i], NULL);
 
    cout << "Inorder traversal of constructed Interval Tree is\n";
    inorder(root);
 
	deleteInterval(root, ints[2]);
	
	cout << "Inorder traversal of constructed Interval Tree is\n";
    inorder(root);
	
    Interval x = {17, 18};
 
    cout << "\nSearching for interval [" << x.low << "," << x.high << "]";
    Interval *res = intervalSearch(root, x);
    if (res == NULL)
        cout << "\nNo Overlapping Interval";
    else
        cout << "\nOverlaps with [" << res->low << ", " << res->high << "]";
}
