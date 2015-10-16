#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define first 0

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
    return 0;
}