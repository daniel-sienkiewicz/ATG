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
	if(!tab[x * (*size) + y]){
		tab[x * (*size) + y] = 1;
	} else{
		printf("Krawedz juz istnieje!");
	}
}

void deleteE(int *tab, int * size){
	int x, y;
	printf("Podaj krawedz do usuniecia: ");
	scanf("%i %i", &x, &y);
	if(tab[x * (*size) + y]){
		tab[x * (*size) + y] = 0;
	} else{
		printf("Nie ma takiej krawedzi!");
	}
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
	printf("Ciag deg: ");
	for(i = 0; i < *size; i++)
    	printf("%i ", degT[i]);
    printf("\n");
}

void addV(int *tab, int * size){
	int i, x = 0, count = (*size);
	int *newMatrix = malloc(((*size) + 1 ) * ((*size) + 1) * sizeof(int));

	for(i = 0; i < ((count + 1) * (count + 1)); i++){
    	if((count + (x * (count + 1))) == i){
    		newMatrix[i] = 0;
    		x++;
    	} else{
    		newMatrix[i] = tab[i - x];
    	}

    	if(i > (count * count) + 1){
    		newMatrix[i] = 0;
    	}
    }
  	tab = realloc(tab, (count + 1) * (count + 1) * sizeof(int));

  	for(i = 0; i < ((count + 1) * (count + 1)); i++)
  		tab[i] = newMatrix[i];

 	free(newMatrix);

	(*size)++;
}

void deleteV(int *tab, int * size){
	int i, nr, count = (*size);
	printf("Ktory wierzcholek usuwamy? ");
	scanf("%i", &nr);
	int * newMatrix = malloc(count * count * sizeof(int));

	for(i = 0; i < ((count) * (count)); i++)
		newMatrix[i] = tab[i];

	if(nr == count - 1){
		tab = realloc(tab, (count - 1) * (count - 1) * sizeof(int));
		
	} else{

	}

	(*size)--;
}

int main(void){
	FILE *data;
	int size, i, j, select = 1;
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
    			printf("3 - powrot\n");
    			printf("0 - koniec\n");
    			printf("\nCo robimy: ");
    			scanf("%i", &select);
    			switch(select){
    				case 1:
    					addE(matrix, &size);
    					printMatrix(matrix, size);
    					break;
    				case 2:
    					deleteE(matrix, &size);
 			   			printMatrix(matrix, size);
    					break;
    				default:
    					break;
    			}
    			break;
    		case 2:
    			printf("1 - dodaj wierzcholek\n");
    			printf("2 - usun wierzcholek\n");
    			printf("3 - stopien wierzcholka\n");
    			printf("4 - powrot\n");
    			printf("0 - koniec\n");
    			printf("\nCo robimy: ");
    			scanf("%i", &select);
    			switch(select){
    				case 1:
    					addV(matrix, &size);
    					printMatrix(matrix, size);
    					break;
    				case 2:
    					deleteV(matrix, &size);
 			   			printMatrix(matrix, size);
    					break;
    				case 3:
    					degV(matrix, &size);
    					break;
    				default:
    					break;
    			}
    			break;
    		case 3:
    			printMatrix(matrix, size);
    			break;
    		default:
    			select = 0;
    			break;
    	}
    }
    free(matrix);
	return 0;
}