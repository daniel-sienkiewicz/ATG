#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define first 0

struct L{
	int nr;
	struct L *next;
};

struct L *head; /**< Head of the list*/
struct L *tail; /**< Tail of the list*/

void printMatrix(int *tab, int size){
	int i, j;

	printf("    ");
	for(i = 0; i < size; i++)
		printf("%i  ", i);

	printf("\n");
	for(i = 0; i < size; i++){
		printf("%i  ", i);
    	for(j = 0; j < size; j++)
    		printf("|%i ", tab[i * size + j]);
    	printf("|\n");
    }
}

void insert(int nr){
	struct L *newObject = (struct L *)malloc(sizeof(struct L));
	newObject->next = NULL;
	newObject->nr = nr;

	//if list is empty
	if(head == NULL){
		head = newObject;
		(head)->next = NULL;
		tail = head;
		tail->next = NULL;
		return;
	} else {
		(tail)->next = newObject;
		(tail) = newObject;
		return;
	}
}

int countAll(){
	struct L *jumper = (struct L *)malloc(sizeof(struct L));
	jumper = head;
	int count = 0;

	while(jumper != NULL){
		count++;	
		jumper = jumper->next;
	}
	
	free(jumper);
	return count;
}

void printOne(struct L * jumper){
	if(jumper != NULL){
		printf("%i, ", jumper->nr);
	} else{
		printf("NULL\n");
	}
}

void printL(){
	struct L *jumper = (struct L *)malloc(sizeof(struct L));
	jumper = head;
	printf("\nL: ");
	while(jumper != NULL){
		printOne(jumper);
		jumper = jumper->next;
	}
	printf("\n");
	free(jumper);
}

int inL(int nr){
	int answer = 0;
	struct L *jumper = (struct L *)malloc(sizeof(struct L));
	jumper = head;
	while(jumper != NULL){
		if(jumper->nr == nr)
			answer = 1;
		jumper = jumper->next;
	}
	free(jumper);

	return answer;
}

void getDeg(int * matrix, int * deg, int size){
	int i, j;
	for(i = 0; i < size; i++){
    	for(j = 0; j < size; j++)
    		deg[i] += matrix[i * size + j];
    }
}

int main(void){
	FILE *data;
	int size, i, j;
	printf("\033[2J");
    printf("\033[0;0f");
	printf("Wcztanie z pliku...\n");
    if ((data = fopen("data", "r")) == NULL)
    	printf ("Nie mogę otworzyć pliku data!\n");

	fscanf(data, "%d", &size);
	printf("Rozmiar: %i\n", size);
    int *matrix = malloc(size * size * sizeof(int));
    int *deg = malloc(size * sizeof(int));

    // Load data into table from file
    for(i = 0; i < size; i++)
    	for(j = 0; j < size; j++)
    		fscanf(data, "%d", &matrix[i * size + j]);

    fclose (data);
    // Print loaded data
    printMatrix(matrix, size);
    getDeg(matrix, deg, size);
    printf("\nDeg: ");
   	for(i = 0; i < size; i++){
   		printf("%i ", deg[i]);
   	}
   	printf("\n");
    return 0;
}