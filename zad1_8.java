package ovh.sienkiewicz;

import java.util.ArrayList;

public class EK {
	
	// DEBUG
	public static void printGraf(int graf[][][]){
		for(int i = 0; i < graf.length; i++){
			for(int j = 0; j < graf.length; j++){
				System.out.print(graf[i][j][0] + " ");
			}
			System.out.println();
		}
	}
	
	// Usun cechy wierzcholkom za wyjatkiem s
	public static void init(int tab[][], ArrayList<Integer> L){
		for(int i = 0; i < tab.length; i++){
			for(int j = 0; j < 3; j++){
				tab[i][j] = -1;
			}
		}
		
		L.clear();
		
		// Ocechowanie zrodla s(-, -inf)
		tab[0][0] = -1;
		tab[0][1] = -2;
		tab[0][2] = 99999;
	}
	
	public static int EKalg(int T[][], int graf[][][], ArrayList<Integer> L){
		L.add(0);
		int ktory;
		
		while(!(L.contains(graf.length - 1)) && (L.size() != 0)){
			//wierzcho³ek pobrany z L
			ktory = L.get(0);
			
			// Cechujemy wierzcho³ki osi¹galne z i
			for(int i = 0; i < graf.length; i++){
				if(graf[i][ktory][1] != 0 && graf[i][ktory][1] - graf[i][ktory][0] > 0){
					if(T[i][1] == -1){
						T[i][0] = ktory;
						T[i][1] = 1;
						T[i][2] = Math.min(T[ktory][2], graf[i][ktory][1] - graf[i][ktory][0]);
						L.add(i);
					}
				}
			}
			
			L.remove(0);
			
			// DEBUG
			System.out.print("L: ");
			for(int i : L)
				System.out.print(i + " ");
			System.out.println();
			
			// DEBUG
			System.out.println("T:");
			for(int i = 0; i < 3; i++){
				for(int j = 0; j < T.length; j++){
					System.out.print(T[j][i] + " ");
				}
				System.out.println();
			}
		}
		
		if(L.contains(graf.length - 1))
			return T[T.length - 1][2];
		else
			return 0;
	}
	
	// Powieksz przeplyw o wartosc
	public static void edytuj(int graf[][][], int zwieksz, int T[][]){
		int ktory = T[T.length - 1][0];
		int poprzedni = T.length - 1;
		while(ktory != 0){
			graf[poprzedni][ktory][0] += zwieksz; 
			poprzedni = ktory;
			ktory = T[poprzedni][0];
		}
		
		graf[poprzedni][ktory][0] += zwieksz;
	}
	
	// MAIN
	public static void main(String[] args) {
		int zwieksz = 0;
						    // s      z1     z2     z3     o1     o2     o3     t
		int graf [][][] = {{{0, 0},{0, 0}, {0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0}}, // s
						   {{0, 26},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0}}, // z1
						   {{0, 24},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0}}, // z2
						   {{0, 19},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0}}, // z3
						   {{0, 0}, {0, 8},{0, 6},{0,4},{0, 0},{0, 0},{0, 0},{0, 0}}, // o1
					 	   {{0, 0}, {0, 12},{0, 12},{0,12},{0, 0},{0, 0},{0, 0},{0, 0}}, // o1
						   {{0, 0}, {0, 12},{0, 12},{0,7},{0, 0},{0, 0},{0, 0},{0, 0}}, // o1
						   {{0, 0}, {0, 0},{0, 0},{0, 0},{0,13},{0,32},{0,24},{0, 0}}};// t
		
		int T[][] = new int[graf.length][3];
		
		// 1
		// Inicjalizacja kolejki L
		ArrayList<Integer> L = new ArrayList<Integer>();
		init(T, L);
		
		do{
			// 2
			// Cechujemy wierzcho³ki osi¹galne z i
			zwieksz = EKalg(T, graf, L);
			System.out.println("Zwiekszamy o: " + zwieksz);
		
			if(zwieksz != 0){
				// 3
				// Powieksz przeplyw o wartosc
				edytuj(graf, zwieksz, T);
				
				// DEBUG
				printGraf(graf);
		
				// Usun cechy wierzcholkom za wyjatkiem s
				init(T, L);
			}
		}while(zwieksz != 0);
		
		// 4
		// Otrzymany przeplyw jest maksymalny
		System.out.println("KONIEC");
		
		// DEBUG
		printGraf(graf);
	}
}