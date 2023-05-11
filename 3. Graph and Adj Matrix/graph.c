#include<stdio.h>
#include<stdlib.h>



typedef struct node {
	
    int dest;
    struct node *next;
}Node;

typedef struct graph {
	
    int V;
    struct node** adjacencyLists;
}Graph;


void makeAdjacencyMatrix(int ***matrix, int n){
	
	int i,j;
	
	*matrix = (int**)calloc(n,sizeof(int *));
	
	for (i=0; i<n; i++) {
    	(*matrix)[i] = (int *)calloc(n,sizeof(int));
	}
	
	printf("Enter the prerequisite matrix.\n");
	
	for(i=0; i<n; i++){
		for(j=0; j<n; j++){
			printf("If the %d. course is the prerequisite for the %d. course, enter 1. Enter:", j+1, i+1);
			scanf("%d", &(*matrix)[i][j]);
		}
	
	}

}

void addEdge(Graph* graph, int source, int destination) {
   
    Node* newNode = (Node*)malloc(sizeof(Node));
    
    newNode->dest = destination;
    newNode->next = graph->adjacencyLists[source];
    
    graph->adjacencyLists[source] = newNode;
    
    
}


void adjMatrixToAdjList(int **matrix, Graph* graph, int n) {
	
	int i, j;
	
    graph->V = n;
    graph->adjacencyLists = (Node**) calloc(n, sizeof(Node*));
    
   
    for (i=0; i<n; i++) {
        for (j=0; j<n; j++) {
        	
            if (matrix[i][j] == 1) {
                addEdge(graph, i, j);
            }
        }
    }
}


void printGraph(Graph* graph) {
	
    int i;
    Node* tmp;
    for (i=0; i<graph->V; i++) {
    	
        tmp = graph->adjacencyLists[i];
        

        printf("Course [%d] ->> " , i+1);
        while (tmp != NULL) {
            printf("Course [%d] ->> ", tmp->dest +1 );
            tmp = tmp->next;
        }
        printf("NULL\n");
    }
}

void printMatrix(int **matrix, int n){
	int i, j;
	
	for(i=0; i<n; i++){
		for(j=0; j<n; j++){
			printf("%d\t", matrix[i][j]);
		}
		printf("\n");
	}
}



void numberOfPrerequisites(Graph* graph, int n, int *arr){

	int i;
	Node *tmp;
	
	for(i=0; i<n; i++){
		
		tmp = graph->adjacencyLists[i];
		
		while(tmp){
			
			arr[tmp->dest] +=1;
			tmp = tmp->next;
		}
	}
	printf("\n");
	
	for(i=0; i<n; i++){
		printf("Course-%d: ", i+1);
		printf("%d\t", arr[i]);
	}
	
}


int main(){
	
	int n;
	int **adjacencyMatrix;
	
	Graph* graph = (Graph*) malloc(sizeof(Graph));
	
	
	printf("How many course will be taken?");
	scanf("%d", &n);
	

	makeAdjacencyMatrix(&adjacencyMatrix, n);
	printMatrix(adjacencyMatrix, n);
	
    adjMatrixToAdjList(adjacencyMatrix, graph, n);
    printGraph(graph);
    
	int *arr = (int*)calloc(n,sizeof(int));
	numberOfPrerequisites(graph, n, arr);

	
	
	return 0; 
}
