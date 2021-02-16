import com.googlecode.lanterna.SGR;
import com.googlecode.lanterna.TerminalPosition;
import com.googlecode.lanterna.TextColor;
import com.googlecode.lanterna.graphics.TextGraphics;

public class Hero extends Element{
    private int x;
    private int y;
    final private int mov = 1;

    public Hero(int x, int y){
        super(x,y);
    }

    public Position moveUp(){
        return new Position(position.getX(), position.getY()-mov);
    }
    public Position moveDown(){
        return new Position(position.getX(), position.getY()+mov);
    }
    public Position moveRight(){
        return new Position(position.getX()+mov, position.getY());
    }
    public Position moveLeft(){
        return new Position(position.getX()-mov, position.getY());
    }
    public void setPosition(Position position){
        this.position = position;
    }

    public void draw(TextGraphics graphics){
        graphics.setForegroundColor(new TextColor.RGB(255,0,0));
        graphics.enableModifiers(SGR.BOLD);             //set the hero bold
        graphics.putString(new TerminalPosition(getPosition().getX(), getPosition().getY()), "X");
        graphics.setForegroundColor(new TextColor.RGB(255,255,255));
    }

}
