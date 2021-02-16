import com.sun.org.apache.xpath.internal.operations.String;

public class StringCaseChanger implements StringTransformer {
    StringDrink drink;
    Integer nActions = 0;
    public StringCaseChanger(StringDrink drink){
        this.drink = drink;
    }
    @Override
    public void execute() {
        StringBuffer b = new StringBuffer(this.drink.getText());
        for (int i = 0; i< this.drink.getText().length(); i++) {
            if (Character.isLowerCase(this.drink.getText().charAt(i)))
                b.setCharAt(i, Character.toUpperCase(b.charAt(i)));
            else
                b.setCharAt(i,Character.toLowerCase(b.charAt(i)));
        }
        this.drink.setText(b.toString());
        nActions ++;
    }

    @Override
    public void undo(){
        if (nActions == 0) return;
        execute();
        nActions--;
    }
}
