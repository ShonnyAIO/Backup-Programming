#include<bits/stdc++.h>
using namespace std;

#ifdef DEBUG 
#define D_LOG(x) x
#else 
#define D_LOG(x)
#endif

// K-d Tree borrowed from http://www.geeksforgeeks.org/k-dimensional-tree/

const int k = 2;

// A structure to represent node of kd tree
struct Node
{
		int point[k]; // To store k dimensional point
		Node *left, *right;
};
 
// A method to create a node of K D tree
struct Node* newNode(int arr[])
{
		struct Node* temp = new Node;
 
		for (int i=0; i<k; i++)
			 temp->point[i] = arr[i];
 
		temp->left = temp->right = NULL;
		return temp;
}
 
// Inserts a new node and returns root of modified tree
// The parameter depth is used to decide axis of comparison
Node *insertRec(Node *root, int point[], unsigned depth)
{
		// Tree is empty?
		if (root == NULL)
			 return newNode(point);
 
		// Calculate current dimension (cd) of comparison
		unsigned cd = depth % k;
 
		// Compare the new point with root on current dimension 'cd'
		// and decide the left or right subtree
		if (point[cd] < (root->point[cd]))
				root->left	= insertRec(root->left, point, depth + 1);
		else
				root->right = insertRec(root->right, point, depth + 1);
 
		return root;
}
 
// Function to insert a new point with given point in
// KD Tree and return new root. It mainly uses above recursive
// function "insertRec()"
Node* insert(Node *root, int point[])
{
		return insertRec(root, point, 0);
}

// A utility function to find minimum of three integers
Node *minNode(Node *x, Node *y, Node *z, int d)
{
		Node *res = x;
		if (y != NULL && y->point[d] < res->point[d])
			 res = y;
		if (z != NULL && z->point[d] < res->point[d])
			 res = z;
		return res;
}

// Recursively finds minimum of d'th dimension in KD tree
// The parameter depth is used to determine current axis.
Node *findMinRec(Node* root, int d, unsigned depth)
{
		// Base cases
		if (root == NULL)
				return NULL;
 
		// Current dimension is computed using current depth and total
		// dimensions (k)
		unsigned cd = depth % k;
 
		// Compare point with root with respect to cd (Current dimension)
		if (cd == d)
		{
				if (root->left == NULL)
						return root;
				return findMinRec(root->left, d, depth+1);
		}
 
		// If current dimension is different then minimum can be anywhere
		// in this subtree
		return minNode(root,
							 findMinRec(root->left, d, depth+1),
							 findMinRec(root->right, d, depth+1), d);
}
 
// A wrapper over findMinRec(). Returns minimum of d'th dimension
Node *findMin(Node* root, int d)
{
		// Pass current level or depth as 0
		return findMinRec(root, d, 0);
}
 
// A utility method to determine if two Points are same
// in K Dimensional space
bool arePointsSame(int point1[], int point2[])
{
		// Compare individual pointinate values
		for (int i = 0; i < k; ++i)
				if (point1[i] != point2[i])
						return false;
 
		return true;
}
 
// Copies point p2 to p1
void copyPoint(int p1[], int p2[])
{
	 for (int i=0; i<k; i++)
			 p1[i] = p2[i];
}

// Function to delete a given point 'point[]' from tree with root
// as 'root'.	depth is current depth and passed as 0 initially.
// Returns root of the modified tree.
Node *deleteNodeRec(Node *root, int point[], int depth)
{
	D_LOG(cout<<"deleteNodeRec depth="<<depth<<endl;)
		// Given point is not present
		if (root == NULL)
				return NULL;
 
		// Find dimension of current node
		int cd = depth % k;
 
		// If the point to be deleted is present at root
		if (arePointsSame(root->point, point))
		{
				// if (root->right == NULL && root->left == NULL) {
				//		 delete root;
				//		 return NULL;
				// }

				// Node *rmin = root->right != NULL ? findMinRec(root->right, cd, depth + 1) : NULL;
				// Node *lmin = root->left != NULL ? findMinRec(root->left, cd, depth + 1) : NULL;
				// Node *min;
				
				// if (rmin != NULL && lmin != NULL) {
				//		 if (rmin->point[cd] < lmin->point[cd]) {
				//				 copyPoint(root->point, rmin->point);
				//				 root->right = deleteNodeRec(root->right, rmin->point, depth+1);
				//		 } else {
				//				 copyPoint(root->point, lmin->point);
				//				 root->left = deleteNodeRec(root->left, lmin->point, depth+1);
				//		 }
				// } else if (rmin != NULL) {
				//		 copyPoint(root->point, rmin->point);
				//		 root->right = deleteNodeRec(root->right, rmin->point, depth+1);
				// } else if (lmin != NULL) {
				//		 copyPoint(root->point, lmin->point);
				//		 root->left = deleteNodeRec(root->left, lmin->point, depth+1);
				// }

				// 2.b) If right child is not NULL
				if (root->right != NULL)
				{
						// Find minimum of root's dimension in right subtree
						Node *min = findMinRec(root->right, cd, depth + 1);
 
						// Copy the minimum to root
						copyPoint(root->point, min->point);
 
						// Recursively delete the minimum
						root->right = deleteNodeRec(root->right, min->point, depth+1);
				}
				else if (root->left != NULL) // same as above
				{
						Node *min = findMinRec(root->left, cd, depth + 1);
						copyPoint(root->point, min->point);
						root->right = deleteNodeRec(root->left, min->point, depth+1);
						root->left = NULL;

				}
				else // If node to be deleted is leaf node
				{
						delete root;
						return NULL;
				}
				return root;
		}
 
		// 2) If current node doesn't contain point, search downward
		if (point[cd] < root->point[cd])
				root->left = deleteNodeRec(root->left, point, depth+1);
		else
				root->right = deleteNodeRec(root->right, point, depth+1);
		return root;
}
 
// Function to delete a given point from K D Tree with 'root'
 Node* deleteNode(Node *root, int point[])
{
	D_LOG(cout<<"deleteNode point.t="<<point[0]<<", point.m="<<point[1]<<endl;)
	 // Pass depth as 0
	 return deleteNodeRec(root, point, 0);
}

deque<Node *> found;

int countDelete(Node *root, int t, int m, int depth) {
	// Find dimension of current node
		int cd = depth % k;
		D_LOG(cout<<"depth="<<depth<<endl;)
		D_LOG(cout<<"root, t="<<root->point[0]<<", m="<<root->point[1]<<endl;)
		if (cd == 0) {
			D_LOG(cout<<"thickness"<<endl;)
			D_LOG(cout<<"point.t="<<root->point[0]<<endl;)
			// thickness
			if (root->point[0] > t) {
				if (root->left == NULL) {
					D_LOG(cout<<"t is too big, no smaller children."<<endl;)
					return 0;
				} else {
					D_LOG(cout<<"t is too big, check smaller children."<<endl;)
					return countDelete(root->left, t, m, depth+1);
				}
			} else {
				int v = 0;
				if (root->point[1] >= m) {
					v++;
					found.push_front(root);
				}
				D_LOG(cout<<"t is fine, is m?"<<v<<endl;)
				if (root->left != NULL) {
					v += countDelete(root->left, t, m, depth+1);
				}
				if (root->right != NULL) {
					v += countDelete(root->right, t, m, depth+1);	
				}
				return v;
			}
		} else {
			D_LOG(cout<<"mass"<<endl);
			D_LOG(cout<<"point.m="<<root->point[1]<<endl;)
			// mass
			if (root->point[1] < m) {
				if (root->right == NULL) {
					D_LOG(cout<<"m is too small, no bigger children."<<endl;)
					return 0;
				} else {
					D_LOG(cout<<"m is too small, check bigger children."<<endl;)
					return countDelete(root->right, t, m, depth+1);
				}
			} else {
				int v = 0;
				if (root->point[0] <= t) {
					v++;
					found.push_front(root);
				}
				D_LOG(cout<<"m is fine, is t?"<<v<<endl;)
				if (root->left != NULL) {
					v += countDelete(root->left, t, m, depth+1);
				}
				if (root->right != NULL) {
					v += countDelete(root->right, t, m, depth+1);	
				}
				return v;
			}
		}
}

int main()
{
	struct Node *root = NULL;
	int slot_count; cin>>slot_count;
	vector<pair<int,int>> slots,coins;
	long int result = 0;
	int t, m;
	for(int i = 0; i < slot_count; ++i) {
		cin>>t; cin>>m;
		slots.push_back(make_pair(t,m));
	}
	int coin_count; cin>>coin_count;
	for(int j = 0; j < coin_count; ++j) {
		cin>>t; cin>>m; coins.emplace_back(t,m);
	}
	random_shuffle(coins.begin(),coins.end());
	for (auto const &i: coins){
		int point[2] = {i.first,i.second};
		root = insert(root, point);
	}
		//printtree(root, true);
	D_LOG(cout<<"slots="<<slot_count<<", coins="<<coin_count<<endl;)
	int dist = 1;
	for(auto it = slots.begin(); coin_count > 0 && it != slots.end(); it++, dist++) {
		found.clear();
		D_LOG(cout<<"slot: t="<<it->first<<", m="<<it->second<<endl;)

		countDelete(root, it->first, it->second, 0);
		result = result + (found.size() * dist);
		// try to find the members of the tree that are c(t) <= s(t) and c(m) >= s(m)
		D_LOG(cout<<"removals "<<found.size()<<", result="<<result<<endl;)

				static int vv[100000][2]; int vvn=0;
				for(auto it=found.begin(); it != found.end(); it++) {
						copyPoint(vv[vvn++],(*it)->point);
						//cerr<<"DELETE: "<<(*it)->point[0]<<" "<<(*it)->point[1]<<endl;
				}
		for(auto it=found.begin(); it != found.end(); it++) {
						root = deleteNodeRec(root, vv[--vvn], 0);
			//root = deleteNode(root, (*it)->point);
			coin_count--;
		}
	}
	cout<<result<<endl;
	assert(coin_count==0);
}
