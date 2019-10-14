package com.company.Domain.Validators;

import com.company.Domain.Exceptions.ThreeDimensionalObjectException;
import com.company.Domain.Sphere;

public class SphereValidator
{
    public static void validateSphere(Sphere sphere) throws ThreeDimensionalObjectException
    {
        if(sphere.getRadius() < 0)
        {
            throw new ThreeDimensionalObjectException("Sphere radius cannot be negative.");
        }
    }
}
