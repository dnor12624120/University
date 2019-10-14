package com.company;

import java.util.ArrayList;

public class Main
{
    public static void main(String[] args)
    {
        Employee e1 = new Employee(1, "test1", 20);
        Manager m1 = new Manager(2, "test2", 10, new ArrayList<Integer>(){{add(1);}});
        try
        {
            EmployeeValidator.validateEmployee(e1);
            EmployeeValidator.validateEmployee(m1);
        }
        catch (EmployeeException exception)
        {
            System.out.println(exception.getMessage());
        }
    }
}
