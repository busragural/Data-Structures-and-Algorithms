#include<stdio.h>
#include<stdlib.h>


typedef struct node {
	
    int data;													// courses
    int ind;													// indegree
    int newInd;													// keeps the decreasing indegree value
    struct node *next;

}Node;

typedef struct graph {
	
    int vertex;														// vertex
    struct node** adjacencyLists;	
}Graph;

void makeAdjacencyMatrix(int***, int);							// receives the lessons from the user depending on the prerequisites
void adjMatrixToAdjList(int**, Graph*, int) ;					// matrix to list
void printGraph(Graph*);										// prints adjacency list
void printMatrix(int**, int);									// prints adjacency matrix
void calculateIndegree(Graph*);									// calculates the prerequisites of the course.
void printIndegree(Graph*);										// prints the prerequisites of the course.
void semesterCount(Graph*);										// calculates which courses will be taken in which semester

int main(){
	
	int i, n;
	int **adjacencyMatrix;
	
	Graph* graph = (Graph*) malloc(sizeof(Graph));
	
	printf("How many course will be taken?");
	scanf("%d", &n);
	
	makeAdjacencyMatrix(&adjacencyMatrix, n);
	printMatrix(adjacencyMatrix, n);
	
	printf("\n");
    adjMatrixToAdjList(adjacencyMatrix, graph, n);
    printGraph(graph);
    printf("\n");
	
	calculateIndegree(graph);
	printIndegree(graph);
	printf("\n");
	semesterCount(graph);
	
	
	return 0;
}

void makeAdjacencyMatrix(int ***matrix, int n){
	
	int i,j;
	
	*matrix = (int**)calloc(n,sizeof(int *));
	
	for (i=0; i<n; i++) {
    	(*matrix)[i] = (int *)calloc(n,sizeof(int));
	}
	
	printf("Enter the prerequisite matrix.\n");
	
	for(i=0; i<n; i++){
		for(j=0; j<n; j++){
			
			if(i!=j && (*matrix)[j][i] == 0 ){					// cannot be diagonally symmetrical	
				printf("[%d] ---> [%d]\n", i+1, j+1);
				printf("If the %d. course is the prerequisite for the %d. course, enter 1. Enter:", j+1, i+1);
				scanf("%d", &(*matrix)[i][j]);
			}
				
		}
	}

}

void adjMatrixToAdjList(int **matrix, Graph* graph, int n) {
	
	int i, j;
	
    graph->vertex = n;
    graph->adjacencyLists = (Node**)calloc(n, sizeof(Node*));

    Node *curr;
   
    for (i=0; i<n; i++) {
        for (j=0; j<n; j++) {
        	
            if (matrix[i][j] == 1) {							// if there is a connection between two courses
                
                Node *newNode = (Node*)malloc(sizeof(Node));
                newNode->data = j;
                newNode->ind = 0;
                newNode->newInd = 0;
                newNode->next = NULL;
                
                if(graph->adjacencyLists[i] == NULL){
                	graph->adjacencyLists[i] = newNode;
                	
				}
				else{
					curr = graph->adjacencyLists[i];
					while(curr->next != NULL){
						curr = curr->next;
					}
					curr->next = newNode;
				}
            }
        }
    }
}


void printGraph(Graph* graph) {
	
    int i;
    Node* tmp;
    printf("\nADJACENCY LIST:\n");
    for (i=0; i<graph->vertex; i++) {
    	
        tmp = graph->adjacencyLists[i];
        
        printf("Course [%d] ->> " , i+1);
        while (tmp != NULL) {
            printf("Course [%d] ->> ", tmp->data +1 );
            tmp = tmp->next;
        }
        printf("NULL\n");
    }
}

void printMatrix(int **matrix, int n){
	int i, j;
	printf("\nADJACENCY MATRIX:\n");
	for(i=0; i<n; i++){
		for(j=0; j<n; j++){
			printf("%d\t", matrix[i][j]);
		}
		printf("\n");
	}
}

void calculateIndegree(Graph* graph) {
	
    int i,j, indegrees;
    Node* tmp;
    	
    for(i=0; i<graph->vertex; i++){									// for every course
        indegrees = 0;
        for (j = 0; j<graph->vertex; j++) {							// navigating the entire list
            tmp = graph->adjacencyLists[j];
            while(tmp != NULL){
                if(tmp->data == i){
                    indegrees++;
                }
                tmp = tmp->next;
            }
        }
        
		Node *newNode = (Node*)malloc(sizeof(Node));			// adding the found indegree value as the first element of the list
		newNode->data = -2;
		newNode->ind = indegrees;
		newNode->newInd = indegrees;
		if(graph->adjacencyLists[i] == NULL){
			newNode->next = NULL;
			graph->adjacencyLists[i] = newNode;
			
		}
		else{
			newNode->next = graph->adjacencyLists[i];
			graph->adjacencyLists[i] = newNode;
		}
    }
}

void printIndegree(Graph *graph){
	int i;
	
	for(i=0; i<graph->vertex; i++){
		if(graph->adjacencyLists[i]->ind != -1){
			printf("Course-%d: %d\t", i+1, graph->adjacencyLists[i]->ind);
		}
	}
}

void semesterCount(Graph *graph){		
						
	int count =0;												// how many semesters
	int i, control;												// control of all courses taken
	Node *tmp;
	
	while(control != graph->vertex){								
		control=0;
		count++;
		for(i=0; i<graph->vertex; i++){
			
			if(graph->adjacencyLists[i]->ind == 0 ){
				printf("Semester %d -- Course-[%d] can be taken.\n", count, i+1);
	
				graph->adjacencyLists[i]->newInd = -1;
				tmp = graph->adjacencyLists[i];
				tmp = tmp->next;
	
				while(tmp != NULL){
					graph->adjacencyLists[tmp->data]->newInd--;	// the indegree value of other courses for which the selected course is a prerequisite is reduced
					tmp=tmp->next;
				}
			}
		}
		for(i=0; i<graph->vertex; i++){								// the indegree is updated
			graph->adjacencyLists[i]->ind = graph->adjacencyLists[i]->newInd;
			if(graph->adjacencyLists[i]->newInd == -1){			// checks if all lessons have been taken
				control++;
			}
		}
		printf("\n");
		printIndegree(graph);
		printf("\n");
		
	}
	
	printf("The student finishes school in %d semesters.", count);
}
