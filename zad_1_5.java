package ovh.sienkiewicz;

import java.util.ArrayList;
import java.util.List;

public class Hamilton {

	// Metoda sprawdzajaca czy podany stos tworzy droge Hamiltona
	public static boolean czyHam(List<Integer> stos, int graf[][]) {
		if ((graf[stos.get(0)][stos.get(stos.size() - 1)] == 1) && stos.size() == graf.length)
			return true;
		else
			return false;
	}

	// Metoda szukajaca cykl Hamiltona w grafie
	public static boolean ham(List<Integer> stos, int graf[][], int zdjety) {
		int v = stos.get(stos.size() - 1);

		// Wyszukiwanie sasiada
		for (int i = 0; i < graf.length; i++) {
			if (graf[v][i] == 1 && i > zdjety && !stos.contains(i)) {
				stos.add(i);
				zdjety = -1;
				i = 0;
				v = stos.get(stos.size() - 1);
			}
		}
		
		// Sprawdzanie czy stos jest cyklem hamiltona
		if (!czyHam(stos, graf)) {
			if(stos.size() - 1 > 0){
				zdjety = stos.get(stos.size() - 1);
				stos.remove(stos.size() - 1);
				ham(stos, graf, zdjety);
			}else{
				return false;
			}
		}
		return true;
	}

	public static void main(String[] args) {
		// Przykladowy graf do wyszukania cyklu Hamiltona
		/*int graf[][] = { { 0, 1, 1, 0 }, 
						 { 1, 0, 1, 1 }, 
						 { 1, 1, 0, 1 }, 
						 { 0, 1, 1, 0 } };*/
		
		// Kolejny przykladowy graf do wyszukania cyklu Hamiltona
		int graf[][] = { { 0, 1, 0, 1, 1 }, 
						 { 1, 0, 1, 0, 0 }, 
						 { 0, 1, 0, 1, 0 }, 
						 { 1, 0, 1, 0, 1 },
						 { 1, 0, 0, 1, 0 }};

		// Stos pomocniczy
		List<Integer> stos = new ArrayList<Integer>();

		// Wydruk macierzowej reprezentacji grafu
		System.out.println("Graf:");
		for (int i = 0; i < graf.length; i++) {
			for (int j = 0; j < graf[i].length; j++)
				System.out.print(graf[i][j] + " ");
			System.out.println();
		}
		// Dodanie pierwszego (startowego) wierzcholka do listy
		stos.add(0);

		// Szukanie cyklu
		boolean result = ham(stos, graf, -1);

		// Wydruk oraz interpretacja wyniku
		if (result && stos.size() > 1) {
			System.out.print("\nCykl Hamiltona: ");
			for (int i : stos)
				System.out.print(i + " -> ");
			System.out.println(stos.get(0));
		}else{
			System.out.println("\nNie ma cyklu hamiltona w podanym grafie");
		}
	}
}