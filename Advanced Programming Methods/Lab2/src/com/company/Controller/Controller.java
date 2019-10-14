package com.company.Controller;

import com.company.Domain.Cube;
import com.company.Domain.Cylinder;
import com.company.Domain.Exceptions.ThreeDimensionalObjectException;
import com.company.Domain.Sphere;
import com.company.Domain.ThreeDimensionalObject;
import com.company.Domain.Validators.CubeValidator;
import com.company.Domain.Validators.CylinderValidator;
import com.company.Domain.Validators.SphereValidator;
import com.company.Repository.ThreeDimensionalObjectArray;
import com.company.Repository.ThreeDimensionalObjectContainer;

import javax.management.openmbean.InvalidOpenTypeException;
import javax.naming.SizeLimitExceededException;
import java.util.ArrayList;

public class Controller
{
    private ThreeDimensionalObjectContainer repository;

    public Controller(ThreeDimensionalObjectContainer repository)
    {
        this.repository = repository;
    }

    public void addCube(double edgeLength)
    {
        Cube cube = new Cube(edgeLength);
        try
        {
            CubeValidator.validateCube(cube);
            repository.add(cube);
        }
        catch (ThreeDimensionalObjectException | SizeLimitExceededException exception)
        {
            System.out.println(exception.getMessage());
        }
    }

    public void addCylinder(double height, double radius)
    {
        Cylinder cylinder= new Cylinder(height, radius);
        try
        {
            CylinderValidator.validateCylinder(cylinder);
            repository.add(cylinder);
        }
        catch (ThreeDimensionalObjectException | SizeLimitExceededException exception)
        {
            System.out.println(exception.getMessage());
        }
    }

    public void addSphere(double radius)
    {
        Sphere sphere = new Sphere(radius);
        try
        {
            SphereValidator.validateSphere(sphere);
            repository.add(sphere);
        }
        catch (ThreeDimensionalObjectException | SizeLimitExceededException exception)
        {
            System.out.println(exception.getMessage());
        }
    }

    public void removeObject(int index)
    {
        repository.remove(index);
    }

    public void updateCube(int index, double edgeLength)
    {
        Cube cube = new Cube(edgeLength);
        try
        {
            CubeValidator.validateCube(cube);
            repository.update(index, cube);
        }
        catch (ThreeDimensionalObjectException | IndexOutOfBoundsException | InvalidOpenTypeException exception)
        {
            System.out.println(exception.getMessage());
        }
    }

    public void updateCylinder(int index, double height, double radius)
    {
        Cylinder cylinder= new Cylinder(height, radius);
        try
        {
            CylinderValidator.validateCylinder(cylinder);
            repository.update(index, cylinder);
        }
        catch (ThreeDimensionalObjectException | IndexOutOfBoundsException | InvalidOpenTypeException exception)
        {
            System.out.println(exception.getMessage());
        }
    }

    public void updateSphere(int index, double radius)
    {
        Sphere sphere = new Sphere(radius);
        try
        {
            SphereValidator.validateSphere(sphere);
            repository.update(index, sphere);
        }
        catch (ThreeDimensionalObjectException | IndexOutOfBoundsException | InvalidOpenTypeException exception)
        {
            System.out.println(exception.getMessage());
        }
    }

    public ArrayList<ThreeDimensionalObject> filter(ThreeDimensionalObjectArray.Predicate predicate)
    {
        return repository.filter(predicate);
    }
}
