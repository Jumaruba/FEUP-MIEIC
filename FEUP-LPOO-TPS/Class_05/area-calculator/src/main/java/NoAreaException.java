public class NoAreaException extends Throwable {
    private String message;
    public NoAreaException(String message){
        this.message = message;
    }

    @Override
    public String getMessage() {
        return message;
    }
}
