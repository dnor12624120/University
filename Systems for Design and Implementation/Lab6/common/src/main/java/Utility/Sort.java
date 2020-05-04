package Utility;

import java.util.ArrayList;

public class Sort
{
    private ArrayList<SortCriteria> sortCriteria;

    private Sort(Sort other)
    {
        this.sortCriteria = other.sortCriteria;
    }

    private void append(SortCriteria criteria)
    {
        sortCriteria.add(criteria);
    }

    public Sort(SortCriteria criteria)
    {
        sortCriteria = new ArrayList<SortCriteria>();
        sortCriteria.add(criteria);
    }

    public Sort and(SortCriteria criteria)
    {
        Sort newSort = new Sort(this);
        newSort.append(criteria);
        return newSort;
    }

    public ArrayList<SortCriteria> getSortCriteria() { return sortCriteria; }
}
