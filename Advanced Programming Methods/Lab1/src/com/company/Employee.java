package com.company;

import org.jetbrains.annotations.Contract;

public class Employee
{
    private int m_id;
    private String m_name;
    private int m_daysWorkedPerMonth;
    protected static final float m_salaryMultiplier = 2f;

    @Contract(pure = true)
    Employee()
    {
        m_id = 0;
        m_name = "";
    }

    @Contract(pure = true)
    Employee(int id, String name, int daysWorkedPerMonth)
    {
        m_id = id;
        m_name = name;
        m_daysWorkedPerMonth = daysWorkedPerMonth;
    }

    public void setID(int id)
    {
        m_id = id;
    }

    public void setName(String name)
    {
        m_name = name;
    }

    public void setDaysWorkedPerMonth(int daysWorkedPerMonth) { m_daysWorkedPerMonth = daysWorkedPerMonth; }

    public int getID()
    {
        return m_id;
    }

    public String getName()
    {
        return m_name;
    }

    public int getDaysWorkedPerMonth() { return m_daysWorkedPerMonth; }

    public float getSalary() { return m_daysWorkedPerMonth * Manager.m_salaryMultiplier; }
}
