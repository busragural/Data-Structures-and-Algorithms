#include<stdio.h>
#include<stdlib.h>
#include<time.h>


typedef struct node{
	int data;
	int newValue;
	struct node* left;
	struct node* right;
}Node;


Node *createTree(int);															// creating a node
Node *insertChild(Node *, int);													// adding new child with comparing
Node *find(Node *, int);														// searching to find the element to delete
Node* findMin(Node*);															// looking at the min values to find the element to delete
Node* deleteChild(Node*, int);													// deletion of the selected element

void treeTraversal(Node *);														// print to screen as root-left-right 			
	
void printHorizontal(Node *, int,int);											// printing like tree
void printTree(Node*,int);														// working together with printHorizontal    -thx geeksforgeeks-							
void printParents(Node*);														// [a] is parent, (a) is child

int isEmpty(int *);																// checking if the stack is empty
int pop(int *, int *);															// pop an element from the stack 
int isFull(int *);																// checking if the stack is full
void push(int *, int, int*, int);												// push an element to the stack 


int main(){
	
	srand(time(NULL));
	int maxWeight, fruitNumber, selected, power, top, random, i, tmp, newNumber;
	Node* root = NULL;
	Node *del =(Node*)malloc(sizeof(Node));
	
	do{
		printf("What is the maximum weight of the fruit?\n");
		scanf("%d", &maxWeight);	
	}while(maxWeight < 0);
	
	do{
		printf("How many fruits will there be on the tree?\n");
		scanf("%d", &fruitNumber);	
	}while(fruitNumber > maxWeight);

	int *arr = (int*)calloc(maxWeight,sizeof(int));        						 //checks that the same element did not come
	
	for(i=0; i<fruitNumber; i++){
		do{
			random = rand()%maxWeight+1;	
		}while(arr[random-1] ==1);
		
		arr[random-1] ++;
		root = insertChild(root, random );
	}
	
	free(arr);
	
	arr = (int*)calloc(fruitNumber,sizeof(int));								//it will be the first basket

	printf("\nThe tree in string form: ");
	treeTraversal(root);
	printf("\n");
	printParents(root);
	printf("\n");
	printTree(root,0);

	top = fruitNumber-1;														// for the stack overflow or underflow 
	
	while(root != NULL){
			
		printf("\nWhich numbered fruit do you want to shoot?\n");
		scanf("%d", &selected);
		
		del = root;
		del = find(del,selected);

		while(del==NULL){
		
			printf("\nInvalid! The selected fruit does not exist. Try again.\n");
			scanf("%d", &selected);	
			del = find(root,selected);
		}

		printf("What's your shooting power?\n");
		scanf("%d", &power);
		
		del->newValue -= power;
		
		if(del->newValue <= 0){													// checks if the fruit will fall from the tree
			
			push(arr, del->data, &top, fruitNumber);							// if it fell, the function throws it into the first basket
			
			root = deleteChild(root, del->data);
			printf("\nThe tree after deletion: \n");
			treeTraversal(root);
			printf("\n");
			printTree(root,0);
			
		}
		else{
			printf("\nThe Original Tree:\n");
			printTree(root,0);													
			printf("\n");
			printf("\nNew Tree:\n");
			printTree(root,1);													
			
		}
		
		printf("\nBasket: ");
		for(i=0; i<fruitNumber; i++){
			if(arr[i] != 0){
				printf("%d ", arr[i]);
			}
		}
		printf("\n");
	
	}
	
	int *stack = (int*)malloc(fruitNumber*sizeof(int));
	
	top = 0;
	
	newNumber = fruitNumber-1;
	while(top < fruitNumber){
		tmp = pop(arr, &top);
		push(stack, tmp, &newNumber, fruitNumber);
	}
	
	printf("\nThe basket after pop: ");
	for(i=0; i<fruitNumber; i++){
		printf("%d ", stack[i]);	
	}
	return 0;
}

Node *createTree(int data){
	
	Node *tree = (Node*)malloc(sizeof(Node));
	tree->data = data;
	tree->newValue = data;
	tree->left = NULL;
	tree->right = NULL;
	
	return tree;
}

Node *insertChild(Node *node, int data){
	
	if(node == NULL){
		return createTree(data);
	}
	if(data < node->data){
		node->left = insertChild(node->left, data);
	}
	else if(data > node->data){
		node->right = insertChild(node->right, data);
	}
	return node;
}

Node *find(Node *node, int data){

	if (node == NULL) {
        return NULL;
    }
    
	if(node->data == data){
		return node; 								
	}
	else if (node->data > data) {
		return find(node->left, data);
	}
	
	else if (node->data < data){
		return find(node->right, data);
	}

	else{
		return node;
	}

}

Node* findMin(Node* tree){
	if(tree && tree->left){
		return findMin(tree->left);
	}
	else{
		return tree;
	}
}


Node* deleteChild(Node* tree, int data){
	if(tree==NULL){
		return NULL;
	}
	
	if(data > tree->data){
		tree->right = deleteChild(tree->right, data);
	}
	
	else if(data < tree->data){
		tree->left = deleteChild(tree->left, data);
	}
	
	else if(tree->left != NULL && tree->right !=NULL){ 
		tree->data = findMin(tree->right)->data;
		tree->right = deleteChild(tree->right, tree->data);
	}
	else{
		tree = (tree->left != NULL) ? tree->left : tree->right;
	}
	return tree;
}

void treeTraversal(Node *tree){         										// root-left-right 		

	if (tree==NULL) {
		return;
	}
	printf("%d\t", tree->data);
	treeTraversal(tree->left);
	treeTraversal(tree->right);
}

void printHorizontal(Node *root, int gap, int reelValue){
	
    if(root != NULL){
	    int i;
	    gap += 3;																// for visuality
	    
	    if(reelValue==0){
	    	printHorizontal(root->right, gap,0);								// a value of 0 prints the first tree 
		}
		else{
			printHorizontal(root->right, gap,1);								// a value of 1 prints the tree that has changed
		}
	    
	    printf("\n");
	    for(i=3; i<gap; i++){
	        printf(" ");
	    }
	    
	    if(reelValue == 0){
	    	printf("%d\n", root->data);	
	    	printHorizontal(root->left, gap,0);
		}
		else{
			printf("%d\n", root->newValue );
			printHorizontal(root->left, gap,1);
		}
    }
    else{
    	return;	
	}
}

void printTree(Node* root, int reelValue){
	if(root == NULL){
		printf("The list is empty.\n");
	}
	if(reelValue == 0){
	   	printHorizontal(root, 0,0);
	}
	else{
		printHorizontal(root, 0,1);
	}
    
}

void printParents(Node* node) {
    if (node == NULL){
   		return;	
	} 
    if (node->left != NULL) {
        printf("[%d] ->", node->data);											// parent
        printf("(%d)", node->left->data);										// child
        if (node->right != NULL) {
            printf("...");
        }
    }
    if (node->right != NULL) {
        printf("[%d] ->", node->data);											// parent
        printf("(%d)", node->right->data);										// child
    }
    printf("\n");
    printParents(node->left);
    printParents(node->right);
}

int isEmpty(int *top){
	
	if(*top == -1){
		return 1;	
	}
	else{
		return 0;
	}
}

int pop(int *arr, int *top){
	
	int data;
	if(!isEmpty(top)){
		data = arr[*top];
		*top +=1;
		return data;
	}
	else{
		printf("empty\n");
		return -1;
	}
}

int isFull(int *top){
	if(*top==-1){
		return 1;
	}
	else{
		return 0;
	}
}

void push(int *arr, int data, int* top,int m){
	
	if(!isFull(top)){
		
		arr[*top] = data;
		*top = *top -1; 
	}
	else{
		printf("Full\n");
	}
}
