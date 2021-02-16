package com.aor.numbers;

import java.util.ArrayList;
import java.util.List;

public class ListFilterer {
    List<Integer> list;
    public ListFilterer (List<Integer> list){
        this.list = list;
    }

    public List<Integer> filter(IListFilter filter){
        List<Integer> newList = new ArrayList<>();
        for (Integer l: list){
            if (filter.accept(l)) newList.add(l);
        }
        return newList;
    }
}
