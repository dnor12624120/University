package com.company.Type;

public class BooleanType implements Type
{
    public boolean hasSameType(Object value)
    {
        return value instanceof BooleanType;
    }
    public String toString() { return "bool"; }
}
