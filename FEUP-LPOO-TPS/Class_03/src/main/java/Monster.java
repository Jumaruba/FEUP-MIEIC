import com.googlecode.lanterna.TerminalPosition;
import com.googlecode.lanterna.graphics.TextGraphics;


public class Monster extends Element {
    public Monster(int x, int y){
        super(x,y);
    }
    public void draw(TextGraphics graphics){
        graphics.putString(new TerminalPosition(position.getX(), position.getY()), "M" );

        escreve(10);
    }

    public void escreve(Object o) {
        System.out.println(o.toString());
    }

}
