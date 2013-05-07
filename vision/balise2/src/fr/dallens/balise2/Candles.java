package fr.dallens.balise2;

public class Candles {
	
	private int candlesPos; // 2 bits pour la position, 2 bots par couleur
	// si nombre négatif (dernier bit vaut 1), alors erreur
	
	public Candles() {
		candlesPos = -1;
	}
	
	// synchronized pour éviter que quand le thread de socket lise les couleurs
	// le thread de calcul les modifie (valeur incohérente)
	public synchronized int getCandlesPos() {
		return candlesPos;
	}
	
	public synchronized void setCandlesPos(int candlePos) {
		this.candlesPos = candlePos;
	}
	
	private String intToColor(int color) {
		switch(color) {
		case 0:
			return "red";
		case 1:
			return "blue";
		case 2:
			return "white";
		default:
			return "unknown";
		}
	}
	
	public String toString() {
		String res =  String.format("Position: %d, ", candlesPos & 0xff);
		int val = candlesPos;
		for (int i=1; i<=12; i++) {
			val = val>>2;
			res += String.format("%s ", intToColor(val & 0xff));
		}
		return res;
	}

}
