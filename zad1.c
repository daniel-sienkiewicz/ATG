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

void sort(int *tab, int size){
	int i, j, tmp;

	for(i = 0; i < size; i++){
		for(j = 0; j < size - 1; j++){
			if(tab[j] > tab[j + 1]){
				tmp = tab[j];
				tab[j] = tab[j + 1];
				tab[j + 1] = tmp;
			}
		}
	}
}

void addE(int *tab, int * size){
	int x, y;
	printf("Podaj krawedz do dodania: ");
	scanf("%i %i", &x, &y);
	tab[x * (*size) + y] = 1;
}

void deleteE(int *tab, int * size){
	int x, y;
	printf("Podaj krawedz do usuniecia: ");
	scanf("%i %i", &x, &y);
	tab[x * (*size) + y] = 0;
}

void degV(int *tab, int * size){
	int degT[*size];
	int x, deg = 0, i, j, min = *size, max = 0, parzy = 0, nieparzy = 0;
	printf("Podaj wierzcholek: ");
	scanf("%i", &x);

	for(i = 0; i < *size; i++)
		deg += tab[x * (*size) + i];

	printf("Stopien wierzcholka %i to: %i\n", x, deg);
	deg = 0;
	for(i = 0; i < *size; i++){
    	for(j = 0; j < *size; j++){
    		deg += tab[i * (*size) + j];		
    	}

    	if(deg < min)
    		min = deg;

    	if(deg > max)
    		max = deg;

    	if(deg%2 == 0)
    		parzy++;

    	else
    		nieparzy++;

    	degT[i] = deg;

    	deg = 0;
    }

    sort(degT, *size);

	printf("Min deg to: %i\n", min);
	printf("Max deg to: %i\n", max);
	printf("Parzystych deg jest: %i\n", parzy);
	printf("Nie parzystych deg jest: %i\n", nieparzy);
	printf("Ciag stopni: ");
	for(i = 0; i < *size; i++)
    	printf("%i ", degT[i]);
    printf("\n");
}

void addV(int *tab, int * size){
	int i, j;
	int newMatrix[((*size) + 1 ) * ((*size) + 1)];
	(*size)++;

	for(i = 0; i < *size; i++){
 	   	for(j = 0; j < *size; j++){
 	   		newMatrix[i * (*size) + j] = 0;
    	}
    }	

	for(i = 0; i < *size - 1; i++){
 	   	for(j = 0; j < *size - 1; j++){
 	   		newMatrix[i * (*size) + j] = tab[i * (*size) + j];
    	}
    }

    printMatrix(newMatrix, &(*size));

    printf("%p %p", &tab, &newMatrix);
}

void deleteV(int *tab, int * size){

}

int main(void){
	FILE *data;
	int size, i, j, select = 1;
	printf("Wcztanie z pliku...\n");
    if ((data = fopen("data", "r")) == NULL)
    	printf ("Nie mogę otworzyć pliku data!\n");

	fscanf(data, "%d", &size);
	printf("Rozmiar: %i\n", size);
    int matrix[size * size];

    // Load data into table from file
    for(i = 0; i < size; i++)
    	for(j = 0; j < size; j++)
    		fscanf(data, "%d", &matrix[i * size + j]);

    fclose (data);
    // Print loaded data
    printMatrix(matrix, &size);

	// Menu	
    while(select){
    	printf("\n1 - Krawedzie\n");
    	printf("2 - Wierzcholki\n");
    	printf("3 - drukuj\n");
    	printf("0 - koniec\n");
    	printf("\nCo robimy: ");
    	scanf("%i", &select);

    	switch(select){
    		case 1:
    			printf("1 - dodaj krawedz\n");
    			printf("2 - usun krawedz\n");
    			printf("\nCo robimy: ");
    			scanf("%i", &select);
    			switch(select){
    				case 1:
    					addE(matrix, &size);
    					printMatrix(matrix, &size);
    					break;
    				case 2:
    					deleteE(matrix, &size);
 			   			printMatrix(matrix, &size);
    					break;
    			}
    			break;
    		case 2:
    			printf("1 - dodaj wierzcholek\n");
    			printf("2 - usun wierzcholek\n");
    			printf("3 - stopien wierzcholka\n");
    			printf("\nCo robimy: ");
    			scanf("%i", &select);
    			switch(select){
    				case 1:
    					addV(matrix, &size);
    					printMatrix(matrix, &size);
    					break;
    				case 2:
    					deleteV(matrix, &size);
 			   			printMatrix(matrix, &size);
    					break;
    				case 3:
    					degV(matrix, &size);
    					break;
    			}
    			break;
    		case 3:
    			printMatrix(matrix, &size);
    			break;
    		default:
    			select = 0;
    			break;
    	}
    }
	return 0;
}