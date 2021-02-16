public class StringInverter implements StringTransformer {
    StringDrink d;
    Integer nActions = 0;
    public StringInverter(StringDrink d){
        this.d = d;
    }

    @Override
    public void execute() {
        StringBuffer s = new StringBuffer(d.getText());
        s.reverse();
        d.setText(s.toString());
        this.nActions ++;
    }

    @Override
    public void undo(){
        if (this.nActions == 0) return;
        execute();
        this.nActions--;
    }
}
