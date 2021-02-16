public class ImpatientStrategy implements OrderingStrategy {

    @Override
    public void wants(StringRecipe recipe, StringBar bar) {
        bar.order(recipe);
    }

    @Override
    public void happyHourStarted(Bar bar) {

    }

    @Override
    public void happyHourEnded(Bar bar) {

    }
}
