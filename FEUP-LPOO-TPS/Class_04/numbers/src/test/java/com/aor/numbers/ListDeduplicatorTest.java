package com.aor.numbers;

import org.junit.Before;
import org.junit.Test;
import org.mockito.Mockito;

import java.util.ArrayList;
import java.util.List;

import static org.junit.Assert.*;

public class ListDeduplicatorTest{
    List<Integer> list;
    @Test
    public void deduplicate() {
        class Stub implements IListSorter {
            @Override
            public List<Integer> sort() {
                List<Integer> list1 = new ArrayList<>();

                list1.add(1);
                list1.add(2);
                list1.add(4);
                list1.add(5);
                return list1;

            }
        }
        List<Integer> expected = new ArrayList<>();
        expected.add(1);
        expected.add(2);
        expected.add(4);
        expected.add(5);

        Stub stub = new Stub();
        ListDeduplicator deduplicator = new ListDeduplicator(list);
        List<Integer> distinct = deduplicator.deduplicate(stub);

        assertEquals(expected, distinct);
    }
    @Test
    public void bugDeduplicate(){

        List<Integer> list1 = new ArrayList<>();
        list1.add(1);
        list1.add(2);
        list1.add(2);
        list1.add(4);

        IListSorter sorter = Mockito.mock(IListSorter.class);
        Mockito.when(sorter.sort()).thenReturn(list1);
        List<Integer> list = new ArrayList<>();
        list.add(1);
        list.add(2);
        list.add(4);
        list.add(2);


        ListDeduplicator deduplicator = new ListDeduplicator(list);
        List<Integer> distinct = deduplicator.deduplicate(sorter);
        List<Integer> expected = new ArrayList<>();
        expected.add(1);
        expected.add(2);
        expected.add(4);

        assertEquals(expected, distinct);
    }


}