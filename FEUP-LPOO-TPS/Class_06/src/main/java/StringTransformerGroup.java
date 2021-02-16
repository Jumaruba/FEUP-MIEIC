import java.util.List;

public class StringTransformerGroup implements StringTransformer{
    List<StringTransformer> rp;
    public StringTransformerGroup(List<StringTransformer> rp){
        this.rp = rp;
    }

    @Override
    public void execute(){
        for (StringTransformer st: rp){
            st.execute();
        }
    }

    @Override
    public void undo() {
        for (StringTransformer st: rp){
            st.undo();
        }
    }
}
