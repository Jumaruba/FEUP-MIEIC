public class AreaXMLOutputter {
    SumProvider a;
    public AreaXMLOutputter(SumProvider a){
        this.a = a;
    }

    public String output(){
        return "<area>"+a.sum() + "</area>";
    }
}
