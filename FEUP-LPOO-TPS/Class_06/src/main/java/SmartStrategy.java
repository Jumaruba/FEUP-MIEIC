public class SmartStrategy implements OrderingStrategy {
    StringBar bar;
    StringRecipe recipe;
    public SmartStrategy(){}
    @Override
    public void wants(StringRecipe recipe, StringBar bar) {
        if (bar.isHappyHour()) bar.order(recipe);
        else{
            this.bar = bar;
            this.recipe = recipe;}


    }
    //if not happy hour it waits
    @Override
    public void happyHourStarted(Bar bar) {
        this.bar.order(recipe);
    }

    @Override
    public void happyHourEnded(Bar bar) {

    }
}
