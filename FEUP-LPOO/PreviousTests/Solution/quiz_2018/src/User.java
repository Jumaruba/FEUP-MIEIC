import java.lang.Integer;

public class User extends Person{
    public User(String name, Integer age){
        super(name, age);
    }

    public User(String name){
        super(name);
    }

    public String getUsername() {
        return name + age.toString();
    }

}
