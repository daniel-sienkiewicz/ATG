package ovh.sienkiewicz;

import java.util.ArrayList;
import java.util.List;

public class Dijkstry {
	public static void dijkstry(int graf[][], int nr) {
		List<Integer> stos = new ArrayList<Integer>();
		int min, u = 0;
		int[] D = new int[graf.length];
		
		for (int i = 0; i < graf.length; i++) {
			if (graf[i][nr] != 0) {
				D[i] = graf[i][nr];
			} else
				D[i] = 999;
			stos.add(i);
		}
		D[nr] = 0;
		stos.remove(stos.indexOf(nr));

		while (stos.size() > 0) {
			min = 9999;

			for (int i : stos)
				if (D[i] < min) {
					min = D[i];
					u = i;
				}

			stos.remove(stos.indexOf(u));

			for (int v : stos)
				D[v] = Math.min(D[v], D[u] + graf[u][v]);
		}
		
		System.out.print(nr + " | ");
		for(int i = 0; i < D.length; i++)
			System.out.print(D[i] + " | ");
		System.out.println();
	}

	public static void main(String args[]) {
		// Przyklodowy graf
		int graf[][] = { { 9999, 0, 2, 2, 1, 9999 }, 
						 { 9999, 9999, 1, 9999, 3, 1 }, 
						 { 2, 1, 9999, 9999, 1, 9999 }, 
						 { 2, 9999, 1, 9999, 2, 9999 },
						 { 1, 3, 1, 2, 9999, 4 }, 
						 { 9999, 1, 9999, 9999, 4, 9999 } };
		
		
		System.out.println("Najkrotsze drogi");
		System.out.print("    ");
		for(int i = 0; i < graf.length; i++)
			System.out.print(i + " | ");
		System.out.println();
		for(int i = 0; i < graf.length; i++)
			dijkstry(graf, i);
	}
}