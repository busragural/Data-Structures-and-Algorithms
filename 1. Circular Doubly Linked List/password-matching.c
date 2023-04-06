#include<stdio.h>
#include<time.h>
#include <stdlib.h>


typedef struct node {
    int data;
    struct node* next;
    struct node* prev;
}Node;

int getRandom(int);
void createWheel(Node **, int *, int, int, int,int);  // it generates three wheels with just one common number in different positions and random numbers from 1-N
void printList(Node *);
void findCommonNum(Node *, Node *, Node *);			  // finding common number with position by comparing three lists
//void findCommonNum(Node *, int);					  // finding common number and position by comparing list with common number variable
void putCommonNum(Node **, int, int);			 	  // adding the common number after the wheel is created
void turnWheel(Node *, Node *, int, int);			  // spins the wheel in the shortest direction to decrypt

int main(){
	
	srand(time(NULL));

	int n,m,i, common;
	int position_1 =NULL, position_2=NULL, position_3 =NULL;
		
	Node *wheel_1 = NULL;
	Node *wheel_2 = NULL;
	Node *wheel_3 = NULL;
	
	printf("How many values will the wheel consist of? (M)\nValue:");
	scanf("%d", &m);
	
	if(m < 3) {
		do{
			printf("Invalid value! Please re-enter.\nValue:");
			scanf("%d", &m);
		}while(m <3);
	}
	
	printf("What value will the wheel get from 1 to? (N)\nValue:");
	scanf("%d", &n);
	
	if(n <= (2*m)-1){
		do{
			printf("Invalid value! Please re-enter.\nValue:");
			scanf("%d", &n);
		}while(n <= (2*m)-1);
	}
	
	int *arr = (int*)malloc(n*sizeof(int));

	for(i=0; i<n; i++){				//to be able to control, reset the sequence of numbers from 1 to N	
		arr[i] = 0;
	}
	
	common = getRandom(n);  
	
	while(position_1 == position_2 || position_1 == position_3 || position_2 == position_3){
        position_1 = getRandom(m)-1;
        position_2 = getRandom(m)-1;
        position_3 = getRandom(m)-1;
    }
	
	createWheel(&wheel_1, arr, n, m, common,position_1);
	createWheel(&wheel_2, arr, n, m, common,position_2);
	createWheel(&wheel_3, arr, n, m, common,position_3);
	printf("\n1. Wheel\t");
	printList(wheel_1);
	printf("\n2. Wheel\t");
	printList(wheel_2);
	printf("\n3. Wheel\t");
	printList(wheel_3);
	
	findCommonNum(wheel_1,wheel_2,wheel_3);

	printf("\n\n\nTHE PASSWORD\n");
	printList(wheel_1);
	turnWheel(wheel_1, wheel_2, common, m);
	turnWheel(wheel_1, wheel_3, common, m);
	
	return 0;
}

void turnWheel(Node *wheel_1, Node *wheel_2, int common,int m){
	int steps,i, position1=1, position2=1;
	Node *temp;
	Node *current = wheel_1;
	while(current->data != common){
		current = current->next;
		position1++;
	}
	
	current = wheel_2;
	while(current->data != common){
		current = current->next;
		position2++;
	}
	
    int dist = (position2 >= position1) ? position2 - position1 : m - (position1 - position2);  //turns the wheel to the right or left by the difference between the positions
    
     if (dist <= m / 2) {
        printf("\nRotate the  wheel counterclockwise (left) %d steps.\n", dist);
        current = wheel_2;
        for(i=0; i<dist; i++){
        	current = current->next;
		}
		temp = current;
	    do {
	        printf("%d\t", temp->data);
	        temp = temp->next;
	    } while (temp != current); 
    } 
	else {
        printf("\nRotate the  wheel clockwise (right) %d steps.\n", m - dist);
        current = wheel_2;
        for(i=0; i<(m - dist); i++){
        	current = current->prev;
		}
		temp = current;
	    do {
	        printf("%d\t", temp->data);
	        temp = temp->next;
	    } while (temp != current); 
    }
}

//void findCommonNum(Node *wheel, int common){
//	
//	Node *current = wheel;
//	int position = 1;
//	while(current->data != common){
//		current = current->next;
//		position++;
//	}
//	printf("\nCommon number:%d\nPosition:%d", common, position);
//}

void findCommonNum(Node *wheel_1, Node *wheel_2, Node *wheel_3){		//three whiles are needed as three wheels are being compared
	Node *current = wheel_1;
	Node *current2 = wheel_2;
	Node *current3 = wheel_3;
	int flag=1;
	int count1=0, count2=0, count3=0;

	do{	
		count1++;
		current2 = wheel_2;
		do{
			count2++;
			if(current->data == current2->data){
				current3 = wheel_3;
				do{	
					count3++;
					if(current->data == current3->data){
						printf("\n\n\nCommon Number: %d\nPosition in wheel_1: %d\nPosition in wheel_2: %d\nPosition in wheel_3: %d", current->data, count1, count2, count3);
						flag=0;
					}
					current3 = current3->next;
				
				}while(current3 != wheel_3 && flag == 1);
			}
			current2 = current2->next;
			count3 = 0; 
		}while(current2 != wheel_2 && flag == 1);
		current = current->next;
	  count2 = 0;
	  count3 = 0;
	}while(current != wheel_1 && flag == 1);
}

void putCommonNum(Node **wheel, int position, int common){
	int i;
	Node *current = *wheel;
	for(i=0; i<position; i++){
		current= current->next;
	}
	current->data = common;
}

void createWheel(Node **wheel, int *arr, int n, int m, int common,int position){		// creating a circular doubly linked list
	int i,randomNum, isSame, flag,control;
	Node *start =NULL, *temp=NULL, *temp2=NULL, *prev=NULL, *newNode;
	
	start = *wheel;
	
	for(i=0; i<m; i++){
		
		isSame =1;  	 // check if the same number exists in a linked list
		flag =1;	   	 // check the incorrectly generated number in the list again
		
		if(start== NULL){
			do{
				randomNum = getRandom(n);
			}while(randomNum == common);
			
			if(arr[randomNum-1] == 2){
				do{
					randomNum = getRandom(n);	
				}while(randomNum == common || arr[randomNum-1] == 2);     //  if there are 2 times randNum in the array 
			}															  // or randNum is generated the same number with the common number is checked
			
			newNode = (Node*)malloc(sizeof(Node));
			newNode->data = randomNum;
			newNode->next = start;
			arr[randomNum-1]++;
			
			start=newNode;
			start->next = start;
			start->prev = start;
			*wheel = start;
		}
		else{
			while(isSame ==1){
				randomNum = getRandom(n);
				
				temp = start;
				
				if(start->next ==  start){       				// the second time it enters the loop, it should check for a single-element list
					if(randomNum == temp->data || randomNum == common || arr[randomNum - 1] == 2){
						do{
							randomNum = getRandom(n);	
						}while(temp->data == randomNum || randomNum == common|| arr[randomNum-1] ==2);
					}
					isSame=0;
				}
				
				else{										  // checks for three or more entries into the loop.
					control = 1;							  // checking whether consecutive elements are the same.
					while((temp!= start && flag ==1) || control ){                                                   //one day it will be improved 
						control=0;
			
						if(temp->data == randomNum || randomNum == common || arr[randomNum-1] ==2){
								
							randomNum = getRandom(n);
							temp = start;
							control=1;
						}
						else{
							temp = temp->next;		
						}	
					}
					if(flag ==1){
						isSame=0;
					}
				}
			}
			newNode = (Node*)malloc(sizeof(Node));
			newNode->data = randomNum;
			newNode->next = start;
			arr[randomNum-1]++;
			
			if(start->next == start){									// to add the second element
				start->next = newNode;
				start->prev = newNode;
				newNode->next = start;
				newNode->prev = start;
			}
			else{														// to add the third or more elements
				temp2 = start;
				while(temp2->next!=start){
					temp2 = temp2->next;
				}
				temp2->next = newNode;
				newNode->prev= temp2;
				newNode->next= start;
				start->prev = newNode;
			}	
		}
	}
	putCommonNum(wheel,position,common);								//writes the common number to the random position
}

void printList(Node *head){
	if (head == NULL) {
	       printf("List is empty.\n");
	    return;
	}
	Node* temp = head;
	
	do {
	    printf("%d\t", temp->data);
	    temp = temp->next;
	} while (temp != head);
	
}

int getRandom(int m){
	int sayi = rand()%m + 1;
	return sayi;
}
