import com.googlecode.lanterna.TerminalPosition;
import com.googlecode.lanterna.graphics.TextGraphics;

import java.util.List;

public class Wall extends Element{
    public Wall(int x, int y) {
        super(x,y);
    }

    public void draw(TextGraphics graphics) {
        graphics.putString(new TerminalPosition(position.getX(), position.getY()+1), "W");
    }

}
