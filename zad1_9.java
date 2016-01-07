package ovh.sienkiewicz;

public class ALF {

	public static void degree(int VT[][], int graf[][]){
		for(int i = 0; i < graf.length; i++){
			for(int j = 0; j < graf.length; j++){
				VT[i][0] = i;
				VT[j][1] += graf[i][j];
			}
		}
	}
	
	public static void sortVT(int VT[][]){
		int tmp;
		for(int i = 0; i < VT.length; i++){
			for(int j = 0; j < VT.length - 1; j++){
				if(VT[j][1] < VT[j + 1][1]){
					tmp = VT[j][0];
					VT[j][0] = VT[j + 1][0];
					VT[j + 1][0] = tmp;
					
					tmp = VT[j][1];
					VT[j][1] = VT[j + 1][1];
					VT[j + 1][1] = tmp;
				}
			}
		}
	}
	
	public static void coloring(int CT[], int VT[][], int graf[][]){
		boolean C[] = new boolean[VT.length];
		int t;
		
		// Nadanie koloru dla pierwszego wierzcholka
		CT[VT[0][0]] = 0;
		
		// Nadanie kolorow dla reszty wierzcholkow
		for(int i = 1; i < VT.length; i++){
			
			// Zerowanie dostepnych kolorow dla danego wierzcholka
			for(int j = 0; j < C.length; j++)
				C[j] = false;
			
			// Sprawdzenie kolorow dla wszytskich sasiadow
			for(int j = 0; j < VT.length; j++){
				if(graf[VT[i][0]][j] == 1){
					if(CT[j] != -1){
						C[CT[j]] = true;
					}
				}
			}
			
			// Szukanie wolnego najmniejszego koloru
			t = 0;
			while(C[t])
				t++;
			
			CT[VT[i][0]] = t;
		}
	}
	
	public static void main(String[] args) {
		// Graf wejsciowy
		int graf[][] = {{0, 1, 0, 0, 1, 0},
						{1, 0, 1, 0, 1, 1},
						{0, 1, 0, 1, 0, 0},
						{0, 0, 1, 0, 1, 1},
						{1, 1, 0, 1, 0, 0},
						{0, 1, 0, 1, 0, 0}};
		
		int VT[][] = new int[graf.length][graf.length]; // Wierzcholki i ich stopnie
		int CT[] = new int[graf.length]; // Kolory wierzcholkow -> -1 BRAK koloru
		int max = 0; // Ilosc kolorow potrzebnych do kolorowania
		
		// Inicjalizacja uzytych kolorow
		for(int i = 0; i < CT.length; i++){
			CT[i] = -1;
		}
		
		// DEBUG
		System.out.println("Graf:");
		for(int i = 0; i < graf.length; i++){
			for(int j = 0; j < graf.length; j++)
				System.out.print(graf[i][j] + " ");
			System.out.println();
		}
		
		// Liczenie stopni wierzcholkow
		degree(VT, graf);
		
		// Sortowanie po stopniach wierzcholka
		sortVT(VT);
		System.out.println("\nPosortowane stopnie wierzcholkow:");
		for(int i = 0; i < VT.length; i++)
			System.out.println("deg[" + VT[i][0] + "] = " + VT[i][1]);
		
		// Kolorowanie wierzcholkow
		coloring(CT, VT, graf);
		System.out.println("\nKolorowanie:");
		for(int i = 0; i < VT.length; i++){
			System.out.println("kolor[" + i + "] = " + CT[i]);
			if(CT[i] > max)
				max = CT[i] + 1;
		}
		
		System.out.println("\nIlosc kolorow: " + max);
	}	
}