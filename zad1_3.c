#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printMatrix(int *tab, int * size){
    int i, j;

    printf("    ");
    for(i = 0; i < *size; i++)
        printf("%i  ", i);

    printf("\n");
    for(i = 0; i < *size; i++){
        printf("%i  ", i);
        for(j = 0; j < *size; j++)
            printf("|%i ", tab[i * (*size) + j]);
        printf("|\n");
    }
}

void multiply(int *m1, int *m2, int * size){
    int i, j, k;
    for(i = 0; i < *size; i++){
        for(j = 0; j < *size; j++){
            m2[i * (*size) + j] = 0;
            for(k = 0; k < *size; k++){
                m2[i * (*size) + j] += m1[i * (*size) + k] * m1[k * (*size) + j];
            }
        }
    }
}

int main(void){
	FILE *data;
	int size, i, j, odp = 0;
	printf("Wcztanie z pliku...\n");
    if ((data = fopen("data", "r")) == NULL)
    	printf ("Nie mogę otworzyć pliku data!\n");

	fscanf(data, "%d", &size);
	printf("Rozmiar: %i\n", size);
    int m1[size * size];
    int m2[size * size];
    // Load data into table from file
    for(i = 0; i < size; i++)
    	for(j = 0; j < size; j++)
    		fscanf(data, "%d", &m1[i * size + j]);

    fclose (data);
    // Print loaded data
    printMatrix(m1, &size);
    
    multiply(m1, m2, &size);
    multiply(m2, m1, &size);

    for(i = 0; i < size; i++)
        odp += m1[i * size + i];

    printf("Trojkatow jest: %i\n", odp/6);
    return 0;
}