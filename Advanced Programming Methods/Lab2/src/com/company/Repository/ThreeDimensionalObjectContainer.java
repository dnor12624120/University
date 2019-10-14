package com.company.Repository;

import com.company.Domain.ThreeDimensionalObject;

import javax.naming.SizeLimitExceededException;
import java.util.ArrayList;

public interface ThreeDimensionalObjectContainer
{
    void add(ThreeDimensionalObject object) throws SizeLimitExceededException;
    void remove(int index) throws IndexOutOfBoundsException;
    void update(int index, ThreeDimensionalObject newObject) throws IndexOutOfBoundsException;
    ArrayList<ThreeDimensionalObject> filter(ThreeDimensionalObjectArray.Predicate predicate);
    int size();
}
