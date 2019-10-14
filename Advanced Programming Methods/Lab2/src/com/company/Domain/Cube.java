package com.company.Domain;

public class Cube implements ThreeDimensionalObject
{
    private double edgeLength;

    public Cube()
    {
        this.edgeLength = 0;
    }

    public Cube(double edgeLength)
    {
        this.edgeLength = edgeLength;
    }

    public double getEdgeLength()
    {
        return edgeLength;
    }

    public void setEdgeLength(double edgeLength)
    {
        this.edgeLength = edgeLength;
    }

    public double getVolume()
    {
        return Math.pow(edgeLength, 3);
    }

    public String toString() { return "Cube edge length: " + edgeLength
            + "\n Cube volume: " + getVolume(); }
}
