import com.googlecode.lanterna.graphics.TextGraphics;

public abstract class Element {

    protected Position position;
    protected Element(int x, int y){
        this.position = new Position(x,y);
    }

    public abstract void draw(TextGraphics graphics);

    public Position getPosition(){
        return this.position;
    }
}
