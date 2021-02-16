import com.googlecode.lanterna.TerminalPosition;
import com.googlecode.lanterna.graphics.TextGraphics;

public class Coin extends Element{
    public Coin(int x, int y){
        super(x,y);
    }

    public void draw(TextGraphics graphics){
        graphics.putString(new TerminalPosition(position.getX(), position.getY()), "O");
    }
}
