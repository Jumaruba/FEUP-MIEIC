public interface OrderingStrategy {
    void wants(StringRecipe recipe, StringBar bar);
    void happyHourStarted(Bar bar);
    void happyHourEnded(Bar bar);
}
