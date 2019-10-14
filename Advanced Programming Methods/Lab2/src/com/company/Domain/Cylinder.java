package com.company.Domain;

public class Cylinder implements ThreeDimensionalObject
{
    private double radius;
    private double height;

    public Cylinder()
    {
        this.radius = 0;
        this.height = 0;
    }

    public Cylinder(double radius, double height)
    {
        this.radius = radius;
        this.height = height;
    }

    public double getRadius()
    {
        return radius;
    }

    public double getHeight()
    {
        return height;
    }

    public void setRadius(double radius)
    {
        this.radius = radius;
    }

    public void setHeight(double height)
    {
        this.height = height;
    }

    public final double getVolume()
    {
        return height * Math.pow(radius, 2) * Math.PI;
    }

    public String toString()
    {
        return "Cylinder height: " + height +
               "\n Cylinder radius: " + radius +
               "\n Cylinder volume: " + getVolume();
    }
}
