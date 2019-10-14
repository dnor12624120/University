package com.company.Domain.Validators;

import com.company.Domain.Cube;
import com.company.Domain.Exceptions.ThreeDimensionalObjectException;

public class CubeValidator
{
    public static void validateCube(Cube cube) throws ThreeDimensionalObjectException
    {
        if(cube.getEdgeLength() < 0)
        {
            throw new ThreeDimensionalObjectException("Edge length cannot be negative");
        }
    }
}
