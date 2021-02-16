package com.aor.numbers;

import org.junit.Before;
import org.junit.Test;
import org.mockito.Mockito;

import java.util.ArrayList;
import java.util.List;

import static org.junit.Assert.assertEquals;

public class ListFiltererTest {
    List<Integer> list = new ArrayList<>();
    @Test
    public void test1(){
        //this test will run with stub: positiveFilter
        class Stub implements IListFilter{
            public boolean accept(Integer number){
                if (number == -1 || number == -3) return false;
                return true;
            }
        }

        Stub stub = new Stub();
        ListFilterer listFilter = new ListFilterer(list);
        List<Integer> expected = new ArrayList<>();
        expected.add(3);
        expected.add(4);
        expected.add(1);
        expected.add(6);
        assertEquals(expected, listFilter.filter(stub));

    }
    @Test
    public void test2(){
        //this test will run mockito: positiveFilter
        ListFilterer listFilter = new ListFilterer(list);
        List<Integer> expected = new ArrayList<>();
        expected.add(3);
        expected.add(4);
        expected.add(1);
        expected.add(6);
        IListFilter filter = Mockito.mock(IListFilter.class);
        Mockito.when(filter.accept(-1)).thenReturn(false);
        Mockito.when(filter.accept(-3)).thenReturn(false);
        Mockito.when(filter.accept(3)).thenReturn(true);
        Mockito.when(filter.accept(4)).thenReturn(true);
        Mockito.when(filter.accept(1)).thenReturn(true);
        Mockito.when(filter.accept(6)).thenReturn(true);
        assertEquals(expected, listFilter.filter(filter));


    }

    @Test
    public void test3(){
        //this test will run with stub: DivisibleByFilter
        class Stub implements IListFilter{
            public boolean accept(Integer number){
                if (number == 4) return false;
                return true;
            }
        }

        Stub stub = new Stub();
        ListFilterer listFilter = new ListFilterer(list);
        List<Integer> expected = new ArrayList<>();
        expected.add(-1);
        expected.add(3);
        expected.add(1);
        expected.add(6);
        expected.add(-3);
        assertEquals(expected, listFilter.filter(stub));

    }

    @Test
    public void test4(){
        //this test will run with mockito: DivisibleByFilter
        IListFilter filter = Mockito.mock(IListFilter.class);
        Mockito.when(filter.accept(-1)).thenReturn(true);
        Mockito.when(filter.accept(3)).thenReturn(true);
        Mockito.when(filter.accept(4)).thenReturn(false);
        Mockito.when(filter.accept(1)).thenReturn(true);
        Mockito.when(filter.accept(6)).thenReturn(true);
        Mockito.when(filter.accept(-3)).thenReturn(true);
        ListFilterer listFilter = new ListFilterer(list);
        List<Integer> expected = new ArrayList<>();
        expected.add(-1);
        expected.add(3);
        expected.add(1);
        expected.add(6);
        expected.add(-3);
        assertEquals(expected, listFilter.filter(filter));
    }

    @Before
    public void setup(){
        this.list.add(-1);
        this.list.add(3);
        this.list.add(4);
        this.list.add(1);
        this.list.add(6);
        this.list.add(-3);
    }


}
