import com.googlecode.lanterna.gui2.BasicWindow;
import com.googlecode.lanterna.screen.Screen;
import com.googlecode.lanterna.screen.TerminalScreen;
import com.googlecode.lanterna.terminal.DefaultTerminalFactory;
import com.googlecode.lanterna.terminal.Terminal;

import javax.smartcardio.TerminalFactory;
import java.io.IOException;

public class Interface {
    public static void main(String[] args) throws IOException {
        //terminal and screen layer
        Terminal terminal = new DefaultTerminalFactory().createTerminal();
        Screen screen = new TerminalScreen(terminal);
        screen.startScreen();

        //create window to hold the panel
        BasicWindow window = new BasicWindow;
        window.setHints()
        //create gui and start gui
    }
}
