#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define ALPHABET 10

typedef struct node {
    struct node* children[ALPHABET];
    bool isEnd;
    char *word;
}Node;


Node* createNode();
int getKeypadNumber(char );
void insert(Node*, char*);
void search(Node*, int*, int);


int main(){
	
	Node* root = createNode();
	char *word = (char*)malloc(25*sizeof(char)); 
	bool quit = true;										// exit game
	int num, count, temp;									// digits counter
	int i;
	FILE* file = fopen("dictionary.txt", "r");
	
    if (file == NULL) {
        printf("File does not exist.\n");
        return 0;
    }
      
	while (fgets(word, 100, file) != NULL) {
		
	    int len = strlen(word);
	    if (len > 0 && word[len-1] == '\n') {
	        word[len-1] = '\0'; 						// convert '\n' to '\0'
	    }
	    
	   insert(root, word);	   
	}
	

	fclose(file);

	printf("Enter -1 to exit.");
 	while(quit){
 		
 		printf("\n\nEnter a number:");
		scanf("%d", &num);
		
		if(num == -1){
			quit = false;
		}
		else{
			count = 0;
		    temp = num;
		    
		    while (temp > 0) {
		        temp /= 10;
		        count++;
		    }
		    
			int* digits = (int*)malloc(count*sizeof(int));
		    temp = num;
		    
		    for (i=count-1; i>= 0; i--) {
		        digits[i] = temp % 10;
		        temp /= 10;
		    }	
			search(root, digits, count);	
		}
	}
	
	return 0;
}



Node* createNode() {
	
	int i;
    Node* newNode = (Node*)malloc(sizeof(Node));
    
    newNode->isEnd = false;
    
    for (i=0; i<ALPHABET; i++) {
        newNode->children[i] = NULL;
    }   
    return newNode;
}


int getKeypadNumber(char ch){
		
    if(ch == 'ç' || ch == 'ð' || ch == 'ü' || ch == 'þ'){
    	return 1;
	}
    else if(ch == 'a' || ch == 'b' || ch == 'c' ){
    	return 2;
	}
	else if(ch == 'd' ||ch == 'e'||ch == 'f'){
		return 3;
	}
	else if(ch == 'g' ||ch == 'h' || ch == 'i'){
		return 4;
	}
	else if(ch == 'j' ||ch == 'k' || ch == 'l'){
		return 5;
	}
	else if(ch == 'm' ||ch == 'n' || ch == 'o'){
		return 6;
	}
	else if(ch == 'p' ||ch == 'q' || ch == 'r' || ch == 's'){
		return 7;
	}
   	else if(ch == 't' ||ch == 'u' || ch == 'v'){
		return 8;
	}
	else if(ch == 'w' ||ch == 'x' || ch == 'y' || ch == 'z'){
		return 9;
	}
	else{
		return 0;
	}	
	
}

void insert(Node* root, char* word) { 
	
    Node* current = root;
    int index, i = 0;

    while (current->isEnd || i<strlen(word) ) {				// end of word or have we # node
     		
     	if(current->isEnd && i== strlen(word)){				// # node 
     		index = 0;
     			
		}
		else{												// convert to number
			index = getKeypadNumber(word[i]);	
			
		}
     	
        if (current->children[index] == NULL) {				
        	
            current->children[index] = createNode();       	
            
        }
      		
        current = current->children[index];
        while(current->children[0] != NULL ){				// if the node to be added comes after the tag
        	
			current = current->children[0];
		}
		
        i++;       
    }
  		
    current->isEnd = true;									// end of number represents a word  
    current->word = (char*)malloc((strlen(word) + 1) * sizeof(char));
    strcpy(current->word, word);   
  
}


void search(Node *root, int *arr, int size){
	
	Node *current = root;
	int i=0;
	bool notFound = false;		
	bool control = false;	

	while((!current->isEnd || current->children[0] != NULL || i<size) && !notFound && !control){
	
		if(!current->isEnd && i==size){					// if the number sequence ends before reaching the end of the path	
			control =true;
			printf("\n>>>Word not found.");
			
		}
		else{
			
			if(current->children[0] != NULL){			// if we have # node
							
				if(i==size && current->isEnd){
					
					printf("\n>> %s",  current->word );
				}
				current = current->children[0];
			
			}
			else{
				if(current->children[arr[i]] != NULL){
					current = current->children[arr[i]];
					i++;	
				}
				else{
					printf("\n>>>Word not found.");
					notFound = true;
				}	
			}	
		}
		
	}
	if(!notFound && !control){
		printf("\n>> %s", current->word);
	}
	
}
