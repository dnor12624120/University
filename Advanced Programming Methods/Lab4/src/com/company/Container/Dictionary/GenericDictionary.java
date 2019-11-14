package com.company.Container.Dictionary;

public interface Dictionary<T, U>
{
    void insert(T key, U value);
    void remove(T key);
    U getValue(T key);
    boolean contains(T key);
}
