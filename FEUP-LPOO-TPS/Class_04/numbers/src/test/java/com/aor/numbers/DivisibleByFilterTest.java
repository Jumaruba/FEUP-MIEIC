package com.aor.numbers;

import org.junit.Test;

import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertTrue;

public class DivisibleByFilterTest {
    @Test
    public void test1(){
        DivisibleByFilter d1 = new DivisibleByFilter(3);

        assertTrue(d1.accept(3));
        assertFalse(d1.accept(1));
        assertFalse(d1.accept(2));
        assertTrue(d1.accept(6));
        assertFalse(d1.accept(0));

    }
    @Test
    public void test2(){
        DivisibleByFilter d2 = new DivisibleByFilter(1);

        assertTrue(d2.accept(3));
        assertTrue(d2.accept(100));
        assertFalse(d2.accept(0));
    }

}
