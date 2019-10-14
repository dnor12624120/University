package com.company.Interface;

import com.company.Controller.Controller;
import com.company.Domain.Cube;
import com.company.Domain.Sphere;
import com.company.Domain.Cylinder;
import com.company.Domain.ThreeDimensionalObject;
import com.company.Repository.ThreeDimensionalObjectArray;

public class Main
{
    public static void main(String[] args)
    {
        ThreeDimensionalObjectArray repository = new ThreeDimensionalObjectArray(512);
        Controller controller = new Controller(repository);
        ConsoleAPI userInterface = new ConsoleAPI(controller);
        userInterface.run();
    }
}
