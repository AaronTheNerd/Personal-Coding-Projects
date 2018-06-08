public class Cell {
	private boolean isCurrentlyPopulated;
	private boolean goingToBePopulated;
	private int x1;
	private int y1;
	private int x2;
	private int y2;
	
	
	
	public Cell(int anX1, int aY1, int anX2, int aY2) {
		isCurrentlyPopulated = goingToBePopulated = false;
		x1 = setCoord(anX1);
		y1 = setCoord(aY1);
		x2 = setCoord(anX2);
		y2 = setCoord(aY2);
	}
	private boolean isValid(int coord) {
		return (coord >= 0);
	}
	private int setCoord(int coord) {
		if(isValid(coord))
			return coord;
		else
			return 0;
	}
	
	
	
	public int getX1() {
		return x1;
	}
	public int getY1() {
		return y1;
	}
	public int getX2() {
		return x2;
	}
	public int getY2() {
		return y2;
	}
	public boolean isPopulated() {
		return isCurrentlyPopulated;
	}
	public boolean willBePopulated() {
		return goingToBePopulated;
	}
	
	
	
	public void setPopulation(boolean aPopulation) {
		isCurrentlyPopulated = aPopulation;
	}
	
	
	
	public void determineFate(Cell[][] neighbors) {
		int count = 0;
		for(Cell[] cs : neighbors) {
			for(Cell c : cs) {
				if(c != null)
					if(c.isCurrentlyPopulated && !this.equals(c))
						count++;
			}
		}
		if(isCurrentlyPopulated) {
			if(count < 2 || count > 3)
				goingToBePopulated = false;
			else
				goingToBePopulated = true;
		}
		else {
			if(count == 3)
				goingToBePopulated = true;
			else
				goingToBePopulated = false;
		}
	}
	
	
	
	
	public boolean equals(Cell c) {
		return (c.x1 == this.x1 && c.y1 == this.y1 && c.x2 == this.x2 && c.y2 == this.y2);
	}
}
