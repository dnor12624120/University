package com.company.Domain.Token;

public class NonSymbolicToken<T> implements Token
{
    private T value;

    public NonSymbolicToken(T value)
    {
        this.value = value;
    }

    public T getValue() { return value; }
    public void setValue(T value) { this.value = value; }

    public String toString() { return String.valueOf(value); }
}
