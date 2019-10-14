package com.company.Domain;

public class Sphere implements ThreeDimensionalObject
{
    private double radius;

    public Sphere()
    {
        this.radius = 0;
    }

    public Sphere(double radius)
    {
        this.radius = radius;
    }

    public double getRadius()
    {
        return radius;
    }

    public void setRadius(double radius)
    {
        this.radius = radius;
    }

    public double getVolume()
    {
        return 4.0 / 3.0 * Math.PI * Math.pow(radius, 3);
    }

    public String toString() { return "Sphere radius: " + radius
            + "\n Sphere volume: " + getVolume(); }
}
