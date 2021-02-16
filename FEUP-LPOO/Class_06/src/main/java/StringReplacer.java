public class StringReplacer implements StringTransformer{
    Character New;
    Character Old;
    StringDrink drink;
    Integer nActions = 0;

    StringReplacer(StringDrink drink, Character Old, Character New){
        this.drink = drink;
        this.Old = Old;
        this.New = New;
    }

    @Override
    public void execute() {
        this.drink.setText(this.drink.getText().replace(Old,New));
        nActions++;
    }

    @Override
    public void undo() {
        if (nActions == 0) return;
        this.drink.setText(this.drink.getText().replace(New, Old));
        nActions--;
    }
}
