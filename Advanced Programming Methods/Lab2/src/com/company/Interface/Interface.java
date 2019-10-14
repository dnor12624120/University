package com.company.Interface;

import com.company.Controller.Controller;
import com.company.Domain.ThreeDimensionalObject;

import java.util.ArrayList;
import java.util.Scanner;

class ConsoleAPI
{
    private interface Command
    {
        void run();
    }

    private boolean running;
    private Controller controller;
    private Scanner consoleInputStream;
    private Command[] commands = new Command[]
    {
        this::exit,
        this::addCube,
        this::addCylinder,
        this::addSphere,
        this::removeObject,
        this::updateCube,
        this::updateCylinder,
        this::updateSphere,
        this::viewAllObjects,
        this::viewObjectsWithWeight,
    };

    ConsoleAPI(Controller controller)
    {
        running = true;
        //controller = controller;
        consoleInputStream = new Scanner(System.in);
    }

    private int getIntegerFromConsole(String userPrompt)
    {
        System.out.println(userPrompt + "\n>");
        return consoleInputStream.nextInt();
    }

    private double getDoubleFromConsole(String userPrompt)
    {
        System.out.println(userPrompt + "\n>");
        return consoleInputStream.nextDouble();
    }

    void run()
    {
        printCommands();
        while(running)
        {
            System.out.print(">");
            int commandIndex = consoleInputStream.nextInt();
            commands[commandIndex].run();
        }
    }

    private void printCommands()
    {
        System.out.println("0. Exit");
        System.out.println("1. Add cube");
        System.out.println("2. Add cylinder");
        System.out.println("3. Add sphere");
        System.out.println("4. Delete object");
        System.out.println("5. Update cube");
        System.out.println("6. Update cylinder");
        System.out.println("7. Update sphere");
        System.out.println("8. View all objects");
        System.out.println("9. View objects with volume greater than 25cm^3");
    }

    private void exit()
    {
        running = false;
    }

    private void addCube()
    {
        controller.addCube(getDoubleFromConsole("Enter cube edge length: "));
    }

    private void addCylinder()
    {
        controller.addCylinder(getDoubleFromConsole("Enter cylinder height: "),
                getDoubleFromConsole("Enter cylinder radius: "));
    }

    private void addSphere()
    {
        controller.addSphere(getDoubleFromConsole("Enter sphere radius: "));
    }

    private void removeObject()
    {
        controller.removeObject(getIntegerFromConsole("Enter object index: "));
    }

    private void updateCube()
    {
        controller.updateCube(getIntegerFromConsole("Enter cube index: "),
                getDoubleFromConsole("Enter cube edge length: "));
    }

    private void updateCylinder()
    {
        controller.updateCylinder(getIntegerFromConsole("Enter cylinder index: "),
                getDoubleFromConsole("Enter cylinder height: "),
                getDoubleFromConsole("Enter cylinder radius"));
    }

    private void updateSphere()
    {
        controller.updateSphere(getIntegerFromConsole("Enter sphere index: "),
                getDoubleFromConsole("Enter sphere radius: "));
    }

    private void viewAllObjects()
    {
        for(ThreeDimensionalObject object : controller.filter((object) -> true))
        {
            System.out.println(object.toString());
        }
    }

    private void viewObjectsWithWeight()
    {
        for(ThreeDimensionalObject object : controller.filter((object) -> object.getVolume() > 25.0))
        {
            System.out.println(object.toString());
        }
    }
}
