#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define first 1

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

void findCycle(int * matrix, int size, int level){
	int i = 0, l, spr = 0;
	if(level == first)
		insert(first);

	while(i < size){
		if(matrix[level*size + i] == 1 && !inL(i)){
			insert(i);
			l = i;
			i = size;		
		}
		i++;
	}

	for(i = 0; i < size; i++){
		spr += matrix[level*size + i];
		if(matrix[level*size + i] == 1 && inL(i))
			spr--;
	}

	if(spr){
		findCycle(matrix, size, l);
	}
}

int getDeg(int* matrix, int size){
	int i, answer = 0;
	for(i = 0; i < size; i++){
		answer += matrix[i];
	}

	return answer;
}

void clearL(int* matrix, int size){
	struct L *jumper = (struct L *)malloc(sizeof(struct L));
	jumper = head->next;
	while(jumper->next != NULL){
		if(matrix[first * size + jumper->next->nr] == 0){
			jumper->next->nr = 99;
			jumper->next = jumper->next->next;
		}

		jumper = jumper->next;
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

    // Load data into table from file
    for(i = 0; i < size; i++)
    	for(j = 0; j < size; j++)
    		fscanf(data, "%d", &matrix[i * size + j]);

    fclose (data);
    // Print loaded data
    printMatrix(matrix, size);

    findCycle(matrix, size, first);
    clearL(matrix, size);
    printL();
    printf("Dlugosc cyklu: %i\n", countAll());
    printf("Min: %i\n", getDeg(matrix, size));
    return 0;
}