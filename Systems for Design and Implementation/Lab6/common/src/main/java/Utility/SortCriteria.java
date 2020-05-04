package Utility;

public class SortCriteria
{
    public SortOrder order;
    public String field;

    public SortCriteria(SortOrder order, String field)
    {
        this.order = order;
        this.field = field;
    }
}
