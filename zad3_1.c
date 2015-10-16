#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printMatrix(int *tab, int size){
    int i;

    printf("Dane: ");
    for(i = 0; i < size; i++){
        printf("%i ", tab[i]);
    }
    printf("\n");
}

void sort(int *tab, int size){
	int i, j, tmp;

	for(i = 0; i < size; i++){
		for(j = 0; j < size - 1; j++){
			if(tab[j] < tab[j + 1]){
				tmp = tab[j];
				tab[j] = tab[j + 1];
				tab[j + 1] = tmp;
			}
		}
	}
}

int sum(int *tab, int size){
	int i, sum = 0;
	for(i = 0; i < size; i++)
		sum += tab[i];

	printf("Suma: %i\n", sum);
	return sum%2;
}	

void construct(int *tab, int size, int count){
	int tmp, i;
	printMatrix(tab, size);
	tmp = tab[0];
	
	for(i = 1; i <= tmp; i++)
		tab[i]--;

	tab[0] = 0;
	sort(tab, size);
	if(count + 1 < size - count){
		construct(tab, size, count + 1);
	}
}

int main(void){
	FILE *data;
	int size, i, odp = 0;
	printf("Wcztanie z pliku...\n");
    if ((data = fopen("data2", "r")) == NULL)
    	printf ("Nie mogę otworzyć pliku data!\n");
    fscanf(data, "%d", &size);
	printf("Rozmiar: %i\n", size);
	int deg[size];

	for(i = 0; i < size; i++)
    	fscanf(data, "%d", &deg[i]);
	fclose (data);

	printMatrix(deg, size);

	if(sum(deg, size)){
		printf("Odpoowiedz: NIE\n");
	}
	else{
		sort(deg, size);
		construct(deg, size, 0);
		for(i = 0; i < size; i++)
			odp += deg[i];

		if(!odp)
			printf("Odpoowiedz: TAK\n");		
		else
			printf("Odpoowiedz: NIE\n");
	}

	return 0;
}