import com.googlecode.lanterna.TerminalPosition;
import com.googlecode.lanterna.TerminalSize;
import com.googlecode.lanterna.TextColor;
import com.googlecode.lanterna.graphics.TextGraphics;

public class Energy {
    private int value;
    public Energy(int energy){
        value = energy;
    }

    public void lossEnergy(){
        this.value --;
    }

    public int getEnergy(){
        return this.value;
    }

    public void showLifeBar(TextGraphics graphics){
        graphics.setBackgroundColor(new TextColor.RGB(0,0,255));
        graphics.fillRectangle(new TerminalPosition(0,0), new TerminalSize(value, 1), ' ');
        graphics.setBackgroundColor(TextColor.Factory.fromString("#008000"));

    }
}
