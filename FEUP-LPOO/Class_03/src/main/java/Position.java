public class Position {
	private int x; 
	private int y; 

	//default position 
	public Position(int x, int y){
		this.x = x; 
		this.y = y; 
	}
	public void setPosition(Position position){
		this.x = position.x; 
		this.y = position.y; 
	}

	public int getX(){
		return x; 
	}

	public int getY(){
		return y; 
	}

	@Override
	public boolean equals(Object o){
		if (o == null) return false; 
		if (this == o) return true;

		if (getClass() != o.getClass()) return false; 

		Position p = (Position)o; 
		return (p.getX() == x && p.getY() == y);
	}
}
