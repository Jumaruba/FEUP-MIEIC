import com.googlecode.lanterna.graphics.TextGraphics;
import com.googlecode.lanterna.screen.Screen;
import com.googlecode.lanterna.screen.TerminalScreen;
import com.googlecode.lanterna.terminal.DefaultTerminalFactory;
import com.googlecode.lanterna.terminal.Terminal;
import com.googlecode.lanterna.input.KeyStroke;

import java.io.IOException;

import static com.googlecode.lanterna.input.KeyType.*;

public class Game {
    private Screen screen;
    private Arena arena;
    private TextGraphics graphics;

    public Game() {
        try {
            Terminal terminal = new DefaultTerminalFactory().createTerminal();
            screen = new TerminalScreen(terminal);   //it will open a screen inside the terminal

            screen.setCursorPosition(null); //we don't need the cursor
            screen.startScreen();
            screen.doResizeIfNecessary();
            graphics = screen.newTextGraphics();
            arena = new Arena(50,22);
        } catch (IOException ex) {
            ex.printStackTrace();
        }

    }

    public void draw() throws IOException {
        screen.clear();
        arena.draw(graphics);
        screen.refresh();
    }

    public void run() throws IOException {
        this.draw();
        while (true) {
            KeyStroke key = screen.readInput();
            if (key.getKeyType() == ArrowUp) arena.moveHero(arena.getHero().moveUp()); 
            if (key.getKeyType() == ArrowDown) arena.moveHero(arena.getHero().moveDown()); 
            if (key.getKeyType() == ArrowLeft) arena.moveHero(arena.getHero().moveLeft());
            if (key.getKeyType() == ArrowRight) arena.moveHero(arena.getHero().moveRight());

            this.draw();
            if (arena.energyHandler()) break;
            if ((key.getKeyType() == Character && key.getCharacter() == 'q') || key.getKeyType() == EOF) {
                screen.close();
                return;
            }
        }
        System.out.println("GAME OVER!");
        screen.close();

    }


}
