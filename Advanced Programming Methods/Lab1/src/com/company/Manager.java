package com.company;
import org.jetbrains.annotations.Contract;

import java.util.*;

public class Manager extends Employee
{
    private ArrayList<Integer> m_managedEmployees;
    private static final float m_managedEmployeesMultiplier = 15f;


    @Contract(pure = true)
    Manager()
    {

    }

    Manager(int id, String name, int daysWorkedPerMonth, ArrayList<Integer> managedEmployees)
    {
        super(id, name, daysWorkedPerMonth);
        m_managedEmployees = managedEmployees;
    }

    public void addManagedEmployee(int id)
    {
        m_managedEmployees.add(id);
    }

    public ArrayList<Integer> getManagedEmployees()
    {
        return m_managedEmployees;
    }

    public float getSalary()
    {
        return super.getSalary() + m_managedEmployees.size() * Manager.m_managedEmployeesMultiplier;
    }
}
