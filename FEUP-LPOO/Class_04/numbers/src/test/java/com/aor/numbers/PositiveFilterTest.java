package com.aor.numbers;
import org.junit.Test;

import static org.junit.Assert.*;

public class PositiveFilterTest {

    @Test
    public void test1(){
        PositiveFilter filter = new PositiveFilter();
        assertFalse(filter.accept(-1));
        assertFalse(filter.accept(0));
        assertTrue(filter.accept(1));
        assertTrue(filter.accept(10));

    }
}
