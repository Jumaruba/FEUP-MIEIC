import com.googlecode.lanterna.*;
import com.googlecode.lanterna.graphics.TextGraphics;
import jdk.nashorn.internal.ir.Terminal;

import java.util.ArrayList;
import java.util.List;
import java.util.Random;

public class Arena {
    private int width;
    private int height;
    private Hero hero;
    private Energy energy = new Energy(3);
    private List<Wall> walls;
    private List<Coin> coins;
    private List<Monster> monsters;
    private int numbMonsters = 30;

    public Arena(int width, int height) {
        this.width = width;
        this.height = height;
        hero = new Hero(10, 10);
        this.walls = createWalls();
        coins = createCoins();
        monsters = createMonsters();
    }

    public boolean canHeroMove(Position position) {
        if (position.getX() > width) return false;
        if (position.getY() > height) return false;
        if (position.getY() < 0) return false;
        if (position.getX() < 0) return false;
        for (Wall wall : walls)
            if (position.equals(wall.getPosition())) return false;
        return true;
    }

    public void moveHero(Position position) {
        if (canHeroMove(position)) hero.setPosition(position);
    }

    public void draw(TextGraphics graphics) {
        graphics.setBackgroundColor(TextColor.Factory.fromString("#008000"));
        graphics.fillRectangle(new TerminalPosition(0, 0), new TerminalSize(width + 1, height + 1), ' ');
        for (Coin coin : coins) coin.draw(graphics);
        hero.draw(graphics);
        for (Wall wall : walls) wall.draw(graphics);
        moveMonsters();
        for (Monster monster : monsters) monster.draw(graphics);
        retrieveCoins();
        energy.showLifeBar(graphics);
    }

    private void retrieveCoins() {
        for (int i = 0; i < coins.size(); i++)
            if (hero.getPosition().equals(coins.get(i).getPosition())) {
                coins.remove(i);
                return;
            }
    }

    public Hero getHero() {
        return hero;
    }

    public List<Wall> createWalls() {
        List<Wall> walls = new ArrayList<>();

        for (int c = 0; c < width; c++) {
            walls.add(new Wall(c, 0));
            walls.add(new Wall(c, height - 1));
        }

        for (int r = 1; r < height - 1; r++) {
            walls.add(new Wall(0, r));
            walls.add(new Wall(width - 1, r));
        }
        return walls;
    }

    private List<Coin> createCoins() {
        Random random = new Random();
        ArrayList<Coin> coins = new ArrayList<>();
        for (int i = 0; i < 5; i++) {
            coins.add(new Coin(random.nextInt(width - 2) + 1, random.nextInt(height - 2) + 1));
        }
        return coins;
    }

    private List<Monster> createMonsters() {
        Random random = new Random();
        ArrayList<Monster> monsters = new ArrayList<>();
        int x, y;
        Position p;
        for (int i = 0; i < numbMonsters; i++) {
            do {
                x = random.nextInt(width - 2) + 1;
                y = random.nextInt(height - 2) + 1;
                p = new Position(x, y);
            } while (hero.getPosition().equals(p));        //cannot collide with the hero
            monsters.add(new Monster(x, y));
        }
        return monsters;
    }

    public void moveMonsters() {
        Random random = new Random();
        int axisX, axisY;
        for (int i = 0; i < monsters.size(); i++) {
			axisX = monsters.get(i).getPosition().getX() + random.nextInt(3) - 1;
			axisY = monsters.get(i).getPosition().getY() + random.nextInt(3) - 1;
			if (canHeroMove(new Position(axisX, axisY)))
				monsters.set(i, new Monster(axisX, axisY));
        }
    }

    private boolean verifyMonsterCollision(){
    	for (Monster monster: monsters){
    		if (hero.getPosition().equals(monster.getPosition())) return true;
		}
    	return false;
	}

	public boolean energyHandler(){
        if (verifyMonsterCollision()) energy.lossEnergy();
        if (energy.getEnergy() == 0) return true;
        return false;

    }


}
