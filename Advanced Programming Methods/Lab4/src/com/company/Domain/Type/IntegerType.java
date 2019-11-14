package com.company.Type;

public class IntegerType implements Type
{
    public boolean hasSameType(Object value) { return value instanceof IntegerType; }
    public String toString() { return "int"; }
}
