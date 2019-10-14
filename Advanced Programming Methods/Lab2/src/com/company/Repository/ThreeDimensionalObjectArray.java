package com.company.Repository;

import com.company.Domain.ThreeDimensionalObject;

import javax.management.openmbean.InvalidOpenTypeException;
import javax.naming.SizeLimitExceededException;
import java.util.ArrayList;

public class ThreeDimensionalObjectArray implements ThreeDimensionalObjectContainer
{
    private static final int DEFAULT_CAPACITY = 128;
    private ThreeDimensionalObject[] objects;
    private int capacity;
    private int size;

    public interface Predicate
    {
        boolean run(ThreeDimensionalObject object);
    }

    ThreeDimensionalObjectArray()
    {
        this.objects = new ThreeDimensionalObject[DEFAULT_CAPACITY];
        this.capacity = DEFAULT_CAPACITY;
        this.size = 0;
    }

    public ThreeDimensionalObjectArray(int capacity)
    {
        this.objects = new ThreeDimensionalObject[capacity];
        this.capacity = capacity;
        this.size = 0;
    }

    private void swap(int objectIndex1, int objectIndex2)
    {
        ThreeDimensionalObject temp = objects[objectIndex1];
        objects[objectIndex1] = objects[objectIndex2];
        objects[objectIndex2] = temp;
    }

    @Override
    public final void add(ThreeDimensionalObject object) throws SizeLimitExceededException
    {
        if(size == capacity)
        {
            throw new SizeLimitExceededException("Array is full.");
        }
        objects[size++] = object;
    }

    @Override
    public final void remove(int index) throws IndexOutOfBoundsException
    {
        if(index < 0)
        {
            throw new IndexOutOfBoundsException("Index cannot be a negative integer.");
        }
        if(index >= size)
        {
            throw new IndexOutOfBoundsException("Index cannot exceed size.");
        }
        swap(index, size - 1);
        size--;
    }

    @Override
    public void update(int index, ThreeDimensionalObject newObject) throws IndexOutOfBoundsException
    {
        if(index < 0)
        {
            throw new IndexOutOfBoundsException("Index cannot be a negative integer.");
        }
        if(index >= size)
        {
            throw new IndexOutOfBoundsException("Index cannot exceed size.");
        }
        if(newObject.getClass() != objects[index].getClass())
        {
            throw new InvalidOpenTypeException("Old and new object types don't match.");
        }
        objects[index] = newObject;
    }

    @Override
    public final int size()
    {
        return size;
    }

    public ArrayList<ThreeDimensionalObject> filter(Predicate predicate)
    {
        ArrayList<ThreeDimensionalObject> filteredList = new ArrayList<>();
        for (int i = 0; i < size; i++)
        {
            if(predicate.run(objects[i]))
            {
                filteredList.add(objects[i]);
            }
        }
        return filteredList;
    }
}
