#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int getDeg(int* matrix, int size, int v){
    int i, deg = 0;
    for(i = 0; i < size; i++)
        deg += matrix[v * size + i];

    return deg;
}

void deleteLeafs(int * countV, int size, int* matrix, int *toDelete){
    int i, j;
    for(i = 0; i < size; i++){
        if(getDeg(matrix, size, i) == 1){
            toDelete[i] = 1;
            printf("wywalam %i\n", i);
            (*countV)--;
        }
    }

    for(i = 0; i < size; i++){
        if(toDelete[i] == 1){
            for(j = 0; j < size; j++){
                matrix[i * size + j] = 0;
                matrix[j * size + i] = 0;
            }
        }
    }
    printf("\n");
}

void treeCenter(int *r, int *countV, int size, int* matrix, int *toDelete){
    int i;
    if(*countV <= 2){
        if(*countV == 1){
            r = 0;
        }else if(*countV == 2){
            *r = 1;
        }

        printf("Centrum drzewa: ");
        for(i = 0; i < size; i++){
            if(toDelete[i] == 0)
                printf("%i ", i);
        }
        printf("\n");

    }else{
        deleteLeafs(countV, size, matrix, toDelete);
        treeCenter(r, countV, size, matrix, toDelete);    
    }
}

int main(void){
	FILE *data;
	int size, i, j, r, countV;
	printf("\033[2J");
    printf("\033[0;0f");
	printf("Wcztanie z pliku...\n");
    if ((data = fopen("data3", "r")) == NULL)
    	printf ("Nie mogę otworzyć pliku data!\n");

	fscanf(data, "%d", &size);
	printf("Rozmiar: %i\n", size);
    int *matrix = malloc(size * size * sizeof(int));
    int *toDelete = malloc(size * sizeof(int));
    for(i = 0; i < size; i++){
        toDelete[i] = 0;
    }

    countV = size;
    // Load data into table from file
    for(i = 0; i < size; i++)
    	for(j = 0; j < size; j++)
    		fscanf(data, "%d", &matrix[i * size + j]);

    fclose (data);
    // Print loaded data
    printMatrix(matrix, size);
    treeCenter(&r, &countV, size, matrix, toDelete);
    return 0;
}