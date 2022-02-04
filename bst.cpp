#include <iostream>
using namespace std;

struct node {
	int data;
	struct node* left;
	struct node* right;
};

struct node* newNode(int data_){
	struct node* anode = new struct node;
	anode->data = data_;
	anode->left = NULL;
	anode->right = NULL;
	return (anode);
}

void insert(struct node** rootRef, int data_){
	if(*rootRef == NULL){
		*rootRef = newNode(data_);
	}else{
		if(data_ <= (*rootRef)->data)
			insert( &((*rootRef)->left), data_);
		else{
			insert( &((*rootRef)->right), data_);
		}
	}
}

void printTreeInOrder(struct node* root){
	if(root == NULL) return;
	printTreeInOrder(root->left);
	cout << root->data << " ";
	printTreeInOrder(root->right);
}


int countNodes(struct node* root){
	//int count = 0; 
	if(root == NULL) return 0;
	else{	
		return (countNodes(root->left) + countNodes(root->right) + 1);
	}
}

int treeHeight(struct node* root){
	//int count = 0; 
	if(root == NULL) return 0;
	else{	
		return max(treeHeight(root->left), treeHeight(root->right) + 1);
	}
}
	
void printTreePreOrder(struct node* root){
	if(root == NULL) return;
	cout << root->data << " ";
	printTreeInOrder(root->left);
	printTreeInOrder(root->right);

}
void printTreePostOrder(struct node* root){
	if(root == NULL) return;
	printTreeInOrder(root->left);
	printTreeInOrder(root->right);
	cout << root->data << " ";
}

struct node* minValueNode(struct node* root){
	struct node* anode = root;
	while(anode->left != NULL){
		anode = anode->left;
	}

	return (anode);
}

struct node* maxValueNode(struct node* root){
	struct node* anode = root;
	while(anode->right != NULL){
		anode = anode->right;
	}
	return (anode);
}
//
struct node* lookupAddress(struct node* root, int target){
	if(root == NULL)
		return NULL;
	if(root->data == target){ 
		return root;
	}else if(target < root->data){
		return lookupAddress(root->left, target);
	}else{
		return lookupAddress(root->right, target);;
	}

}

struct node* deleteNode(struct node* root, int target)
{
    if (root == NULL)
        return root;
    if (target < root->data)
        root->left = deleteNode(root->left, target);
    else if (target > root->data)
        root->right = deleteNode(root->right, target);
    else {
        if (root->left==NULL and root->right==NULL)
            return NULL;
        else if (root->left == NULL) {
            struct node* current = root->right;
            free(root);
            return current;
        }
        else if (root->right == NULL) {
            struct node* current = root->left;
            free(root);
            return current;
        }
        struct node* current = minValueNode(root->right);
 
        root->data = current->data;
        root->right = deleteNode(root->right, current->data);
    }
    return root;
}

void DeleteAll(struct node** headRef) {
	struct node* current = *headRef; 	
	struct node* next;
		while (current != NULL) {
			next = current->next;
			free(current); 
			current = next; 
		}
    *headRef = NULL; 
}
 
void kthsBiggestHelper(struct node* root, int k, int& counter){

	if(root == NULL || counter >= k) return;

	kthsBiggestHelper(root->right,  k, counter);

	counter = counter + 1;
	if(k == counter) {
		cout << k<< "th biggest value: " << root->data << endl;
		return;
	}

	kthsBiggestHelper(root->left,  k, counter);

}

void kthBiggest(struct node* root, int k){
	int counter = 0;
	kthsBiggestHelper(root,  k, counter);

	return;
}

int findMinDifference(struct node* root) {
	
	int min= minValueNode(root)->data;
	int max = maxValueNode(root)->data; 
	int diff = max - min; 
	
    return diff;
}



bool isBST(struct node* root, struct node* min, struct node* max){
        if(root==NULL) return true;
        if(min!=NULL and root->data <= min->data) return false;
        if(max!=NULL and root->data >= max->data) return false;
        bool leftCheck = isBST(root->left, min, root);
        bool rightCheck = isBST(root->right, root, max);
        return leftCheck && rightCheck;
    }
    
    bool isValidBST(struct node* root) {
        return isBST(root, NULL, NULL);
    }

    int main() {
	    int val;
	    struct node* root = NULL;
	
	insert(&root, 70);
	insert(&root, 60);
	insert(&root, 80);
	insert(&root, 5);
	insert(&root, 95);
	insert(&root, 20);
	
	struct node* min = minValueNode(root);
	struct node* max = maxValueNode(root);
	
	
	cout<< "Max:" <<findMinDifference(root)<<endl;
	cout<< "BST(In Order): " ;
	printTreeInOrder(root);

	cout<< "\nTotal number of nodes: " << countNodes(root);

	cout<< "\nHeight of the tree: " << treeHeight(root); 

	cout<< "\nIn Pre Order Traversal: "; 
	printTreePreOrder(root);

	cout<< "\nIn Post Order Traversal: ";
	printTreePostOrder(root);

	cout << "\nEnter value to delete: ";
	cin >> val; 
	deleteNode(root, val);

	cout<< "BST After Deletion: " ;
	printTreeInOrder(root);

	if (isValidBST){
		cout << "\nTree is a BST" << endl;
	}

	cout << "Enter value to search address: ";
	cin >> val; 

	cout<< "Address for "<< val << " is: " ;
	cout<< lookupAddress(root, val);

	cout<< "\nMinimum absolute difference: ";
	cout<< findMinDifference(root);

	cout << "\nEnter K value for kth biggest: ";
	cin >> val; 
	kthBiggest(root, val);

	DeleteAll(&root);

	return 0;
}
