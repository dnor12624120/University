package com.company.Domain.Validators;

import com.company.Domain.Cylinder;
import com.company.Domain.Exceptions.ThreeDimensionalObjectException;

public class CylinderValidator
{
    public static void validateCylinder(Cylinder cylinder) throws ThreeDimensionalObjectException
    {
        if(cylinder.getHeight() < 0)
        {
            throw new ThreeDimensionalObjectException("Cylinder height cannot be negative.");
        }
        if(cylinder.getRadius() < 0)
        {
            throw new ThreeDimensionalObjectException("Cylinder radius cannot be negative.");
        }
    }
}
