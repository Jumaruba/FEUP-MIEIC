import java.util.List;

public class StringRecipe {
    List<StringTransformer> list;
    public StringRecipe(List<StringTransformer> list){
        this.list = list;
    }

    //the commander is just responsable to receive a list of actions and execute then
    public void mix(){
        for (int i = 0; i< list.size(); i++){
            this.list.get(i).execute();
        }
    }

}
