package com.aor.numbers;

import org.junit.Before;
import org.junit.Test;
import org.mockito.Mockito;

import java.util.ArrayList;
import java.util.List;

import static org.junit.Assert.*;

public class ListAggregatorTest {
    List<Integer> list;
    @Test
    public void sum() {

        ListAggregator aggregator = new ListAggregator(list);

        int sum = aggregator.sum();

        assertEquals(14, sum);
    }

    @Test
    public void max() {

        ListAggregator aggregator = new ListAggregator(list);

        int max = aggregator.max();

        assertEquals(5, max);

        List<Integer> list1 = new ArrayList<>();
        ListAggregator aggregator1 = new ListAggregator(list1);
        list1.add(-1);
        list1.add(-4);
        list1.add(-5);
        int max1 = aggregator1.max();
        assertEquals(-1, max1);
    }


    @Test
    public void min() {

        ListAggregator aggregator = new ListAggregator(list);

        int min = aggregator.min();

        assertEquals(1, min);
    }

    @Test
    public void distinct() {

        List<Integer> list2 = new ArrayList<>();
        list2.add(1);
        list2.add(2);
        list2.add(4);
        list2.add(2);


        List<Integer> list3 = new ArrayList<>();
        list3.add(1);
        list3.add(2);
        list3.add(4);

        IListDeduplicator deduplicator = Mockito.mock(IListDeduplicator.class);
        Mockito.when(deduplicator.deduplicate(null)).thenReturn(list3);

        ListAggregator aggregator = new ListAggregator(list2);
        int distinct1 = aggregator.distinct(deduplicator,null);
        assertEquals(3, distinct1);


    }


    @Before
    public void helper(){
        list = new ArrayList<>();
        list.add(1);
        list.add(2);
        list.add(4);
        list.add(2);
        list.add(5);


    }
}